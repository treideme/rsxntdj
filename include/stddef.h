/* stddef.h (emx+gcc) */

#ifndef _STDDEF_H
#define _STDDEF_H

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (_PTRDIFF_T)
#define _PTRDIFF_T
typedef long ptrdiff_t;
#endif

#if !defined (_SIZE_T)
#define _SIZE_T
typedef unsigned long size_t;
#endif

#if !defined (_WCHAR_T)
#define _WCHAR_T
typedef unsigned short wchar_t;
#endif

#if !defined (NULL)
#if defined (__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#define	offsetof(type, member)  ((size_t)&((type *)0)->member)


#if (!defined (__STRICT_ANSI__) && !defined (_POSIX_SOURCE)) \
    || defined (_WITH_UNDERSCORE)

unsigned *__threadid (void);
#define _threadid (__threadid ())

#endif

#if defined (__cplusplus)
}
#endif

#endif /* not _STDDEF_H */
