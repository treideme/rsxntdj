/* sys/fmutex.h (emx+gcc) */

/* Fast mutex semaphores. */

/* This header requires <sys/builtin.h>. */

#ifndef _SYS_FMUTEX_H
#define _SYS_FMUTEX_H

#if defined (__cplusplus)
extern "C" {
#endif

/* Constants for _fmutex.fs.  See _fmutex_available() for ordering. */

#define _FMS_UNINIT       0
#define _FMS_AVAILABLE    1
#define _FMS_OWNED_SIMPLE 2
#define _FMS_OWNED_HARD   3

/* Constants for _fmutex_create() */

#define _FMC_SHARED     0x01

/* Constants for _fmutex_request() */

#define _FMR_IGNINT     0x01
#define _FMR_NOWAIT     0x02

/* We cannot use __attribute__ ((__packed__)) because G++ does not
   support this. */

#pragma pack(1)
typedef struct
{
  unsigned long hev;            /* HEV */
  __volatile__ signed char fs;  /* Status */
} _fmutex;
#pragma pack()


unsigned __fmutex_request_internal (_fmutex *, unsigned, signed char);
unsigned __fmutex_create_internal (_fmutex *, unsigned);
unsigned __fmutex_release_internal (_fmutex *);


static __inline__ unsigned _fmutex_request (_fmutex *sem, unsigned flags)
{
  signed char fs;

  fs = __cxchg (&sem->fs, _FMS_OWNED_SIMPLE);
  if (fs == _FMS_AVAILABLE)
    return 0;
  else
    return __fmutex_request_internal (sem, flags, fs);
}


static __inline__ unsigned _fmutex_release (_fmutex *sem)
{
  signed char fs;

  fs = __cxchg (&sem->fs, _FMS_AVAILABLE);
  if (fs == _FMS_OWNED_HARD)
    return __fmutex_release_internal (sem);
  else
    return 0;
}


static __inline__ int _fmutex_available (_fmutex *sem)
{
  return sem->fs <= _FMS_AVAILABLE;
}


unsigned _fmutex_create (_fmutex *, unsigned);
unsigned _fmutex_open (_fmutex *);
unsigned _fmutex_close (_fmutex *);
void _fmutex_dummy (_fmutex *);

void _fmutex_checked_close (_fmutex *);
void _fmutex_checked_create (_fmutex *, unsigned);
void _fmutex_checked_open (_fmutex *);
void _fmutex_checked_release (_fmutex *);
void _fmutex_checked_request (_fmutex *, unsigned);

#if defined (__cplusplus)
}
#endif

#endif /* not _SYS_FMUTEX_H */
