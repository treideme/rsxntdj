/* sys/signal.h (emx+gcc) */

#ifndef _SYS_SIGNAL_H
#define _SYS_SIGNAL_H

#if defined (__cplusplus)
extern "C" {
#endif

typedef int sig_atomic_t;

#define SIGHUP    1 /* Hangup */
#define SIGINT    2 /* Interrupt (Ctrl-C) */
#define SIGQUIT   3 /* Quit */
#define SIGILL    4 /* Illegal instruction */
#define SIGTRAP   5 /* Single step (debugging) */
#define SIGABRT   6 /* abort () */
#define SIGEMT    7 /* EMT instruction */
#define SIGFPE    8 /* Floating point */
#define SIGKILL   9 /* Kill process */
#define SIGBUS   10 /* Bus error */
#define SIGSEGV  11 /* Segmentation fault */
#define SIGSYS   12 /* Invalid argument to system call */
#define SIGPIPE  13 /* Broken pipe */
#define SIGALRM  14 /* Alarm */
#define SIGTERM  15 /* Termination, process killed */
#define SIGUSR1  16 /* User-defined signal #1 */
#define SIGUSR2  17 /* User-defined signal #2 */
#define SIGCHLD  18 /* Death of a child process */
#define SIGBREAK 21 /* Break (Ctrl-Break) */
#define SIGWINCH 28 /* Window size change (not implemented) */

#define SIGPTRACENOTIFY 128     /* Notification from ptrace() */

#define SIGCLD   SIGCHLD

#define SIG_DFL ((void (*)(int))0)
#define SIG_IGN ((void (*)(int))1)
#define SIG_ERR ((void (*)(int))-1)

void (*signal (int, void (*)(int)))(int);
int raise (int);


#if !defined (__STRICT_ANSI__)

#define NSIG 29

#define SA_NOCLDSTOP    0x0001

#define SIG_BLOCK       1
#define SIG_UNBLOCK     2
#define SIG_SETMASK     3

#if !defined (_SIGSET_T)
#define _SIGSET_T
typedef unsigned long sigset_t;
#endif

struct sigaction
{
  void (*sa_handler)(int);
  sigset_t sa_mask;
  int sa_flags;
};


int kill (int, int);
int pause (void);

int sigaction (int, __const__ struct sigaction *, struct sigaction *);
int sigpending (sigset_t *);
int sigprocmask (int, __const__ sigset_t *, sigset_t *);
int sigsuspend (__const__ sigset_t *);

int sigaddset (sigset_t *, int);
int sigdelset (sigset_t *, int);
int sigemptyset (sigset_t *);
int sigfillset (sigset_t *);
int sigismember (__const__ sigset_t *, int);

#define _SIGMASK(sig) ((sigset_t)1 << ((sig) - 1))
#define __sigaddset(set,sig)   (*(set) |= _SIGMASK (sig), 0)
#define __sigdelset(set,sig)   (*(set) &= ~_SIGMASK (sig), 0)
#define __sigemptyset(set)     (*(set) = 0, 0)
#define __sigfillset(set)      (*(set) = ~(sigset_t)0, 0)
#define __sigismember(set,sig) ((*(set) & _SIGMASK (sig)) ? 1 : 0)

int _kill (int, int);
int _pause (void);

int _sigaction (int, __const__ struct sigaction *, struct sigaction *);
int _sigpending (sigset_t *);
int _sigprocmask (int, __const__ sigset_t *, sigset_t *);
int _sigsuspend (__const__ sigset_t *);

int _sigaddset (sigset_t *, int);
int _sigdelset (sigset_t *, int);
int _sigemptyset (sigset_t *);
int _sigfillset (sigset_t *);
int _sigismember (__const__ sigset_t *, int);

#endif


#if !defined (__STRICT_ANSI__) && !defined (_POSIX_SOURCE)

#define SIG_ACK ((void (*)(int))4)

#define SA_SYSV         0x0002  /* Reset to SIG_DFL */
#define SA_ACK          0x0004  /* Don't unblock automatically */

#define SIGTY void

#endif


#if defined (__cplusplus)
}
#endif

#endif /* not _SYS_SIGNAL_H */
