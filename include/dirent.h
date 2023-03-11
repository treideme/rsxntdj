/* dirent.h (emx+gcc) */

#ifndef _DIRENT_H
#define _DIRENT_H

#if !defined (_SYS_TYPES_H)
#warning <dirent.h> requires <sys/types.h>
#include <sys/types.h>
#endif

#include <sys/dirent.h>

#if defined (__cplusplus)
extern "C" {
#endif

struct _dirdesc;

typedef struct _dirdesc DIR;

DIR *opendir (__const__ char *);
struct dirent *readdir (DIR *);
int closedir (DIR *);
void rewinddir (DIR *);

#if !defined (_POSIX_SOURCE)
void seekdir (DIR *, long);
long telldir (DIR *);
#endif

DIR *_opendir (__const__ char *);
struct dirent *_readdir (DIR *);
void _seekdir (DIR *, long);
long _telldir (DIR *);
int _closedir (DIR *);
void _rewinddir (DIR *);

#if defined (__cplusplus)
}
#endif

#endif /* not _DIRENT_H */
