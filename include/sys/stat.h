/* sys/stat.h (emx+gcc) */

#ifndef _SYS_STAT_H
#define _SYS_STAT_H

#if !defined (_SYS_TYPES_H)
#warning <sys/stat.h> requires <sys/types.h>
#include <sys/types.h>
#endif

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (_STAT)
#define _STAT
struct stat
{
  dev_t   st_dev;
  ino_t   st_ino;
  mode_t  st_mode;
  nlink_t st_nlink;
  uid_t   st_uid;
  gid_t   st_gid;
  dev_t   st_rdev;
  off_t   st_size;
  time_t  st_atime;
  time_t  st_mtime;
  time_t  st_ctime;
  long    st_attr;
  long    st_reserved;
};
#endif

#if !defined (S_IRUSR)
#define S_IRWXU 00700
#define S_IRUSR 00400
#define S_IWUSR 00200
#define S_IXUSR 00100

#define S_IRWXG 00070
#define S_IRGRP 00040
#define S_IWGRP 00020
#define S_IXGRP 00010

#define S_IRWXO 00007
#define S_IROTH 00004
#define S_IWOTH 00002
#define S_IXOTH 00001

#define	S_ISGID 02000
#define	S_ISUID 04000
#endif

#if !defined (S_IFMT)
#define S_IFMT   0170000  /* Mask for file type */
#define S_IFIFO  0010000  /* Pipe */
#define S_IFCHR  0020000  /* Character device */
#define S_IFDIR  0040000  /* Directory */
#define S_IFREG  0100000  /* Regular file */
#define S_IFSOCK 0140000  /* Socket */

/* S_ISBLK */
#define S_ISCHR(mode)  (((mode) & S_IFMT) == S_IFCHR)
#define S_ISDIR(mode)  (((mode) & S_IFMT) == S_IFDIR)
#define S_ISREG(mode)  (((mode) & S_IFMT) == S_IFREG)
#define S_ISFIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#define S_ISSOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)
#endif

int chmod (__const__ char *, int);
int fstat (int, struct stat *);
int mkdir (__const__ char *, long);
/* mkfifo() */
int stat (__const__ char *, struct stat *);
int umask (int);


#if !defined (_POSIX_SOURCE)

#if !defined (S_IREAD)
#define S_IREAD  0400     /* Owner: read */
#define S_IWRITE 0200     /* Owner: write */
#define S_IEXEC  0100     /* Owner: exec */
#endif

#endif

#if !defined (_POSIX_SOURCE) || defined (_WITH_UNDERSCORE)

int _chmod (__const__ char *, int);
int _fstat (int, struct stat *);
int _mkdir (__const__ char *, long);
/* _mkfifo() */
int _stat (__const__ char *, struct stat *);
int _umask (int);

#endif

#if defined (__cplusplus)
}
#endif

#endif /* not SYS_STAT_H */
