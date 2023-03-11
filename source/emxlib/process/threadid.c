/*
    gettid.c -  replaces gettid() call in the emx library

    Copyright (C) 1995,1996
	Rainer Schnitker, Heeper Str. 283, 33607 Bielefeld
	email: rainer@mathematik.uni-bielefeld.de

    All rights reserved
*/

#include <emx/syscalls.h>
#include <stdlib.h>

#define WIN32_LEAN_AND_MEAN
#include <wingnuc.h>
#include <windows.h>

extern __inline__ int is_rsxnt_loaded()
{
#define RUN_RSX 0x1000
    if (_emx_env & RUN_RSX) {
        if ((_emx_rev >> 16) == 2)  /* RSXNT */
            return 1;
    }
    return 0;
}

int __threadid(void)
{
    if (!is_rsxnt_loaded())
	return 1;
    else
	return GetCurrentThreadId();
}
