/* sigbsd.c (emx+gcc) -- Copyright (c) 1994-1996 by Eberhard Mattes */

#include <sys/uflags.h>

static void sigbsd (void)
{
  _uflags (_UF_SIG_MODEL, _UF_SIG_BSD);
}

__asm__(".section .ctor; .long _sigbsd; .section .text");
