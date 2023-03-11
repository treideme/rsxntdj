/*
    _errno.c -  replaces _errno() call in the emx library

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
#include <errno.h>

#ifdef __MT__

int * _errno_fun(void)
{
    return &((_thread())->_th_errno);
}

int * _errno(void)
{
    return &((_thread())->_th_errno);
}

#else

int * _errno(void)
{
    return & errno;
}

#endif
