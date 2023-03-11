/*
    fmutex.c

    Copyright (C) 1995,1996
	Rainer Schnitker, Heeper Str. 283, 33607 Bielefeld
	email: rainer@mathematik.uni-bielefeld.de

    All rights reserved
*/

#define WIN32_LEAN_AND_MEAN
#include <wingnuc.h>
#include <windows.h>
#include <winerror.h>
#include <stdlib.h>

#include <emx/syscalls.h>
#include <sys/builtin.h>
#include <sys/fmutex.h>
#include <sys/smutex.h>

extern __inline__ int is_rsxnt_loaded()
{
#define RUN_RSX 0x1000
    if (_emx_env & RUN_RSX) {
        if ((_emx_rev >> 16) == 2)  /* RSXNT */
            return 1;
    }
    return 0;
}

/****************************************************************************/
/*	    REPLACE \emx\src\lib\process\fmutex.c			    */
/****************************************************************************/

static char * x2s(void *p)
{
    static char hex[] = "0123456789abcdef";
    static char str[9];
    unsigned long v = (unsigned long) p;
    int i;

    strcpy (str, "--------");
    for (i = 0; i < 8; i++) {
	str[7 - i] = hex[v & 15];
	v >>= 4;
    }
    str[8] = 0;
    return str;
}

unsigned _fmutex_create (_fmutex *sem, unsigned flags)
{
    HANDLE h;

    sem->fs = _FMS_AVAILABLE;

    if (!is_rsxnt_loaded())
	return 0;

    h = CreateEvent (NULL, TRUE, FALSE, x2s(sem));

    sem->hev = (unsigned long) h;
    return (h) ? 0 : 1;
}

unsigned _fmutex_open (_fmutex *sem)
{
    HANDLE h;

    if (!is_rsxnt_loaded())
	return 0;

    h = OpenEvent (EVENT_ALL_ACCESS | EVENT_MODIFY_STATE |
		    SYNCHRONIZE, FALSE, x2s(sem));
    sem->hev = (unsigned long) h;

    return (h) ? 0 : 1;
}

unsigned _fmutex_close (_fmutex *sem)
{
    if (!is_rsxnt_loaded())
	return 0;

    return (CloseHandle ((HANDLE) sem->hev) == TRUE) ? 0 : 1;
}

unsigned __fmutex_request_internal (_fmutex *sem, unsigned flags,
				    signed char fs)
{
    if (fs == _FMS_UNINIT)
	return ERROR_INVALID_HANDLE;

    if (flags & _FMR_NOWAIT)
    {
	if (fs == _FMS_OWNED_HARD)
	{
	    if (__cxchg (&sem->fs, _FMS_OWNED_HARD) == _FMS_AVAILABLE)
		return 0;
	}
	return 1;
    }

    if (!is_rsxnt_loaded())
	return 0;

    for (;;)
    {
	if (ResetEvent ((HANDLE) sem->hev) == FALSE)
	{
            /* MessageBox (NULL, "fmutex request", x2s(sem), 0); */
	    return 1;
	}
	if (__cxchg (&sem->fs, _FMS_OWNED_HARD) == _FMS_AVAILABLE)
	    return 0;
	if (WaitForSingleObject((HANDLE) sem->hev, INFINITE) != WAIT_OBJECT_0)
	    return 1;
    }
    return 0;
}

unsigned __fmutex_release_internal (_fmutex *sem)
{
    if (!is_rsxnt_loaded())
	return 0;

    if (SetEvent ((HANDLE) sem->hev) == FALSE)
    {
        /* MessageBox (NULL, "fmutex release", x2s(sem), 0); */
	return 1;
    }
    Sleep(0);	/* switch thread */
    return 0;
}

void _fmutex_dummy (_fmutex *sem)
{
    sem->fs = _FMS_AVAILABLE;
    sem->hev = 0;
}
