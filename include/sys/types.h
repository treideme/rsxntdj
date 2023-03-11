/* sys/types.h (emx+gcc) */

#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#if !defined (_SIZE_T)
#define _SIZE_T
typedef unsigned long size_t;
#endif

#if !defined (_SSIZE_T)
#define _SSIZE_T
typedef int ssize_t;
#endif

#if !defined (_TIME_T)
#define _TIME_T
typedef unsigned long time_t;
#endif

#if !defined (_INO_T)
#define _INO_T
typedef int ino_t;
#endif

#if !defined (_DEV_T)
#define _DEV_T
typedef int dev_t;
#endif

#if !defined (_OFF_T)
#define _OFF_T
typedef long off_t;
#endif

#if !defined (_MODE_T)
#define _MODE_T
typedef int mode_t;
#endif

#if !defined (_NLINK_T)
#define _NLINK_T
typedef int nlink_t;
#endif

#if !defined (_UID_T)
#define _UID_T
typedef int uid_t;
#endif

#if !defined (_PID_T)
#define _PID_T
typedef int pid_t;
#endif

#if !defined (_GID_T)
#define _GID_T
typedef int gid_t;
#endif

#if !defined (_POSIX_SOURCE)

#if !defined (FD_SETSIZE)
#define	FD_SETSIZE      256
#elif FD_SETSIZE < 256
#error FD_SETSIZE must be at least 256
#endif

#if !defined (_FD_SET_T)
#define _FD_SET_T

typedef struct _fd_set
{
  unsigned long fds_bits[(FD_SETSIZE+31) / 32];
} fd_set;

#endif

#define	FD_SET(n,s)    ((s)->fds_bits[(n)/32] |=  (1L << ((n) & 0x1f)))
#define	FD_CLR(n,s)    ((s)->fds_bits[(n)/32] &= ~(1L << ((n) & 0x1f)))
#define	FD_ISSET(n,s)  ((s)->fds_bits[(n)/32] &   (1L << ((n) & 0x1f)))
#define FD_ZERO(s)     (void)memset (s, 0, sizeof (*(s)))

#endif

#if !defined (_POSIX_SOURCE)

typedef	unsigned char u_char;
typedef	unsigned short u_short;
typedef	unsigned u_int;
typedef	unsigned long u_long;
typedef char *caddr_t;

#endif

#endif /* not _SYS_TYPES_H */
