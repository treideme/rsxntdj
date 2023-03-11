/*
	windows.h - main header file for the Win32 API

	Written by Anders Norlander <anorland@hem2.passagen.se>

	This file is part of a free library for the Win32 API.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*/
#ifndef _WINDOWS_H
#define _WINDOWS_H

#if defined(__i386__) && !defined(_M_IX86)
#define _M_IX86 300
#endif
#if !defined(_X86_) && defined(_M_IX86)
#define _X86_ M_IX86
#endif
#if !defined(i386) && defined(_M_IX86)
#define i386
#endif

#ifdef RC_INVOKED
/* winresrc.h includes the necessary headers */
#include <winresrc.h>
#else

#ifdef __GNUC__
/* Nameless unions are supported in G++ */
#if defined(__cplusplus) && !defined(NONAMELESSUNION)
#define _ANONYMOUS_UNION
#endif
#elif defined(_MSC_VER) || defined(__LCC__)
/* MSVC and LCC-Win32 support nameless unions and structs */
#ifndef NONAMELESSUNIUN
#define _ANONYMOUS_UNION
#endif
#ifndef NONAMELESSSTRUCT
#define _ANONYMOUS_STRUCT
#endif
#elif defined(__BORLANDC__)
/* BC 5.01 support nameless unions in C/C++ and
   nameless structs in C++ */
#ifndef NONAMELESSUNIUN
#define _ANONYMOUS_UNION
#endif
#if defined(__cplusplus) && !defined(NONAMELESSSTRUCT)
#define _ANONYMOUS_STRUCT
#pragma anon_struct on
#endif
#endif

#ifndef _ANONYMOUS_UNION
#define _UNION_NAME(x) x
#define DUMMYUNIONNAME	u
#define DUMMYUNIONNAME2	u2
#define DUMMYUNIONNAME3	u3
#define DUMMYUNIONNAME4	u4
#define DUMMYUNIONNAME5	u5
#else
#define _UNION_NAME(x)
#define DUMMYUNIONNAME
#define DUMMYUNIONNAME2
#define DUMMYUNIONNAME3
#define DUMMYUNIONNAME4
#define DUMMYUNIONNAME5
#endif
#ifndef _ANONYMOUS_STRUCT
#define _STRUCT_NAME(x) x
#define DUMMYSTRUCTNAME	s
#define DUMMYSTRUCTNAME2 s2
#define DUMMYSTRUCTNAME3 s3
#else
#define _STRUCT_NAME(x)
#define DUMMYSTRUCTNAME
#define DUMMYSTRUCTNAME2
#define DUMMYSTRUCTNAME3
#endif

#include <stdarg.h>
#include <windef.h>
#include <wincon.h>
#include <basetyps.h>
#include <excpt.h>
#include <winbase.h>
#include <wingdi.h>
#include <winuser.h>
#include <winnls.h>
#include <winver.h>
#include <winnetwk.h>
#include <winreg.h>
#include <winsvc.h>

#ifndef WIN32_LEAN_AND_MEAN
#include <commdlg.h>
#include <cderr.h>
#include <dde.h>
#include <ddeml.h>
#include <dlgs.h>
#include <lzexpand.h>
#include <nb30.h>
#include <rpc.h>
#include <shellapi.h>
#include <winperf.h>
#include <winspool.h>
#if defined(Win32_Winsock) || !(defined(__INSIDE_CYGWIN__) || defined(__CYGWIN_) || defined(__CYGWIN32__))
#include <winsock.h>
#endif
#endif /* WIN32_LEAN_AND_MEAN */

#endif

#ifdef __OBJC__
/* FIXME: Not undefining BOOL here causes all BOOLs to be WINBOOL (int),
   but undefining it causes trouble as well.
*/
#if 0
#undef BOOL
#endif
#endif

#endif
