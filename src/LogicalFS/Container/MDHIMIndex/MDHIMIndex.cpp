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


/**
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex
 * Description:  constructor
 *
 * @param pmnt A pointer to the PlfsMount
 * @param oopt A pointer to the Plfs_open_opt structure (contains the MPI_COMM)
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
 * @param cof Container_OpenFile pointer
 * @param rw_flags Combination of Posix file open flags (O_CREAT, O_TRUNC, O_RDWR, O_WONLY, O_RDONLY, etc)
 * @param oopt Plfs_open_opt pointer
 * @return ret PLFS error status
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
                this->isopen = true;
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
 * @param cof Pointer to the Container_OpenFile object
 * @param nbytes Number of bytes writen to the data dropping
 * @param offset The logical offset of where the data can be found
 * @param pid The pid of the writing proc
 * @param physoffset The physical offset of the data in the data dropping
 * @param begin
 * @param end
 * 
 * @return ret PLFS Error codes
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_add ( Container_OpenFile */* cof */, size_t nbytes, 
                        off_t offset, pid_t pid, off_t physoffset, 
                        double /* begin */, double /* end */)
{
    plfs_error_t ret = PLFS_SUCCESS;
    unsigned long long key = offset;                  // The identifing key for MDHIM

    if (!this->isopen) { // should not be possible
        mlog(IDX_CRIT, "index_add: but not open?!");
        ret = PLFS_EINVAL;
        goto done;
    }

    this->record->chunk_id       = pid;
    this->record->logical_offset = offset;
    this->record->size           = nbytes;
    this->record->physical_offset = physoffset;

    this->return_msg = mdhimPut(this->mdhix, &key, sizeof(key), this->record, sizeof(Plfs_index_record), NULL, NULL);

    if (!this->return_msg || this->return_msg->error) {
        mlog(IDX_CRIT, "failed to insert key/value into MDHIM index!");
        ret = PLFS_EINVAL;
        goto done;
    }    
    this->dirty_stat = 1; /* Let us know we need to do a mdhimCommit before reading */
    mdhimCommit(this->mdhix, this->mdhix->primary_index);

done:
    mdhim_full_release_msg(this->return_msg);
    return ret;
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
 *      Method:  MDHIMIndex :: index_query
 * Description:  Stab into MDHIM to get the meta data for the data file
 *--------------------------------------------------------------------------------------
 */
plfs_error_t
MDHIMIndex::index_query ( Container_OpenFile * /* cof */, off_t input_offset, size_t input_length, list<index_record> &/* result */ )
{
    plfs_error_t ret = PLFS_SUCCESS;

    ssize_t bytes_remaining = input_length;  // Keep track of how many bytes have been retrieved
    ssize_t bytes_traversed = 0;
    off_t shift;                             // How far we need to shift to get next set of bytes
    unsigned long long int mdhim_value_size; // The size of the returned message

    this->greturn_msg = mdhim_get((unsigned long long int)input_offset, MDHIM_GET_EQ);
    if(!this->greturn_msg || this->greturn_msg->error) {
        // Key did not match offset so get previous key
        this->greturn_msg = mdhim_get((unsigned long long int)input_offset, MDHIM_GET_PREV);
        if(!this->greturn_msg || this->greturn_msg->error) {
            // This is an error condition since no key was found
            ret = PLFS_EINVAL;
            return ret;
        } else if(!this->greturn_msg->keys[0] || !this->greturn_msg->values[0]) {
            // MDHIM returnded but the information was errornous
            mlog(PLFS_DBG, "mdhimGet with MDHIM_GET_PREV failed.\n");
            ret = PLFS_EINVAL;
            return ret;
        }
    }

    // Point to returned value from mdhim_get
    this->record = (Plfs_index_record *)this->greturn_msg->values[0];
    mdhim_value_size = this->record->size;

    do {
        // Determine the offset to start reading the data dropping at
        // Example:
        //  0K                   1K                      2K
        //   ___________________________________________________________________
        //  |____________________|_______________________|______________________|
        //  {-------------v-----------------}
        //             request (size = 1.5K)
        //  There will be no issue on a direct hit but when we get the rest of the
        //  information from the next key we need to know to start at 0 not at 1k
        //     chunk_offset = offset (0) + bytes_traversed (1K) - current.logical_offset (1K)
        //     tell plfs to start reading at offset 0 in the referenced data dropping
        //  the same can be done when the offset starts at 1.5K on the next read query
        //     chunk_offset = offset (1.5) + bytes_traversed (0) - current.logical_offset (1k)
        //     tell plfs to reading up to offset 0.5k in the referenced data dropping
        shift = input_offset+bytes_traversed - this->record->logical_offset;
        bytes_remaining = 0;
        
    } while (bytes_remaining != 0);

    
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
MDHIMIndex::index_new_wdrop ( Container_OpenFile *cof, string ts, pid_t /* pid */, const char *filename)
{
    plfs_error_t ret = PLFS_SUCCESS;
    ostringstream ddrop_pathstream;

    /*
     * Build a string of the path to the data dropping file
     *
     * See ByteRangeIndex::index_new_wdrop for why cof->pid is
     * used over pid (the args)
     */
    ddrop_pathstream << cof->subdir_path << "/" << DROPPINGPREFIX <<
        ts << "." << cof->hostname << "." << cof->pid;

    /* Store the string in the record structure */
    strcpy(this->record->dropping_file, filename);

    return ret;
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


/*
 *--------------------------------------------------------------------------------------
 *       Class:  MDHIMIndex
 *      Method:  MDHIMIndex :: mdhim_get
 * Description:  Does the MDHIM stab appropriate for the type of stab.
 *--------------------------------------------------------------------------------------
 */
struct mdhim_bgetrm_t *
MDHIMIndex::mdhim_get ( unsigned long long int key, int operation )
{
    struct mdhim_bgetrm_t *mdhim_ret;
    if(operation == MDHIM_GET_EQ || operation == MDHIM_GET_PRIMARY_EQ) {
        mdhim_ret = mdhimGet( this->mdhix, this->mdhix->primary_index, &key, sizeof(key), operation);
    } else if(operation == MDHIM_GET_PREV || operation == MDHIM_GET_NEXT) {
        mdhim_ret = mdhimBGetOp( this->mdhix, this->mdhix->primary_index, &key, sizeof(key), 1, operation);
    }
    return mdhim_ret;
}		/* -----  end of method MDHIMIndex::mdhim_get  ----- */

