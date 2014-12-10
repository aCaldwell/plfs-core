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
MDHIMIndex::MDHIMIndex ()
{
    mdhix = NULL;
}  /* -----  end of method MDHIMIndex::MDHIMIndex  (constructor)  ----- */


void
MDHIMIndex::index_open ( Container_OpenFile *cof, int rw_flags,
                         Plfs_open_opt *oopt)
{
    return ;
}		/* -----  end of method MDHIMIndex::index_open  ----- */



ostream &
operator << ( ostream &os, const MDHIMIndex &obj )
{
    os << "# Index dump" << endl;
    os << "# MDHIMmode=" << endl;
    return os;
}		/* -----  end of function operator <<  ----- */
