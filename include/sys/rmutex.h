/* sys/rmutex.h (emx+gcc) */

/* _rmutex semaphores are registered _fmutex semaphores.  They are a
   bit bigger than _fmutex metaphores but they are inherited by child
   processes created with fork().  Shared _rmutex semaphores behave
   like _fmutex semaphores, ie, they are not registered and therefore
   not inherited by child processes created with fork().  (As malloc()
   uses _rmutex semaphores, we have to support shared semaphores
   anyway.) */

/* This header requires <sys/builtin.h> and <sys/fmutex.h>. */

#ifndef _SYS_RMUTEX_H
#define _SYS_RMUTEX_H

#if defined (__cplusplus)
extern "C" {
#endif

/* See also <emx/io.h> and /emx/test/internal.c. */
typedef struct __rmutex
{
  struct __rmutex *next;
  struct __rmutex *prev;
  _fmutex fm;
  unsigned char flags;
  unsigned short count;
} _rmutex;


static __inline__ unsigned _rmutex_request (_rmutex *sem, unsigned flags)
{
  return _fmutex_request (&sem->fm, flags);
}


static __inline__ unsigned _rmutex_release (_rmutex *sem)
{
  return _fmutex_release (&sem->fm);
}


static __inline__ int _rmutex_available (_rmutex *sem)
{
  return _fmutex_available (&sem->fm);
}


unsigned _rmutex_close (_rmutex *);
unsigned _rmutex_create (_rmutex *, unsigned);
unsigned _rmutex_open (_rmutex *);
void _rmutex_dummy (_rmutex *);


static __inline__ void _rmutex_checked_release (_rmutex *sem)
{
  _fmutex_checked_release (&sem->fm);
}


static __inline__ void _rmutex_checked_request (_rmutex *sem, unsigned flags)
{
  _fmutex_checked_request (&sem->fm, flags);
}


void _rmutex_checked_close (_rmutex *);
void _rmutex_checked_create (_rmutex *, unsigned);
void _rmutex_checked_open (_rmutex *);

#if defined (__cplusplus)
}
#endif

#endif /* not _SYS_RMUTEX_H */
