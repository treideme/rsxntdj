/* memory.h (emx+gcc) */

#ifndef _MEMORY_H
#define _MEMORY_H

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (_SIZE_T)
#define _SIZE_T
typedef unsigned long size_t;
#endif

#if !defined (NULL)
#if defined (__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#if !defined (_MEMDIF_EQ)
#define _MEMDIF_EQ 0xffffffff
#endif

void *memccpy (void *, __const__ void *, int, size_t);
void *memchr (__const__ void *, int, size_t);
int memcmp (__const__ void *, __const__ void *, size_t);
void *memcpy (void *, __const__ void *, size_t);
int memicmp (__const__ void *, __const__ void *, size_t);
void *memmove (void *, __const__ void *, size_t);
void *memset (void *s, int, size_t);

size_t _memcount (__const__ void *, int, size_t);
size_t _memdif (__const__ void *, __const__ void *, size_t);
void *_memrchr (__const__ void *, int, size_t);
void _memswap (void *, void *, size_t);

#if defined (__cplusplus)
}
#endif

#endif /* not _MEMORY_H */
