/* stdarg.h (emx+gcc) */

#ifndef _STDARG_H
#define _STDARG_H

#if !defined (_VA_LIST)
#define _VA_LIST
typedef char *va_list;
#endif

#define _VA_ROUND(t) ((sizeof (t) + 3) & -4)

#if !defined (va_start)
#define va_start(ap,v) ap = (va_list)&v + ((sizeof (v) + 3) & -4)
#define va_end(ap) (ap = 0, (void)0)
#define __std_va_arg(ap,t) (ap += _VA_ROUND (t), *(t *)(ap - _VA_ROUND (t)))
#endif

#ifdef __BOUNDS_CHECKING_ON
#include <fix-args.h>
#else
#define va_arg(ap,t) __std_va_arg(ap,t)
#endif

#endif /* not _STDARG_H */
