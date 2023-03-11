/* emx/startup.h (emx+gcc) */

#ifndef _EMX_STARTUP_H
#define _EMX_STARTUP_H

#if defined (__cplusplus)
extern "C" {
#endif

/* argv[i][-1] contains some flag bits: */

#define _ARG_DQUOTE   0x01          /* Argument quoted (")                  */
#define _ARG_RESPONSE 0x02          /* Argument read from response file     */
#define _ARG_WILDCARD 0x04          /* Argument expanded from wildcard      */
#define _ARG_ENV      0x08          /* Argument from environment            */
#define _ARG_NONZERO  0x80          /* Always set, to avoid end of string   */

/* Arrange that FUN will be called by _startup(). */

#define _CRT_INIT1(fun) __asm__(".section .crtinit; .long _" #fun "; .section .text");

/* Arrange that FUN will be called by _cleanup(). */

#define _CRT_EXIT1(fun) __asm__(".section .crtexit; .long _" #fun "; .section .text");

extern void (*_atexit_v[64])(void);
extern int _atexit_n;

extern char ** _org_environ;

extern char _cdll_flag;

void _cleanup (void);

#if defined (__cplusplus)
}
#endif

#endif /* not _EMX_STARTUP_H */
