/* sys/process.h (emx+gcc) */

#ifndef _SYS_PROCESS_H
#define _SYS_PROCESS_H

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (P_WAIT)
#define P_WAIT    0
#define P_NOWAIT  1
#define P_OVERLAY 2
#define P_DEBUG   3
#define P_SESSION 4
#define P_DETACH  5
#define P_PM      6

#define P_DEFAULT    0x0000
#define P_MINIMIZE   0x0100
#define P_MAXIMIZE   0x0200
#define P_FULLSCREEN 0x0300
#define P_WINDOWED   0x0400

#define P_FOREGROUND 0x0000
#define P_BACKGROUND 0x1000

#define P_NOCLOSE    0x2000
#define P_NOSESSION  0x4000

/* Note: 0x8000 is used internally. */

#define P_QUOTE      0x10000
#define P_TILDE      0x20000
#define P_UNRELATED  0x40000
#define P_DEBUGDESC  0x80000

#endif

void abort (void)  __attribute__ ((__noreturn__));
int atexit (void (*)(void));
int execl (__const__ char *, __const__ char *, ...);
int execle (__const__ char *, __const__ char *, ...);
int execlp (__const__ char *, __const__ char *, ...);
int execlpe (__const__ char *, __const__ char *, ...);
int execv (__const__ char *, char * __const__ *);
int execve (__const__ char *, char * __const__ *, char * __const__ *);
int execvp (__const__ char *, char * __const__ *);
int execvpe (__const__ char *, char * __const__ *, char * __const__ *);
void exit (int) __attribute__ ((__noreturn__));
void _exit (int) __attribute__ ((__noreturn__));
int fork (void);
int getpid (void);
int getppid (void);
int spawnl (int, __const__ char *, __const__ char *, ...);
int spawnle (int, __const__ char *, __const__ char *, ...);
int spawnlp (int, __const__ char *, __const__ char *, ...);
int spawnlpe (int, __const__ char *, __const__ char *, ...);
int spawnv (int, __const__ char *, char * __const__ *);
int spawnve (int, __const__ char *, char * __const__ *, char * __const__ *);
int spawnvp (int, __const__ char *, char * __const__ *);
int spawnvpe (int, __const__ char *, char * __const__ *, char * __const__ *);
int system (__const__ char *);
int wait (int *);
int waitpid (int, int *, int);

int _execl (__const__ char *, __const__ char *, ...);
int _execle (__const__ char *, __const__ char *, ...);
int _execlp (__const__ char *, __const__ char *, ...);
int _execlpe (__const__ char *, __const__ char *, ...);
int _execv (__const__ char *, char * __const__ *);
int _execve (__const__ char *, char * __const__ *, char * __const__ *);
int _execvp (__const__ char *, char * __const__ *);
int _execvpe (__const__ char *, char * __const__ *, char * __const__ *);
int _fork (void);
int _getpid (void);
int _getppid (void);
int _spawnl (int, __const__ char *, __const__ char *, ...);
int _spawnle (int, __const__ char *, __const__ char *, ...);
int _spawnlp (int, __const__ char *, __const__ char *, ...);
int _spawnlpe (int, __const__ char *, __const__ char *, ...);
int _spawnv (int, __const__ char *, char * __const__ *);
int _spawnve (int, __const__ char *, char * __const__ *, char * __const__ *);
int _spawnvp (int, __const__ char *, char * __const__ *);
int _spawnvpe (int, __const__ char *, char * __const__ *, char * __const__ *);
int _wait (int *);
int _waitpid (int, int *, int);


#if defined (__cplusplus)
}
#endif

#endif /* not _SYS_PROCESS_H */
