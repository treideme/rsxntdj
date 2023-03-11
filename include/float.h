/* float.h (emx+gcc) */

#ifndef _FLOAT_H
#define _FLOAT_H

#if defined (__cplusplus)
extern "C" {
#endif

#define DBL_RADIX       2
#define DBL_MANT_DIG    53
#define DBL_MIN_EXP     (-1021)
#define DBL_MAX_EXP     1024
#define DBL_DIG         15
#define DBL_MIN_10_EXP  (-307)
#define DBL_MAX_10_EXP  308
#define DBL_MIN         2.2250738585072014e-308
#define DBL_MAX         1.7976931348623158e+308
#define DBL_EPSILON     2.2204460492503131e-016
#define DBL_ROUNDS      1

#define FLT_RADIX       2
#define FLT_MANT_DIG    24
#define FLT_MIN_EXP     (-125)
#define FLT_MAX_EXP     128
#define FLT_DIG         6
#define FLT_MIN_10_EXP  (-37)
#define FLT_MAX_10_EXP  38
#define FLT_MIN         1.17549435e-38F
#define FLT_MAX         3.40282346e+38F
#define FLT_EPSILON     1.19209290e-07F
#define FLT_ROUNDS      1

#define LDBL_RADIX      2
#define LDBL_MANT_DIG   64
#define LDBL_MIN_EXP    (-16381)
#define LDBL_MAX_EXP    16384
#define LDBL_DIG        18
#define LDBL_MIN_10_EXP (-4931)
#define LDBL_MAX_10_EXP 4932
#define LDBL_MIN        3.3621031431120935063e-4932L
#define LDBL_MAX        1.1897314953572317650e+4932L
#define LDBL_EPSILON    1.08420217248550443400745280086994171142578125e-0019L
#define LDBL_ROUNDS     1

#if !defined (__STRICT_ANSI__) && !defined (_POSIX_SOURCE)

#define M_E             2.71828182845904523536
#define M_LOG2E         1.44269504088896340736
#define M_LOG10E        0.434294481903251827651
#define M_LN2           0.693147180559945309422
#define M_LN10          2.302585092994045684018

#define M_PI            3.14159265358979323846
#define M_PI_2          1.57079632679489661923
#define M_PI_4          0.785398163397448309616
#define M_1_PI          0.318309886183790671538
#define M_2_PI          0.636619772367581343076
#define M_2_SQRTPI      1.12837916709551257390

#define M_SQRT2         1.41421356237309504880
#define M_SQRT1_2       0.707106781186547524401

#if !defined (_OMIT_387_STUFF)

#define MCW_EM                  0x003f
#define EM_INVALID              0x0001
#define EM_DENORMAL             0x0002
#define EM_ZERODIVIDE           0x0004
#define EM_OVERFLOW             0x0008
#define EM_UNDERFLOW            0x0010
#define EM_INEXACT              0x0020

#define MCW_IC                  0x1000
#define IC_PROJECTIVE           0x0000
#define IC_AFFINE               0x1000

#define MCW_RC                  0x0c00
#define RC_NEAR                 0x0000
#define RC_DOWN                 0x0400
#define RC_UP                   0x0800
#define RC_CHOP                 0x0c00

#define MCW_PC                  0x0300
#define PC_24                   0x0000
#define PC_53                   0x0200
#define PC_64                   0x0300

#define CW_DEFAULT              (RC_NEAR | PC_64 | MCW_EM)

#define SW_INVALID              0x0001
#define SW_DENORMAL             0x0002
#define SW_ZERODIVIDE           0x0004
#define SW_OVERFLOW             0x0008
#define SW_UNDERFLOW            0x0010
#define SW_INEXACT              0x0020
#define SW_STACKFAULT           0x0040
#define SW_STACKOVERFLOW        0x0200

unsigned _clear87 (void);
unsigned _control87 (unsigned, unsigned);
void _fpreset (void);
unsigned _status87 (void);

#endif /* !defined (_OMIT_387_STUFF) */
#endif


#if defined (__cplusplus)
}
#endif

#endif /* not _FLOAT_H */
