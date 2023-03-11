/*
    thread.c -	replaces _thread() call in the emx library

    Copyright (C) 1995,1996
	Rainer Schnitker, Heeper Str. 283, 33607 Bielefeld
	email: rainer@mathematik.uni-bielefeld.de

    All rights reserved
*/

#include <emx/syscalls.h>
#include <emx/thread.h>

#define WIN32_LEAN_AND_MEAN
#include <wingnuc.h>
#include <windows.h>
#include <winerror.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define RUN_RSX 0x1000

#ifdef __MT__

struct _thread __thread_1 = {
  0,	    /* _th_errno */
  NULL,     /* _th_arg */
  NULL,     /* _th_start */
  NULL,     /* _th_strtok_ptr (must be NULL) */
  {0},	    /* _th_asctime_buf */
  {0},	    /* _th_tmpnam_buf */
  {0},	    /* _th_gmtime_buf */
  1,	    /* _th_rand */
  NULL,     /* _th_store */
  0,	    /* _th_mblen_shift */
  0,	    /* _th_mbtowc_shift */
  0,	    /* _th_wctomb_shift */

	    /* emx 0.9c */
  "",                           /* _th_vollabel */
  "",                           /* _th_error */
  NULL, 			/* _th_rheap */
  NULL, 			/* _th_theap */
  ""                            /* _th_ttyname */
};

unsigned long __ThreadIndex = -1;   /* Win32 Tlsalloc value */

int __thread_init()
{
    static int runtime = 0;    /* rsxnt or dos runtime */

    if (!runtime)  // init
    {
	if (_emx_env & RUN_RSX) {	/* rsx software is running */

	    if ((_emx_rev >> 16) == 2)	/* 0=rsx, 1=rsxwin, 2=rsxnt */
	    {
		runtime = 2;
		if ((__ThreadIndex = TlsAlloc()) == 0xffffffff)
		    ExitProcess(2);
		else
		    TlsSetValue(__ThreadIndex, &__thread_1);
	    }
	    else
		runtime = 1;
	}
	else
	    runtime = 1;
    }

    return (runtime - 1);
}

struct _thread * _thread(void)
{
    if (!__thread_init())
	return &__thread_1;
    else
	return (struct _thread *) TlsGetValue(__ThreadIndex);
}

#endif
