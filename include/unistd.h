/* unistd.h (emx+gcc) */

#ifndef _UNISTD_H
#define _UNISTD_H

#if defined (__cplusplus)
extern "C" {
#endif

#if defined (_POSIX_C_SOURCE) && !defined (_POSIX_SOURCE)
#define _POSIX_SOURCE
#endif

#if !defined (_SIZE_T)
#define _SIZE_T
typedef unsigned long size_t;
#endif

#if !defined (_SSIZE_T)
#define _SSIZE_T
typedef int ssize_t;
#endif

#if !defined (NULL)
#if defined (__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#if !defined (STDIN_FILENO)
#define STDIN_FILENO    0
#define STDOUT_FILENO   1
#define STDERR_FILENO   2
#endif

#if !defined (F_OK)
#define F_OK 0
#define X_OK 1
#define W_OK 2
#define R_OK 4
#endif

#if !defined (SEEK_SET)
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

#if !defined (_PC_LINK_MAX)
#define _PC_LINK_MAX            1
#define _PC_MAX_CANON           2
#define _PC_MAX_INPUT           3
#define _PC_NAME_MAX            4
#define _PC_PATH_MAX            5
#define _PC_PIPE_BUF            6
#define _PC_CHOWN_RESTRICTED    7
#define _PC_NO_TRUNC            8
#define _PC_VDISABLE            9
#endif

#if !defined (_SC_ARG_MAX)
#define _SC_ARG_MAX             1
#define _SC_CHILD_MAX           2
#define _SC_CLK_TCK             3
#define _SC_NGROUPS_MAX         4
#define _SC_OPEN_MAX            5
#define _SC_STREAM_MAX          6
#define _SC_TZNAME_MAX          7
#define _SC_JOB_CONTROL         8
#define _SC_SAVED_IDS           9
#define _SC_VERSION             10
#endif

#if !defined (_POSIX_VERSION)
#define _POSIX_VERSION          199009L
#endif


int access (__const__ char *, int);
unsigned alarm (unsigned);
int chdir (__const__ char *);
/* chown() */
int close (int);
/* ctermid() */
char *cuserid (char *);
int dup (int);
int dup2 (int, int);
int execl (__const__ char *, __const__ char *, ...);
int execle (__const__ char *, __const__ char *, ...);
int execlp (__const__ char *, __const__ char *, ...);
int execv (__const__ char *, char * __const__ *);
int execve (__const__ char *, char * __const__ *, char * __const__ *);
int execvp (__const__ char *, char * __const__ *);
void _exit (int) __attribute__ ((__noreturn__));
int fork (void);
long fpathconf (int, int);
char *getcwd (char *, size_t);
int getegid (void);             /* gid_t getegid (void); */
int geteuid (void);             /* uid_t geteuid (void); */
int getgid (void);              /* gid_t getgid (void); */
int getgroups (int, int *);     /* int getgroups (int, gid_t *); */
char *getlogin (void);
int getpgrp (void);             /* pid_t getpgrp (void); */
int getpid (void);              /* pid_t getpid (void); */
int getppid (void);             /* pid_t getppid (void); */
int getuid (void);              /* uid_t getuid (void); */
int isatty (int);
/* link() */
long lseek (int, long, int);
long pathconf (__const__ char *, int);
int pause (void);
int pipe (int *);
int read (int, void *, size_t);
int rmdir (__const__ char *);
int setgid (int);               /* int setsid (gid_t); */
int setpgid (int, int);         /* int setpgid (gid_t, gid_t); */
int setsid (void);              /* pid_t setsid (void); */
int setuid (int);               /* setuid (uid_t); */
unsigned sleep (unsigned);
long sysconf (int);
int tcgetpgrp (int);            /* pid_t tcgetpgrp (int); */
int tcsetpgrp (int, int);       /* int tcsetpgrp (int, pid_t) */
char *ttyname (int);
int unlink (__const__ char *);
int write (int, __const__ void *, size_t);


#if !defined (_POSIX_SOURCE)

void *brk (void *);
char *getpass (__const__ char *);
char *_getpass1 (__const__ char *);
char *_getpass2 (__const__ char *, int);
int mkstemp (char *);
char *mktemp (char *);
int profil (void *, unsigned, unsigned, unsigned);
void *sbrk (int);

#endif


#if !defined (_POSIX_SOURCE) || _POSIX_C_SOURCE >= 2

extern char *optarg;
extern int optind;
extern int opterr;
extern int optopt;

/* Note: The 2nd argument is not const as GETOPT_ANY reorders the
   array pointed to. */

int getopt (int, char **, __const__ char *);

#endif


#if !defined (_POSIX_SOURCE) || defined (_WITH_UNDERSCORE)

extern char *_optarg;
extern int _optind;
extern int _opterr;
extern int _optopt;

int _getopt (int, char **, __const__ char *);

int _access (__const__ char *, int);
unsigned _alarm (unsigned);
int _chdir (__const__ char *);
int _close (int);
char *_cuserid (char *);
int _dup (int);
int _dup2 (int, int);
int _execl (__const__ char *, __const__ char *, ...);
int _execle (__const__ char *, __const__ char *, ...);
int _execlp (__const__ char *, __const__ char *, ...);
int _execv (__const__ char *, char * __const__ *);
int _execve (__const__ char *, char * __const__ *, char * __const__ *);
int _execvp (__const__ char *, char * __const__ *);
int _fork (void);
long _fpathconf (int, int);
char *_getcwd (char *, size_t);
int _getegid (void);
int _geteuid (void);
int _getgid (void);
int _getgroups (int, int *);
char *_getlogin (void);
int _getpgrp (void);
int _getpid (void);
int _getppid (void);
int _getuid (void);
int _isatty (int);
long _lseek (int, long, int);
long _pathconf (__const__ char *, int);
int _pause (void);
int _pipe (int *);
int _read (int, void *, size_t);
int _rmdir (__const__ char *);
int _setgid (int);
int _setpgid (int, int);
int _setsid (void);
int _setuid (int);
unsigned _sleep (unsigned);
long _sysconf (int);
int _tcgetpgrp (int);
int _tcsetpgrp (int, int);
char *_ttyname (int);
int _unlink (__const__ char *);
int _write (int, __const__ void *, size_t);

void *_brk (void *);
char *_getpass (__const__ char *);
char *_getpass1 (__const__ char *);
char *_getpass2 (__const__ char *, int);
int _mkstemp (char *);
char *_mktemp (char *);
int _profil (void *, unsigned, unsigned, unsigned);
void *_brk (void *);

#endif


#if defined (__cplusplus)
}
#endif

#endif /* not _UNISTD_H */
