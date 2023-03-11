/* glob.h (emx+gcc) */

#ifndef _GLOB_H
#define _GLOB_H

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (_SIZE_T)
#define _SIZE_T
typedef unsigned long size_t;
#endif

#define GLOB_APPEND     0x0001
#define GLOB_DOOFFS     0x0002
#define GLOB_ERR        0x0004
#define GLOB_MARK       0x0008
#define GLOB_NOCHECK    0x0010
#define GLOB_NOESCAPE   0x0020
#define GLOB_NOSORT     0x0040
#define GLOB_PERIOD     0x0080  /* POSIX.2? */

#define GLOB_ABEND      1
#define GLOB_NOMATCH    2
#define GLOB_NOSPACE    3

typedef struct
{
  /* Required by POSIX.2 */
  size_t gl_pathc;
  char **gl_pathv;
  size_t gl_offs;

  /* BSD */
  int gl_flags;

  /* Internal */
  size_t gl_alloc;
  int gl_reserved[3];
} glob_t;

int glob (__const__ char *, int, int (*)(__const__ char *, int), glob_t *);
void globfree (glob_t *);


#if !defined (_POSIX_C_SOURCE) || _POSIX_C_SOURCE >= 2
#define GLOB_MAGCHAR    0x0100
#endif


int _glob (__const__ char *, int, int (*)(__const__ char *, int), glob_t *);
void _globfree (glob_t *);


#if defined (__cplusplus)
}
#endif

#endif /* not _GLOB_H */
