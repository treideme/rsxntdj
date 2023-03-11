/* sys/utime.h (emx+gcc) */

#ifndef _SYS_UTIME_H
#define _SYS_UTIME_H

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (_TIME_T)
#define _TIME_T
typedef unsigned long time_t;
#endif

#if !defined (_UTIMBUF)
#define _UTIMBUF
struct utimbuf
{
  time_t actime;
  time_t modtime;
};
#endif

int utime (__const__ char *, __const__ struct utimbuf *);

int _utime (__const__ char *, __const__ struct utimbuf *);

#if defined (__cplusplus)
}
#endif

#endif /* not _SYS_UTIME_H */
