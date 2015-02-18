/*
 * =====================================================================================
 *
 *       Filename:  MDHIMIndex.c
 *
 *    Description:  MDHIM index code
 *
 *        Version:  1.0
 *        Created:  11/25/2014 03:05:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aaron Caldwell (), acaldwell@lanl.gov
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "plfs_private.h"
#include "Container.h"
#include "ContainerIndex.h"
#include "ContainerOpenFile.h"
#include "MDHIMIndex.h"


ostream&
operator << ( ostream &os, const MDHIMIndex /*&obj */)
{
    os << "# Index dump" << endl;
    os << "# MDHIMmode=" << endl;
    return os;
}   /* -----  end of function operator <<  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
MDHIMIndex::MDHIMIndex (PlfsMount *pmnt, Plfs_open_opt *oopt)
{
    this->db_opts = mdhim_options_init();  /* Initialize the options */
    MdhimOpts *tmp_opts = pmnt->mdhim_opts; /* Just so we don't have to keep refering to pmnt */

    /*
    * XXXAC:
    * Set the mdhim_options.
    * If not defined in the plfsrc, they will be set to the defaults defined by
    * mdhim_options_init
    */
    mdhim_options_set_create_new_db(this->db_opts, tmp_opts->db_create_new);
    mdhim_options_set_key_type(this->db_opts, tmp_opts->db_key_type);
    mdhim_options_set_db_type(this->db_opts, tmp_opts->db_type);
    mdhim_options_set_value_append(this->db_opts, tmp_opts->db_value_append);
    mdhim_options_set_num_worker_threads(this->db_opts, tmp_opts->num_wthreads);
    mdhim_options_set_server_factor(this->db_opts, tmp_opts->db_create_new);
    mdhim_options_set_debug_level(this->db_opts, tmp_opts->debug_level);
    mdhim_options_set_max_recs_per_slice(this->db_opts, tmp_opts->max_recs_per_slice);
    if(tmp_opts->db_name) 
        mdhim_options_set_db_name(this->db_opts, tmp_opts->db_name);
    if(tmp_opts->db_path)
        mdhim_options_set_db_path(this->db_opts, tmp_opts->db_path);
    if(tmp_opts->db_host && tmp_opts->dbs_host && tmp_opts->db_user && 
            tmp_opts->dbs_user && tmp_opts->db_upswd && tmp_opts->dbs_upswd) 
        mdhim_options_set_login_c(this->db_opts, tmp_opts->db_host, tmp_opts->dbs_host, 
                                tmp_opts->db_user, tmp_opts->dbs_user, 
                                tmp_opts->db_upswd, tmp_opts->dbs_upswd);
    if(tmp_opts->db_paths && tmp_opts->num_paths > 0)
        mdhim_options_set_db_paths(this->db_opts, tmp_opts->db_paths, tmp_opts->num_paths);
    if(tmp_opts->manifest_path)
        set_manifest_path(this->db_opts, tmp_opts->manifest_path);

    this->mdhix = mdhimInit(oopt->mdhim_comm, this->db_opts);
    this->dirty_stat = 1;
}   /* -----  end of method MDHIMIndex::MDHIMIndex  (constructor)  ----- */



/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: ~MDHIMIndex
 * Description:  Destructor
 *--------------------------------------------------------------------------------------
 */
MDHIMIndex::~MDHIMIndex()
{
    int closed = MDHIM_SUCCESS;
    closed = mdhimClose(this->mdhix);
    if(closed != MDHIM_SUCCESS) {
        printf("Error closing MDHIM\n");
    }

    mdhim_options_destroy(this->db_opts);

}		/* -----  end of method MDHIMIndex::~MDHIMIndex  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: index_open
 * Description:  This function will check if MDHIM was initialized and then check if 
 *               A stat was ran to get the information about the data distribution.
 *   Arguments:  <cof>: Container_OpenFile pointer
 *               <rw_flags>: Combination of Posix file open flags (O_CREAT, O_TRUNC,
 *                           O_RDWR, O_WONLY, O_RDONLY, etc)
 *               <oopt>: Plfs_open_opt pointer
 *      Return:  <ret>: PLFS error status
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_open ( Container_OpenFile *cof, int rw_flags,
                         Plfs_open_opt *oopt)
{
    if(cof || oopt) {
        printf("This is a place holder");
    }
    plfs_error_t ret = PLFS_SUCCESS;

    if(!this->mdhix) {
        ret = PLFS_EINVAL;
    }

    if (ret == PLFS_SUCCESS) {
        if(this->dirty_stat && (rw_flags == O_RDWR || rw_flags == O_RDONLY)) {
            this->stat_ret = mdhimStatFlush(this->mdhix, this->mdhix->primary_index);
            if(this->stat_ret != MDHIM_SUCCESS) {
                ret = PLFS_EINVAL;
            }else {
                this->dirty_stat = 0;
            }
        }
    }
    return ret;
}   /* -----  end of method MDHIMIndex::index_open  ----- */



/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: index_close
 * Description:  Close (Nothing to do here because the Destructor will close MDHIM)
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_close( Container_OpenFile *, off_t*, size_t*, Plfs_close_opt*)
{
    return PLFS_SUCCESS;
}		/* -----  end of method MDHIMIndex::index_close  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: index_add
 * Description:  Insert into MDHIM an index entry of the data_dropping files location 
 *               and name, logical_offset, physical_offset
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_add ( Container_OpenFile*, size_t, off_t, pid_t, off_t, double, double )
{
    return PLFS_SUCCESS;
}		/* -----  end of method MDHIMIndex::index_add  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: index_add
 * Description:  Insert into MDHIM an index entry of the data_dropping files location 
 *               and name, logical_offset, physical_offset
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_sync ( Container_OpenFile * )
{
    return PLFS_SUCCESS;
}		/* -----  end of method MDHIMIndex::index_sync  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: index_add
 * Description:  Insert into MDHIM an index entry of the data_dropping files location 
 *               and name, logical_offset, physical_offset
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_query ( Container_OpenFile *, off_t , size_t, list<index_record> & )
{
    return PLFS_SUCCESS;
}		/* -----  end of method MDHIMIndex::index_query  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: index_add
 * Description:  Insert into MDHIM an index entry of the data_dropping files location 
 *               and name, logical_offset, physical_offset
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_truncate ( Container_OpenFile *, off_t )
{
    return PLFS_SUCCESS;
}		/* -----  end of method MDHIMIndex::index_query  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: index_add
 * Description:  Insert into MDHIM an index entry of the data_dropping files location 
 *               and name, logical_offset, physical_offset
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_closing_wdrop ( Container_OpenFile *, string, pid_t, const char * )
{
    return PLFS_SUCCESS;
}		/* -----  end of method MDHIMIndex::index_query  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: index_add
 * Description:  Insert into MDHIM an index entry of the data_dropping files location 
 *               and name, logical_offset, physical_offset
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_new_wdrop ( Container_OpenFile *, string, pid_t, const char * )
{
    return PLFS_SUCCESS;
}		/* -----  end of method MDHIMIndex::index_query  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: index_add
 * Description:  Insert into MDHIM an index entry of the data_dropping files location 
 *               and name, logical_offset, physical_offset
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_optimize ( Container_OpenFile * )
{
    return PLFS_SUCCESS;
}		/* -----  end of method MDHIMIndex::index_query  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: index_add
 * Description:  Insert into MDHIM an index entry of the data_dropping files location 
 *               and name, logical_offset, physical_offset
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_info ( off_t &, off_t & )
{
    return PLFS_SUCCESS;
}		/* -----  end of method MDHIMIndex::index_query  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: index_add
 * Description:  Insert into MDHIM an index entry of the data_dropping files location 
 *               and name, logical_offset, physical_offset
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_droppings_getattrsize ( struct plfs_physpathinfo *,
                                          struct stat *,
                                          set<string> *,
                                          set<string> * )
{
    return PLFS_SUCCESS;
}		/* -----  end of method MDHIMIndex::index_query  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: index_add
 * Description:  Insert into MDHIM an index entry of the data_dropping files location 
 *               and name, logical_offset, physical_offset
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_droppings_rename ( struct plfs_physpathinfo *,
                                     struct plfs_physpathinfo *)
{
    return PLFS_SUCCESS;
}		/* -----  end of method MDHIMIndex::index_query  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: index_add
 * Description:  Insert into MDHIM an index entry of the data_dropping files location 
 *               and name, logical_offset, physical_offset
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_droppings_trunc ( struct plfs_physpathinfo *,
                                     off_t )
{
    return PLFS_SUCCESS;
}		/* -----  end of method MDHIMIndex::index_query  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: index_add
 * Description:  Insert into MDHIM an index entry of the data_dropping files location 
 *               and name, logical_offset, physical_offset
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_droppings_unlink ( struct plfs_physpathinfo *)
{
    return PLFS_SUCCESS;
}		/* -----  end of method MDHIMIndex::index_query  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: index_add
 * Description:  Insert into MDHIM an index entry of the data_dropping files location 
 *               and name, logical_offset, physical_offset
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_droppings_zero ( struct plfs_physpathinfo *)
{
    return PLFS_SUCCESS;
}		/* -----  end of method MDHIMIndex::index_query  ----- */
