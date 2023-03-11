/* limits.h (emx+gcc) */

#ifndef _LIMITS_H
#define _LIMITS_H

#define CHAR_BIT      8
#define SCHAR_MIN   (-128)
#define SCHAR_MAX     127
#define UCHAR_MAX     0xffU
#if defined (__CHAR_UNSIGNED__)
#define CHAR_MIN      0
#define CHAR_MAX      UCHAR_MAX
#else
#define CHAR_MIN      SCHAR_MIN
#define CHAR_MAX      SCHAR_MAX
#endif
#define MB_LEN_MAX    6
#define SHRT_MIN    (-32768)
#define SHRT_MAX      32767
#define USHRT_MAX     0xffffU
#define LONG_MIN    (-0x7fffffffL-1L)
#define LONG_MAX      0x7fffffffL
#define ULONG_MAX     0xffffffffUL
#define INT_MIN     (-0x7fffffff-1)
#define INT_MAX       0x7fffffff
#define UINT_MAX      0xffffffffU


#if !defined (__STRICT_ANSI__)

#define _POSIX_ARG_MAX          4096
#define _POSIX_CHILD_MAX        6
#define _POSIX_LINK_MAX         8
#define _POSIX_MAX_CANON        255
#define _POSIX_MAX_INPUT        255
#define _POSIX_NAME_MAX         14
#define _POSIX_NGROUPS_MAX      0
#define _POSIX_OPEN_MAX         16
#define _POSIX_PATH_MAX         255
#define _POSIX_PIPE_BUF         512
#define _POSIX_SSIZE_MAX        32767
#define _POSIX_STREAM_MAX       8
#define _POSIX_TZNAME_MAX       3

#define	NGROUPS_MAX             0

#define SSIZE_MAX               INT_MAX

#endif


#if !defined (__STRICT_ANSI__) && !defined (_POSIX_SOURCE)

#define WORD_BIT        32
#define USI_MAX         UINT_MAX

#define LONG_LONG_MIN   (-0x7fffffffffffffffLL-1LL)
#define LONG_LONG_MAX     0x7fffffffffffffffLL
#define ULONG_LONG_MAX    0xffffffffffffffffULL

#endif

#endif /* not _LIMITS_H */
