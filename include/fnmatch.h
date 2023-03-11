/* fnmatch.h (emx+gcc) */

#ifndef _FNMATCH_H
#define _FNMATCH_H

#if defined (__cplusplus)
extern "C" {
#endif

/* POSIX.2 */

#define FNM_NOMATCH        1

#define FNM_NOESCAPE       16
#define FNM_PATHNAME       32
#define FNM_PERIOD         64

int fnmatch (__const__ char *, __const__ char *, int);


#if !defined (_POSIX_SOURCE) || defined (_WITH_UNDERSCORE)

/* emx extensions */

#define _FNM_MATCH         0
#define _FNM_ERR           2

#define _FNM_STYLE_MASK    15

#define _FNM_POSIX         0
#define _FNM_OS2           1
#define _FNM_DOS           2

#define _FNM_IGNORECASE    128
#define _FNM_PATHPREFIX    256

int _fnmatch (__const__ char *, __const__ char *, int);

#endif


#if defined (__cplusplus)
}
#endif

#endif /* not _FNMATCH_H */
