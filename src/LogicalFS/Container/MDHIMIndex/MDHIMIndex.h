/*
 * MDHIMIndex.h  all structures for the MDHIM index
 */

#include "mdhim.h"


struct plfs_index_record {
    unsigned int chunk_id;
    off_t logical_offset;
    unsigned long long int size;
    unsigned long long int physical_offset;
    char dropping_file[PATH_MAX];
};               /* ----------  end of struct plfs_put_index_record  ---------- */

typedef struct plfs_index_record Plfs_index_record;

/**
 * MDHIMIndex: MDHIM instance of PLFS container index
 */
class MDHIMIndex : public ContainerIndex {
public:
    MDHIMIndex(PlfsMount *pmnt, Plfs_open_opt *oopt);  /* constructor */
    ~MDHIMIndex();                /* destructor */

    const char *index_name(void) { return("MDHIM"); };

    plfs_error_t index_open(Container_OpenFile *cof, int rw_flags,
                            Plfs_open_opt *oopt);
    plfs_error_t index_close(Container_OpenFile *cof, off_t *lastoffp,
                             size_t *tbytesp, Plfs_close_opt *copt);
    plfs_error_t index_add(Container_OpenFile *cof, size_t nbytes,
                           off_t offset, pid_t pid, off_t physoffset,
                           double begin, double end); 
    plfs_error_t index_sync(Container_OpenFile *cof);
    plfs_error_t index_query(Container_OpenFile *cof, off_t input_offset,
                             size_t input_length, list<index_record> &result);
    plfs_error_t index_truncate(Container_OpenFile *cof, off_t offset);
    plfs_error_t index_closing_wdrop(Container_OpenFile *cof, string ts,
                                     pid_t pid, const char *filename);
    plfs_error_t index_new_wdrop(Container_OpenFile *cof, string ts,
                                 pid_t pid, const char *filename);
    plfs_error_t index_optimize(Container_OpenFile *cof);
    plfs_error_t index_info(off_t &lastoff, off_t &bwritten);

    plfs_error_t index_droppings_getattrsize(struct plfs_physpathinfo *ppip,
                                             struct stat *stbuf,
                                             set<string> *openset,
                                             set<string> *metaset);

    plfs_error_t index_droppings_rename(struct plfs_physpathinfo *src,
                                        struct plfs_physpathinfo *dst);
    plfs_error_t index_droppings_trunc(struct plfs_physpathinfo *ppip,
                                               off_t offset);
    plfs_error_t index_droppings_unlink(struct plfs_physpathinfo *ppip);
    plfs_error_t index_droppings_zero(struct plfs_physpathinfo *ppip);

    friend ostream& operator <<(ostream&, const MDHIMIndex&);

private:
    struct mdhim_t *mdhix;     /* handle to any open mdhim index */
    mdhim_options_t *db_opts;  /* handle to the database options for MDHIM */
    int dirty_stat;            /* Flag to keep stats clean */
    int stat_ret;              /* Has a stat been successfully performed */
    Plfs_index_record *record; /* Structure to pass into MDHIM that will hold record
                                  information */

    /*
     * additional state needed:
     *
     * XXX: in-memory cache for index records being written.  allows
     * us to cache a number of records and send them down to mdhim
     * in a batch.  also, if the mdhim index hasn't been established,
     * this will also allow us to cache the records before the ranges
     * for the range servers are established.   we can then analyze
     * the set of offset in memory and use that to make our best guess
     * the optimal mapping from offset to range servers.
     *
     * XXX: range mapping information (non-NULL if ranges have been
     * set?).   we need to know where the range boundaries are so that
     * we can arrange our records so that they do not span range
     * boundaries.  this arrangement is required because MDHIM STAB
     * queries do not span range server boundaries.
     * 
     * XXX: anything else that is needed to configure MDHIM should go
     * here... for example, the set of group communications functions
     * to use.
     */
};
