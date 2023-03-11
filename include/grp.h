/* grp.h (emx+gcc) */

#ifndef _GRP_H
#define _GRP_H

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (_GID_T)
#define _GID_T
typedef int gid_t;
#endif

struct group
{
  char *gr_name;
  gid_t gr_gid;
  char **gr_mem;
};

struct group *getgrgid (gid_t);
struct group *getgrnam (__const__ char *);

#if defined (__cplusplus)
}
#endif

#endif /* not _GRP_H */
