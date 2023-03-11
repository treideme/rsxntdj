/* sys/statfs.h (emx+gcc) */

#ifndef _SYS_STATFS_H
#define _SYS_STATFS_H

#if !defined (_STATFS)
#define _STATFS
struct statfs
{
  short f_fstyp;
  long f_bsize;
  long f_frsize;
  long f_blocks;
  long f_bfree;
  long f_files;
  long f_ffree;
  char f_fname[6];
  char f_fpack[6];
};
#endif

#endif /* not SYS_STATFS_H */
