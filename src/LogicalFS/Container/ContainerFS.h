#ifndef __CONTAINERFS_H_
#define __CONTAINERFS_H_

#include "plfs.h"
#include "LogicalFS.h"
#include "LogicalFD.h"

class Container_OpenFile;   /* forward decl. */

class ContainerFileSystem : public LogicalFileSystem
{
    public:
        ~ContainerFileSystem() {};
        plfs_error_t open(Plfs_fd **pfd, struct plfs_physpathinfo *ppip, 
                          int flags, pid_t pid, mode_t mode, 
                          Plfs_open_opt *open_opt);
        plfs_error_t getattr(struct plfs_physpathinfo *ppip, struct stat *stbuf,
                             int sz_only, Plfs_open_opt *oopt);
        plfs_error_t trunc(struct plfs_physpathinfo *ppip, off_t offset,
                           int open_file, Plfs_open_opt *oopt);
        plfs_error_t chown( struct plfs_physpathinfo *ppip, uid_t u, gid_t g );
        plfs_error_t chmod( struct plfs_physpathinfo *ppip, mode_t mode );
        plfs_error_t getmode( struct plfs_physpathinfo *ppip, mode_t *mode );
        plfs_error_t access( struct plfs_physpathinfo *ppip, int mask );
        plfs_error_t rename(struct plfs_physpathinfo *ppip,
                            struct plfs_physpathinfo *ppip_to, Plfs_open_opt *oopt);
        plfs_error_t link(struct plfs_physpathinfo *ppip, 
                          struct plfs_physpathinfo *ppip_to);
        plfs_error_t utime(struct plfs_physpathinfo *ppip, struct utimbuf *ut);
        plfs_error_t unlink( struct plfs_physpathinfo *ppip, Plfs_open_opt *oopt );

        /* create: requires O_TRUNC for plfs_create, xcreate does the work */
        plfs_error_t create(struct plfs_physpathinfo *ppip, mode_t mode,
                            int flags, pid_t pid, Plfs_open_opt *oopt) {
            return(this->xcreate(ppip, mode, flags|O_TRUNC, pid, oopt));
        }

        plfs_error_t mkdir(struct plfs_physpathinfo *ppip, mode_t);
        plfs_error_t readdir(struct plfs_physpathinfo *ppip, set<string> *buf);
        plfs_error_t readlink(struct plfs_physpathinfo *ppip, char *buf, 
                              size_t bufsize, int *bytes);
        plfs_error_t rmdir(struct plfs_physpathinfo *ppip);
        plfs_error_t symlink(const char *from, 
                             struct plfs_physpathinfo *ppip_to);
        plfs_error_t statvfs(struct plfs_physpathinfo *ppip, 
                             struct statvfs *stbuf);
        plfs_error_t resolvepath_finish(struct plfs_physpathinfo *ppip);

        /* xcreate: like create, but doesn't force O_TRUNC */
        plfs_error_t xcreate(struct plfs_physpathinfo *ppip, mode_t, int flags,
                             pid_t pid, Plfs_open_opt *oopt);
};

/* zero helper function, shared with ContainerFD */
plfs_error_t containerfs_zero_helper(struct plfs_physpathinfo *ppip,
                                     int open_file, 
                                     Container_OpenFile *opencof,
                                     Plfs_open_opt *oopt);
int container_index_id(const char *spec);  /* so YAML sees it */


extern ContainerFileSystem containerfs;

#endif /* __CONTAINERFS_H_ */
