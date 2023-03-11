/* io.h (emx+gcc) */

#ifndef _IO_H
#define _IO_H

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (_SIZE_T)
#define _SIZE_T
typedef unsigned long size_t;
#endif

#if !defined (SEEK_SET)
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

struct stat;
struct _fd_set;
struct timeval;

int remove (__const__ char *);
int rename (__const__ char *, __const__ char *);

int access (__const__ char *, int);
int chmod (__const__ char *, int);
int chsize (int, long);
int close (int);
int creat (__const__ char *, int);
int dup (int);
int dup2 (int, int);
int eof (int);
long filelength (int);
int fstat (int, struct stat *);
int fsync (int);
int ftruncate (int, long);
int ioctl (int, int request, ...);
int isatty (int);
long lseek (int, long, int);
int mkstemp (char *);
char *mktemp (char *);
int open (__const__ char *, int, ...);
int pipe (int *);
int read (int, void *, size_t);
int select (int, struct _fd_set *, struct _fd_set *, struct _fd_set *,
    struct timeval *);
int setmode (int, int);
int sopen (__const__ char *, int, int, ...);
int stat (__const__ char *, struct stat *);
long tell (int);
int truncate (char *, long);
int umask (int);
int unlink (__const__ char *);
int write (int, __const__ void *, size_t);

int _access (__const__ char *, int);
int _chmod (__const__ char *, int);
int _chsize (int, long);
int _close (int);
int _creat (__const__ char *, int);
int _crlf (char *, size_t, size_t *);
int _dup (int);
int _dup2 (int, int);
int _eof (int);
long _filelength (int);
int _fstat (int, struct stat *);
int _fsync (int);
int _ftruncate (int, long);
int _imphandle (int);
int _ioctl (int, int request, ...);
int _isatty (int);
int _isterm (int);
long _lseek (int, long, int);
int _mkstemp (char *);
char *_mktemp (char *);
int _open (__const__ char *, int, ...);
int _pipe (int *);
int _read (int, void *, size_t);
int _seek_hdr (int);
int _select (int, struct _fd_set *, struct _fd_set *, struct _fd_set *,
    struct timeval *);
int _setmode (int, int);
int _sopen (__const__ char *, int, int, ...);
int _stat (__const__ char *, struct stat *);
long _tell (int);
int _truncate (char *, long);
int _umask (int);
int _unlink (__const__ char *);
int _write (int, __const__ void *, size_t);

#if defined (__cplusplus)
}
#endif

#endif /* not _IO_H */
