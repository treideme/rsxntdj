/* sys/wait.h (emx+gcc) */

#ifndef _SYS_WAIT_H
#define _SYS_WAIT_H

#if defined (__cplusplus)
extern "C" {
#endif

#define WNOHANG         1
#define WUNTRACED       2

#define WIFEXITED(st)   (((st) & 0x7f) == 0)
#define WIFSIGNALED(st) (((st) & 0x7f) != 0x7f && ((st) & 0x7f) != 0)
#define WIFSTOPPED(st)  (((st) & 0x7f) == 0x7f)

#define WEXITSTATUS(st) ((st) >> 8)
#define WTERMSIG(st)    ((st) & 0x7f)
#define WSTOPSIG(st)    ((st) >> 8)

int wait (int *);
int waitpid (int, int *, int);

#if !defined (_POSIX_SOURCE) || defined (_WITH_UNDERSCORE)

int _wait (int *);
int _waitpid (int, int *, int);

#endif

#if defined (__cplusplus)
}
#endif

#endif /* not SYS_WAIT_H */
