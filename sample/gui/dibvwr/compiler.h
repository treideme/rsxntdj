/* compiler.h, platform stuff. I always have a header like this when
 * dealing with multiple compilers etcs.
 *
 * Written by Alfons Hoogervorst, 1995-1997, proteus@worldaccess.nl.        */

/*
 * @DOC
 * @module compiler.h |
 * Compiler dependent settings; these settings should do for Windows
 * compilers lile MSVC++, Borland C++, Symantec ++ and the DJGPP/RSXNTDJ
 * package.
 * @index compiler.h | func
 */

#ifndef _AHX_COMPILER_H
#define _AHX_COMPILER_H

/* This header defines the following macros:
 *
 */

/* RSXNTDJ & Borland C++ */
/* @func | _WIN32, WIN32 | Win32 platform                                   */
#if defined(__WIN32__)
#   if !defined(_WIN32)
#       define _WIN32           1
#   endif
#   if !defined(WIN32)
#       define WIN32            1
#   endif
#endif

/* RSXNTDJ & Borland C++ */
/* @func | _WINDLL | Defined if compiling for DLLs                          */
#if defined(__DLL__)
#   if !defined(_WINDLL)
#       define _WINDLL          1
#   endif
#endif

/* RSXNTDJ & Borland C++ */
/* @func | _MT | Defined when using multithreaded RTLs                      */
#if defined(__MT__)
#   if !defined(_MT)
#       define _MT              1
#   endif
#endif

#if 0
/* RSXNTDJ & DJGPP headers are making some noise over size_t
 * refer to WINGNUC.H and DJGPP.H                                           */
#if defined(__RSXNT__) && defined(_WIN32)
#define _SIZE_T                 1
#endif
#endif

/* Pretty sure it's DJGPP. If we're using CPP, this conditional makes sure
 * that RC script files know about the used environment.                    */
/* @func | _GNUC_CPP | Defined when the GNUC preprocessor is in use         */
#if !defined(__DJGPP__) && defined(unix) && defined(GO32) && defined(MSDOS) && defined(i386)
#   ifndef _GNUC_CPP
#       define _GNUC_CPP        1
#   endif
#elif defined(__DJGPP__)
#   define _GNUC_CPP            1
#endif

/* For GNUC always assume we're ready for 4.0+ */
#if defined(__GNUC__)
#   if defined(WINVER)
#       undef WINVER
#   endif
#   define WINVER               0x0400
#   define __FUNC__             "unknown"
#endif

#endif /* !_AHX_COMPILER_H */
