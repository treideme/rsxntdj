/* sigsysv.c (emx+gcc) -- Copyright (c) 1994-1996 by Eberhard Mattes */

#include <sys/uflags.h>

static void sigsysv (void)
{
  _uflags (_UF_SIG_MODEL, _UF_SIG_SYSV);
}

__asm__(".section .ctor; .long _sigsysv; .section .text");
