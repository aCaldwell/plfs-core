#include "plfs_private.h"
#include "ContainerIndex.h"

#include "ByteRangeIndex.h"

/**
 * container_index_id
 *
 * @param spec the index type to lookup
 * @return the id of the index, CT_UNKNOWN if we can't it
 */
int container_index_id(const char *spec) {
    if (strcasecmp(spec, "byterange") == 0)
        return(CI_BYTERANGE);
    if (strcasecmp(spec, "mdhim") == 0)
        return(CI_MDHIM);
#if 0   /* XXX: placeholder for pattern-based index compression */
    if (strcasecmp(spec, "pattern") == 0)
        return(CI_PATTERN);
#endif
    return(CI_UNKNOWN);
}

/**
 * container_index_alloc: allocate an index based on type
 *
 * @param pmnt the mount we are using (to get type value)
 * @return the new index
 */
class ContainerIndex *container_index_alloc(PlfsMount *pmnt, Plfs_open_opt *oopt) {
    ContainerIndex *ci;

    switch (pmnt->fileindex_type) {
    case CI_BYTERANGE:
        ci = new ByteRangeIndex(pmnt);
        break;
#if 0 /* notyet */
    case CI_PATTERN:
        ci = new PatternIndex(pmnt);
        break;
#endif        
    case CI_MDHIM:
        ci = new MDHIMIndex(pmnt, oopt);
        break;
    default:
        ci = NULL;
        mlog(CON_CRIT, "container_index_alloc: unknown type %d",
             pmnt->fileindex_type);
    }

    return(ci);
}

/**
 * container_index_free: free index no longer in use
 *
 * @param ci the index to free
 * @return PLFS_SUCCESS or error
 */
plfs_error_t container_index_free(ContainerIndex *ci) {
    
    /* XXX: add some logging? */
    
    delete ci;
    return(PLFS_SUCCESS);
    
}

