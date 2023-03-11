/* strings.h (emx+gcc) */

#ifndef _STRINGS_H
#define _STRINGS_H

#include <string.h>

#if defined (__cplusplus)
extern "C" {
#endif

int  bcmp (__const__ void *, __const__ void *, size_t);
void bcopy (__const__ void *, void *, size_t);
void bzero (void *, size_t);
int ffs (int i);
char *index (__const__ char *, int);
char *rindex (__const__ char *, int);


#if defined (__cplusplus)
}
#endif

#endif /* not _STRINGS_H */
