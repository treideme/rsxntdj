/* sys/select.h (emx+gcc) */

#ifndef _SYS_SELECT_H
#define _SYS_SELECT_H

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (FD_SETSIZE)
#define	FD_SETSIZE      256
#elif FD_SETSIZE < 256
#error FD_SETSIZE must be at least 256
#endif

#if !defined (_FD_SET_T)
#define _FD_SET_T

typedef struct _fd_set
{
  unsigned long fds_bits[(FD_SETSIZE+31) / 32];
} fd_set;

#endif

#define	FD_SET(n,s)    ((s)->fds_bits[(n)/32] |=  (1L << ((n) & 0x1f)))
#define	FD_CLR(n,s)    ((s)->fds_bits[(n)/32] &= ~(1L << ((n) & 0x1f)))
#define	FD_ISSET(n,s)  ((s)->fds_bits[(n)/32] &   (1L << ((n) & 0x1f)))
#define FD_ZERO(s)     (void)memset (s, 0, sizeof (*(s)))

struct timeval;

int select (int, struct _fd_set *, struct _fd_set *, struct _fd_set *,
    struct timeval *);

int _select (int, struct _fd_set *, struct _fd_set *, struct _fd_set *,
    struct timeval *);

void *memset (void *, int, size_t); /* Used by FD_ZERO */

#if defined (__cplusplus)
}
#endif

#endif /* not _SYS_SELECT_H */
