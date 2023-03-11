/* WinGnuC.c - Macros for GNU C Compiler to include Win32 SDK

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

#ifndef _WINGNUC_H
#define _WINGNUC_H

#ifdef __GNUC__

/* To speed up compile time, uncomment the next line */
/**/
#define WIN32_LEAN_AND_MEAN
/**/

#define _STDCALL_SUPPORTED              /* GNU C supports __stdcall */
#define NONAMELESSUNION                 /* union should have a name */

#define __cdecl                         /* Microsoft extentions */
#define _cdecl
#define __unaligned
#define __export
#define __stdcall __attribute__((stdcall))
#define __declspec(import)

#ifndef WIN32
#define WIN32 100
#endif
#ifndef _WIN32
#define _WIN32
#endif

#ifdef i386                             /* define target */
#define _X86_
#define I386_HOST       1
#ifndef _M_IX86
#define _M_IX86         300
#endif
#endif

#define _INTEGRAL_MAX_BITS 64
#define __int64 long long

#ifndef _WCHAR_T                        /* !EMX wchar_t */
#define _WCHAR_T
#define _WCHAR_T_DEFINED                /* SDK wchar_t */
typedef unsigned short wchar_t;
#else  /* _WCHAR_T */
#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
#endif
#endif /* _WCHAR_T */

#ifndef _SIZE_T                         /* !EMX Symbol */
#define _SIZE_T
#define _SIZE_T_DEFINED                 /* SDK Symbol */
typedef unsigned long size_t;
#else /* _SIZE_T */
#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
#endif
#endif

/* define missing structured exception handlers */
struct _EXCEPTION_RECORD;
struct _CONTEXT;
struct _RTL_CRITICAL_SECTION;
struct tagCREATESTRUCTA;
struct tagCREATESTRUCTW;

#endif /* __GNUC__ */

#endif /* _WINGNUC_H */
