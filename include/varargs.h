/* varargs.h (emx+gcc) */

#ifndef _VARARGS_H
#define _VARARGS_H

#if !defined (NULL)
#if defined (__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#define _VA_LIST

#define _VA_ROUND(type) ((sizeof (type) + 3) & -4)

#define va_alist __builtin_va_alist
#define va_dcl int __builtin_va_alist;
#define va_list char *

#define va_start(alist) alist = (char *)&__builtin_va_alist
#define va_end(alist) (alist = 0, (void)0)
#define __std_va_arg(alist,t) (alist += _VA_ROUND (t), \
                               *((t *)(alist - _VA_ROUND (t))))

#ifdef __BOUNDS_CHECKING_ON
#include <fix-args.h>
#else
#define va_arg(alist,t) __std_va_arg(alist,t)
#endif

#endif /* not _VARARGS_H */
