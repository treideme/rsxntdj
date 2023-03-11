/*
    GetEnv.c - Defines getenv() for DLL's without C-runtime

    Copyright (C) 1995,1996
	Rainer Schnitker, Heeper Str. 283, 33607 Bielefeld
	email: rainer@mathematik.uni-bielefeld.de

    All rights reserved
*/
#ifdef __GNUC__
#include <wingnuc.h>
#endif

#define WIN32_LEAN_AND_MEAN
#define STRICT
#define NOGDI
#include <windows.h>
#include <malloc.h>

char * getenv(const char *name)
{
    DWORD len;
    TCHAR *mem;
    TCHAR buf[4];

    if ((len = GetEnvironmentVariable(name, buf, sizeof(buf))) == 0)
        return NULL;

    mem = HeapAlloc (GetProcessHeap(), 0, (len + 1) * sizeof(TCHAR));

    if (!mem)
        return NULL;

    len = GetEnvironmentVariable(name, mem, len + 1);
    mem[len] = 0;

    return mem;
}
