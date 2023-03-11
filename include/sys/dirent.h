/* sys/dirent.h (emx+gcc) */

#ifndef _SYS_DIRENT_H
#define _SYS_DIRENT_H

#if !defined (_SYS_TYPES_H)
#warning <sys/dirent.h> requires <sys/types.h>
#include <sys/types.h>
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

#define _DIRENT_D_MODE_RENAMED_D_ATTR

struct dirent
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

#endif /* not SYS_DIRENT_H */
