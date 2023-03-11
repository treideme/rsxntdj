/ emx/asm386.h (emx+gcc) -- Copyright (c) 1992-1996 by Eberhard Mattes

#include <sys/errno.h>

#define _xam fxam; fstsww %ax; andb $0x45, %ah

#define j_nan cmpb $0x01, %ah; je
#define j_inf cmpb $0x05, %ah; je

/* MATHSUFFIX1 is for sin() vs. sinf() vs. _sinl() */
/* MATHSUFFIX2 is for _sin() vs. _sinf() vs. _sinl() */
/* MATHSUFFIX3 is for sin() vs. sinf() vs. sinl () */

#if defined (LONG_DOUBLE)
#define FLD fldt
#define MATHSUFFIX1(X)   _##X##l
#define MATHSUFFIX2(X)  _##X##l
#define MATHSUFFIX3(X)  X##l
#define CONV(X)
#elif defined (FLOAT)
#define FLD flds
#define MATHSUFFIX1(X)  _##X##f
#define MATHSUFFIX2(X)  _##X##f
#define MATHSUFFIX3(X)  X##f
#define CONV(X) fstps X; flds X
#else
#define FLD fldl
#define MATHSUFFIX1(X)  X
#define MATHSUFFIX2(X)  _##X
#define MATHSUFFIX3(X)  X
#define CONV(X) fstpl X; fldl X
#endif

#define LABEL0(name)    _##name
#define LABEL(name)     LABEL0(name)

#define ALIGN   .align  2, 0x90

#if !defined (__MT__)

#define SET_ERRNO_CONST(x) \
        movl    x, _errno

#else

#define SET_ERRNO_CONST(x) \
        call    __errno ;\
        movl    x, (%eax)

#endif

#if defined (__GPROF__)
#define PROFILE_FRAME	call __mcount
#define PROFILE_NOFRAME	pushl %ebp; movl %esp, %ebp; call __mcount; popl %ebp
#else
#define PROFILE_FRAME
#define PROFILE_NOFRAME
#endif

#if defined (__EPILOGUE__)
#define EPILOGUE_NO_RET(name) LABEL(__POST$##name):
#else
#define EPILOGUE_NO_RET(name)
#endif

#define EPILOGUE(name) EPILOGUE_NO_RET (name) ret

/* Cf. <math.h> */

#define FP_ZERO         0
#define FP_SUBNORMAL    1
#define FP_NORMAL       2
#define FP_INFINITE     3
#define FP_NAN          4
