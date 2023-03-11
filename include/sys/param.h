/* sys/param.h (emx+gcc) */

#ifndef _SYS_PARAM_H
#define _SYS_PARAM_H

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (PAGE_SIZE)
#define PAGE_SIZE 0x1000
#endif

#if !defined (HZ)
#define HZ        100
#endif

#if !defined (MAXNAMLEN)
#define MAXNAMLEN  260
#endif

#if !defined (MAXPATHLEN)
#define MAXPATHLEN 260
#endif

/* Don't try to do this inline for now */

#if !defined (htonl)
#define htonl(X) _swapl(X)
#define ntohl(X) _swapl(X)
#define htons(X) _swaps(X)
#define ntohs(X) _swaps(X)
#endif

unsigned short _swaps (unsigned short _x);
unsigned long _swapl (unsigned long _x);

#if defined (__cplusplus)
}
#endif

#endif /* not _SYS_PARAM_H */
