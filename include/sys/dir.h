/* sys/dir.h (emx+gcc) */

#ifndef _SYS_DIR_H
#define _SYS_DIR_H

#if !defined (_SYS_TYPES_H)
#warning <sys/dir.h> requires <sys/types.h>
#include <sys/types.h>
#endif

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (MAXNAMLEN)
#define MAXNAMLEN  260
#endif

#if !defined (MAXPATHLEN)
#define MAXPATHLEN 260
#endif

#if !defined (A_RONLY)
#define A_RONLY   0x01
#define A_HIDDEN  0x02
#define A_SYSTEM  0x04
#define A_LABEL   0x08
#define A_DIR     0x10
#define A_ARCHIVE 0x20
#endif

#define _DIRECT_D_MODE_RENAMED_D_ATTR

struct direct
{
  ino_t          d_ino;                 /* Almost not used           */
  int            d_reclen;              /* Almost not used           */
  int            d_namlen;              /* Length of d_name          */
  char           d_name[MAXNAMLEN + 1]; /* File name, 0 terminated   */
  long           d_size;                /* File size (bytes)         */
  unsigned short d_attr;                /* OS file attributes        */
  unsigned short d_time;                /* OS file modification time */
  unsigned short d_date;                /* OS file modification date */
};

struct _dircontents
{
  char *                _d_entry;
  long                  _d_size;
  unsigned short        _d_attr;
  unsigned short        _d_time;
  unsigned short        _d_date;
  struct _dircontents * _d_next;
};

struct _dirdesc
{
  int                   dd_id;
  long                  dd_loc;
  struct _dircontents * dd_contents;
  struct _dircontents * dd_cp;
};

typedef struct _dirdesc DIR;

DIR *opendir (__const__ char *name);
struct direct *readdir (DIR *dirp);
void seekdir (DIR *dirp, long off);
long telldir (DIR *dirp);
int closedir (DIR *dirp);
void rewinddir (DIR *dirp);

#if defined (__cplusplus)
}
#endif

#endif /* not SYS_DIR_H */
