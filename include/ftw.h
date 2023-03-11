/* ftw.h (emx+gcc) */

#ifndef _FTW_H
#define _FTW_H

#if defined (__cplusplus)
extern "C" {
#endif

#define FTW_F           0
#define FTW_D           1
#define FTW_DNR         2
#define FTW_NS          3

int ftw (__const__ char *,
    int (*)(__const__ char *, __const__ struct stat *, int),
    int);

#if defined (__cplusplus)
}
#endif

#endif /* not _FTW_H */
