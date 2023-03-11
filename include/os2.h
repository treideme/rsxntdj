/* os2.h (emx+gcc) */

#ifndef _OS2_H
#define _OS2_H

#if defined (__cplusplus)
extern "C" {
#endif

#define _Cdecl
#define _Far16
#define _Optlink
#define _Pascal
#define _Seg16
#define _System

#if defined (USE_OS2_TOOLKIT_HEADERS)
#include <os2tk.h>
#else
#include <os2emx.h>          /* <-- change this line to use Toolkit headers */
#endif
#include <os2thunk.h>

#if defined (__cplusplus)
}
#endif

#endif /* not _OS2_H */
