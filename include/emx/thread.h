/* emx/thread.h (emx+gcc) */

#ifndef _EMX_THREAD_H
#define _EMX_THREAD_H

#if defined (__cplusplus)
extern "C" {
#endif

#if defined (__MT__)

#if !defined (_TM)
#define _TM
struct tm         /* cf. <time.h> */
{
  int tm_sec;     /* 0..59 */
  int tm_min;     /* 0..59 */
  int tm_hour;    /* 0..23 */
  int tm_mday;    /* 1..31 */
  int tm_mon;     /* 0..11 */
  int tm_year;    /* 0(:=1900).. */
  int tm_wday;    /* 0..6 */
  int tm_yday;    /* 0..365 */
  int tm_isdst;   /* 0 */
};
#endif

struct _uheap;

struct _thread
{
  int             _th_errno;                /* comes first, cf. errnofun.s */
  void          * _th_arg;
  void          (*_th_start)(void *);
  unsigned char * _th_strtok_ptr;
  char            _th_asctime_buf[26+2];    /* 2 chars for padding */
  char            _th_tmpnam_buf[16];       /* cf. stdio.h */
  struct tm       _th_gmtime_buf;
  unsigned int    _th_rand;                 /* Used by rand() */
  void          * _th_store;                /* Pointer to user data */
  int             _th_mblen_shift;          /* Shift state for mblen() */
  int             _th_mbtowc_shift;         /* Shift state for mbtowc() */
  int             _th_wctomb_shift;         /* Shift state for wctomb() */
  char            _th_vollabel[12];         /* Used by _getvol() */
  char            _th_error[28];            /* Used by strerror() */
  struct _uheap * _th_rheap;                /* Default regular heap */
  struct _uheap * _th_theap;                /* Default tiled heap */
  char            _th_ttyname[32];          /* Used by ttyname() */
  char            _th_inetntoa[16];         /* Used by inetntoa() */
  int             _th_reserved[971];        /* 4096 bytes, total */
};

struct _thread *_thread (void);

#endif /* defined (__MT__) */


#if defined (__cplusplus)
}
#endif

#endif /* not _EMX_THREAD_H */
