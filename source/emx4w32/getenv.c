/* GetEnv.c - Defines getenv() for DLL's without C-runtime

   Copyright (c) 1995-1999 Rainer Schnitker

   This file is part of RSXNT.

   RSXNT is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   RSXNT is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with RSXNT; see the file COPYING.  If not, write to
   the Free Software Foundation, 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA. */

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
