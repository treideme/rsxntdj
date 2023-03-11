/* ulimit.h (emx+gcc) */

#ifndef _ULIMIT_H
#define _ULIMIT_H

#include <sys/ulimit.h>

#if defined (__cplusplus)
extern "C" {
#endif

long ulimit (int, ...);

long _ulimit (int, ...);

#if defined (__cplusplus)
}
#endif

#endif /* not _ULIMIT_H */
