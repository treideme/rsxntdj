/* LibMain.c - dummy DLL LibMain() if the program has not one

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
#define NOGDI
#define NOKERNEL
#define NOUSER
#include <windows.h>

BOOL APIENTRY LibMain(HANDLE hInst, DWORD fdwReason, LPVOID lpReserved)
{
    return TRUE;
}
