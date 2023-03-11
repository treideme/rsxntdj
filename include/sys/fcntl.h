/* sys/fcntl.h (emx+gcc) */

#ifndef _SYS_FCNTL_H
#define _SYS_FCNTL_H

#if defined (__cplusplus)
extern "C" {
#endif

/* Don't forget to update /emx/src/dos/termio.inc when changing this! */

#if !defined (O_RDONLY)
#define O_ACCMODE       0x03    /* mask */
#define O_RDONLY        0x00
#define O_WRONLY        0x01
#define O_RDWR          0x02
#define O_NONBLOCK      0x04
#define O_APPEND        0x08
#define O_TEXT          0x10

#define O_BINARY        0x0100
#define O_CREAT         0x0200
#define O_TRUNC         0x0400
#define O_EXCL          0x0800
#define O_SYNC          0x2000
#define O_NOCTTY        0x4000
#define O_SIZE          0x8000

#if !defined (_POSIX_SOURCE)
#define O_NDELAY        O_NONBLOCK
#define O_NOINHERIT     0x1000
#endif

#endif

#if !defined (F_OK)
#define F_OK 0
#define X_OK 1
#define W_OK 2
#define R_OK 4
#endif

#if !defined (F_GETFL)
#define F_GETFL     1
#define F_SETFL     2
#define F_GETFD     3
#define F_SETFD     4
#define F_DUPFD     5
#define F_GETOSFD   6           /* RSXNT */
#endif

#if !defined (FD_CLOEXEC)
#define FD_CLOEXEC  0x01
#endif

int creat (__const__ char *, int);
int fcntl (int, int, ...);
int open (__const__ char *, int, ...);

#if !defined (_POSIX_SOURCE)

#if !defined (LOCK_SH)
#define LOCK_SH     0x01
#define LOCK_EX     0x02
#define LOCK_NB     0x04
#define LOCK_UN     0x08
#endif

int flock (int, int);

#endif


#if !defined (_POSIX_SOURCE) || defined (_WITH_UNDERSCORE)

int _creat (__const__ char *, int);
int _fcntl (int, int, ...);
int _flock (int, int);
int _open (__const__ char *, int, ...);

#endif


#if defined (__cplusplus)
}
#endif

#endif /* not _SYS_FCNTL_H */
