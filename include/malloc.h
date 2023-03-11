/* malloc.h (emx+gcc) */

#ifndef _MALLOC_H
#define _MALLOC_H

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


void *calloc (size_t, size_t);
void free (void *);
void *malloc (size_t);
void *realloc (void *, size_t);


#if (!defined (__STRICT_ANSI__) && !defined (_POSIX_SOURCE)) \
    || defined (_WITH_UNDERSCORE)

#if !defined (_HEAPOK)
#define _HEAPOK       0
#define _HEAPEMPTY    1
#define _HEAPBADBEGIN 2
#define _HEAPBADNODE  3
#define _HEAPBADEND   4
#define _HEAPBADROVER 5
#endif

void *_tcalloc (size_t, size_t);
void _tfree (void *);
int _theapmin (void);
void *_tmalloc (size_t);
void *_trealloc (void *, size_t);

void *_expand (void *, size_t);
int _heapchk (void);
int _heapmin (void);
int _heapset (unsigned);
int _heap_walk (int (*)(__const__ void *, size_t, int, int,
    __const__ char *, size_t));
size_t _msize (__const__ void *);

#endif


#if defined (__cplusplus)
}
#endif

#endif /* not _MALLOC_H */
