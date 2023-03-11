/* math.h (emx+gcc) */

#ifndef _MATH_H
#define _MATH_H

#if defined (__cplusplus)
extern "C" {
#endif

#define HUGE_VAL        1e9999

double acos (double);
double asin (double);
double atan (double);
double atan2 (double, double);
double ceil (double);
double cos (double);
double cosh (double);
double exp (double);
double fabs (double);
double floor (double);
double fmod (double, double);
double frexp (double, int *);
double hypot (double, double);
double ldexp (double, int);
double log (double);
double log10 (double);
double modf (double, double *);
double pow (double, double);
double rint (double);
double sin (double);
double sinh (double);
double sqrt (double);
double tan (double);
double tanh (double);
double trunc (double);

#if !defined (__NO_C9X)

#define HUGE_VALF       1e9999F
#define HUGE_VALL       1e9999L
#define INFINITY        1e9999          /* TODO: float_t */
#define NAN             (0.0/0.0)       /* TODO: Exceptions, float_t */

#define DECIMAL_DIG     21

#define FP_ZERO         0
#define FP_SUBNORMAL    1
#define FP_NORMAL       2
#define FP_INFINITE     3
#define FP_NAN          4

#define fpclassify(x) \
    ((sizeof (x) == sizeof (float))  ? __fpclassifyf (x) \
   : (sizeof (x) == sizeof (double)) ? __fpclassify (x) \
   :                                   __fpclassifyl (x))

#define signbit(x) \
    ((sizeof (x) == sizeof (float))  ? __signbitf (x) \
   : (sizeof (x) == sizeof (double)) ? __signbit (x) \
   :                                   __signbitl (x))

#define isfinite(x) \
    ((sizeof (x) == sizeof (float))  ? __isfinitef (x) \
   : (sizeof (x) == sizeof (double)) ? __isfinite (x) \
   :                                   __isfinitel (x))

#define isnormal(x) \
    ((sizeof (x) == sizeof (float))  ? __isnormalf (x) \
   : (sizeof (x) == sizeof (double)) ? __isnormal (x) \
   :                                   __isnormall (x))

#define isnan(x) \
    ((sizeof (x) == sizeof (float))  ? __isnanf (x) \
   : (sizeof (x) == sizeof (double)) ? __isnan (x) \
   :                                   __isnanl (x))

float copysignf (float, float);
double copysign (double, double);
long double copysignl (long double, long double);

float nextafterf (float, float);
double nextafter (double, double);
long double nextafterl (long double, long double);

long double acosl (long double);
long double asinl (long double);
long double atanl (long double);
long double atan2l (long double, long double);
long double ceill (long double);
long double cosl (long double);
long double coshl (long double);
long double expl (long double);
long double fabsl (long double);
long double floorl (long double);
long double fmodl (long double, long double);
long double frexpl (long double, int *);
long double hypotl (long double, long double);
long double ldexpl (long double, int);
long double logl (long double);
long double log10l (long double);
long double modfl (long double, long double *);
long double powl (long double, long double);
long double rintl (long double);
long double sinl (long double);
long double sinhl (long double);
long double sqrtl (long double);
long double tanl (long double);
long double tanhl (long double);
long double truncl (long double);

int __fpclassify (double);
int __fpclassifyf (float);
int __fpclassifyl (long double);

int __signbit (double);
int __signbitf (float);
int __signbitl (long double);

int __isfinite (double);
int __isfinitef (float);
int __isfinitel (long double);

int __isnormal (double);
int __isnormalf (float);
int __isnormall (long double);

int __isnan (double);
int __isnanf (float);
int __isnanl (long double);

#endif

#if !defined (__STRICT_ANSI__)

#define HUGE    HUGE_VAL

double atof (__const__ char *);
double cbrt (double);

#if !defined (_ABS)                                    /* see also stdlib.h */
#define _ABS
#if !defined (__GNUC__) || __GNUC__ >= 2
extern int abs (int);
extern long labs (long);
#else
extern __inline__ int abs (int _n) { return (_n < 0 ? -_n : _n); }
extern __inline__ long labs (long _n) { return (_n < 0 ? -_n : _n); }
#endif
#endif

#endif


#if !defined (__STRICT_ANSI__) || defined (_WITH_UNDERSCORE)

#define _HUGE_VALF      1e9999F
#define _HUGE_VALL      1e9999L
#define _INFINITY       1e9999          /* TODO: float_t */
#define _NAN            (0.0/0.0)       /* TODO: Exceptions, float_t */

#define _LHUGE_VAL      _HUGE_VALL
#define _LHUGE          _HUGE_VALL


float _copysignf (float, float);
double _copysign (double, double);
long double _copysignl (long double, long double);

float _nextafterf (float, float);
double _nextafter (double, double);
long double _nextafterl (long double, long double);

long double _acosl (long double);
long double _asinl (long double);
long double _atanl (long double);
long double _atan2l (long double, long double);
long double _atofl (__const__ char *);
long double _cbrtl (long double);
long double _ceill (long double);
long double _cosl (long double);
long double _coshl (long double);
long double _hypotl (long double, long double);
long double _expl (long double);
long double _fabsl (long double);
long double _floorl (long double);
long double _fmodl (long double, long double);
long double _frexpl (long double, int *);
long double _ldexpl (long double, int);
long double _logl (long double);
long double _log10l (long double);
long double _modfl (long double, long double *);
long double _powl (long double, long double);
long double _rintl (long double);
long double _sinl (long double);
long double _sinhl (long double);
long double _sqrtl (long double);
long double _tanl (long double);
long double _tanhl (long double);
long double _truncl (long double);

#endif


#if defined (__cplusplus)
}
#endif

#endif /* not _MATH_H */
