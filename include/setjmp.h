/* setjmp.h (emx+gcc) */

#ifndef _SETJMP_H
#define _SETJMP_H

#if defined (__cplusplus)
extern "C" {
#endif

/* ANSI X3.159-1989 */

typedef int jmp_buf[12];

int setjmp (jmp_buf);
void longjmp (jmp_buf, int) __attribute__ ((__noreturn__));


#if !defined (__STRICT_ANSI__)

/* POSIX.1 */

typedef int sigjmp_buf[14];

int sigsetjmp (sigjmp_buf, int);
void siglongjmp (sigjmp_buf, int) __attribute__ ((__noreturn__));

#endif


#if defined (__cplusplus)
}
#endif

#endif /* not _SETJMP_H */
