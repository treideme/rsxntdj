/* 386/builtin.h (emx+gcc) */

#ifndef _I386_BUILTIN_H
#define _I386_BUILTIN_H

#if defined (__cplusplus)
extern "C" {
#endif

static __inline__ signed char __cxchg (__volatile__ signed char *p,
                                       signed char v)
{
  __asm__ __volatile__ ("xchgb %0, %1" : "=m"(*p), "=r"(v) : "1"(v));
  return v;
}

static __inline__ short __sxchg (__volatile__ short *p, short v)
{
  __asm__ __volatile__ ("xchgw %0, %1" : "=m"(*p), "=r"(v) : "1"(v));
  return v;
}

static __inline__ int __lxchg (__volatile__ int *p, int v)
{
  __asm__ __volatile__ ("xchgl %0, %1" : "=m"(*p), "=r"(v) : "1"(v));
  return v;
}

static __inline__ void __enable (void)
{
  __asm__ __volatile__ ("sti");
}

static __inline__ void __disable (void)
{
  __asm__ __volatile__ ("cli");
}

#define __ROTATE_FUN(F,I,T) \
  static __inline__ T F (T value, int shift) \
  { \
    __asm__ (I " %b2, %0" : "=g"(value) : "0"(value), "c"(shift) : "cc"); \
    return value; \
  } \
  static __inline__ T F##1 (T value) \
  { \
    __asm__ (I " $1, %0" : "=g"(value) : "0"(value) : "cc"); \
    return value; \
  }

#define __ROTATE(V,S,F) ((__builtin_constant_p (S) && (int)(S) == 1) \
                         ? F##1 (V) : F (V, S))

__ROTATE_FUN (__crotr, "rorb", unsigned char)
__ROTATE_FUN (__srotr, "rorw", unsigned short)
__ROTATE_FUN (__lrotr, "rorl", unsigned long)

__ROTATE_FUN (__crotl, "rolb", unsigned char)
__ROTATE_FUN (__srotl, "rolw", unsigned short)
__ROTATE_FUN (__lrotl, "roll", unsigned long)

#define _crotr(V,S) __ROTATE (V, S, __crotr)
#define _srotr(V,S) __ROTATE (V, S, __srotr)
#define _lrotr(V,S) __ROTATE (V, S, __lrotr)
#define _crotl(V,S) __ROTATE (V, S, __crotl)
#define _srotl(V,S) __ROTATE (V, S, __srotl)
#define _lrotl(V,S) __ROTATE (V, S, __lrotl)

#define _rotr(V,S) _lrotr (V, S)
#define _rotl(V,S) _lrotl (V, S)


static __inline__ int __fls (int v)
{
  int r;

  __asm__ __volatile__ ("bsrl %1, %0;"
                        "jnz 1f;"
                        "movl $-1, %0;"
                        ".align 2, 0x90;"
                        "1:"
                        : "=r"(r) : "r"(v) : "cc");
  return r + 1;
}

#if defined (__cplusplus)
}
#endif

#endif /* not _I386_BUILTIN_H */
