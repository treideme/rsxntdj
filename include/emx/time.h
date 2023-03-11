/* emx/time.h (emx+gcc) */

#ifndef _EMX_TIME_H
#define _EMX_TIME_H

#if defined (__cplusplus)
extern "C" {
#endif

#define _YEARS          (2106 - 1970 + 1)
#define TIME_T_MAX      0xffffffffUL

#if !defined (_TIME_T)
#define _TIME_T
typedef unsigned long time_t;
#endif

struct tm;

struct _tzinfo
{
  char tzname[4];
  char dstzname[4];
  int tz, dst, shift;
  int sm, sw, sd, st;
  int em, ew, ed, et;
};

extern int _tzset_flag;
extern struct _tzinfo _tzi;

extern int const _year_day[_YEARS+1];
extern int const _month_day_leap[];
extern int const _month_day_non_leap[];


int _day (int, int, int);
int _gmt2loc (unsigned long *);
int _loc2gmt (unsigned long *, int);
unsigned long _mktime (struct tm *);
void _compute_dst_table (void);


static __inline__ int _leap_year (unsigned y)
{
  return (y % 4 != 0 ? 0 : y % 100 != 0 ? 1 : y % 400 != 0 ? 0 : 1);
}


#if defined (__cplusplus)
}
#endif

#endif /* not _EMX_TIME_H */
