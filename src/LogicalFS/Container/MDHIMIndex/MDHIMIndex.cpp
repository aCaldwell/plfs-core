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

#include "plfs_private.h"
#include "Container.h"
#include "ContainerIndex.h"
#include "ContainerOpenFile.h"
#include "MDHIMIndex.h"


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
    MdhimOpts tmp_opts = pmnt->mdhim_opts; /* Just so we don't have to keep refering to pmnt */

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
    mdhim_options_set_num_worker_threads(this->db_opts, tmp_opts->db_num_wthreads);
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


plfs_error_t
MDHIMIndex::index_open ( Container_OpenFile *cof, int rw_flags,
                         Plfs_open_opt *oopt)
{
    int stat_ret;
    int ret = PLFS_SUCCESS;


    if(this->dirty_stat && (rw_flags == O_RDWR || rw_flags == O_RDONLY)) {
        stat_ret = mdhimStatFlush(this->mdhix, this->mdhix->primary_index);
        if(stat_ret != MDHIM_SUCCESS) {
            ret = PLFS_EINVAL;
        }
    }
    return ret;
}   /* -----  end of method MDHIMIndex::index_open  ----- */



ostream &
operator << ( ostream &os, const MDHIMIndex &obj )
{
    os << "# Index dump" << endl;
    os << "# MDHIMmode=" << endl;
    return os;
}   /* -----  end of function operator <<  ----- */
