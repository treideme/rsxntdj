/* sys/time.h (emx+gcc) */

#ifndef _SYS_TIME_H
#define _SYS_TIME_H

#include <time.h>

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (_TIMEVAL)
#define _TIMEVAL
struct timeval
{
  long tv_sec;
  long tv_usec;
};
#endif

#if !defined (_TIMEZONE)
#define _TIMEZONE
struct timezone
{
  int tz_minuteswest;
  int tz_dsttime;
};
#endif

int utimes (__const__ char *, __const__ struct timeval *);
int gettimeofday (struct timeval *, struct timezone *);
int settimeofday (__const__ struct timeval *, __const__ struct timezone *);


int _utimes (__const__ char *, __const__ struct timeval *);
int _gettimeofday (struct timeval *, struct timezone *);
int _settimeofday (__const__ struct timeval *, __const__ struct timezone *);

#if defined (__cplusplus)
}
#endif

#endif /* not _SYS_TIME_H */
