/* os2thunk.h (emx+gcc) */

#ifndef _OS2THUNK_H
#define _OS2THUNK_H

typedef unsigned long _far16ptr;

_far16ptr _emx_32to16 (void *ptr);
void *_emx_16to32 (_far16ptr ptr);

unsigned long _emx_thunk1 (void *args, void *fun);

#define _THUNK_PASCAL_PROLOG(SIZE) \
  ({ char _tb[(SIZE)+4]; void *_tp = _tb + sizeof (_tb); \
       *(unsigned long *)_tb = (SIZE);
#define _THUNK_PASCAL_CHAR(ARG)     _THUNK_PASCAL_SHORT (ARG)
#define _THUNK_PASCAL_SHORT(ARG)    (*--((unsigned short *)_tp) = (ARG))
#define _THUNK_PASCAL_LONG(ARG)     (*--((unsigned long *)_tp) = (ARG))
#define _THUNK_PASCAL_FLAT(ARG)     _THUNK_PASCAL_LONG (_emx_32to16 (ARG))
#define _THUNK_PASCAL_FAR16(ARG)    _THUNK_PASCAL_LONG (ARG)
#define _THUNK_PASCAL_FUNCTION(FUN) _16_##FUN
#define _THUNK_PASCAL_CALL(FUN)     _emx_thunk1 (_tb, (void *)(_16_##FUN)); })
#define _THUNK_PASCAL_CALLI(FUN)    _emx_thunk1 (_tb, (void *)(FUN)); })

#define _THUNK_C_PROLOG(SIZE) \
  ({ char _tb[(SIZE)+4]; void *_tp = _tb + sizeof (unsigned long); \
       *(unsigned long *)_tb = (SIZE);
#define _THUNK_C_CHAR(ARG)     _THUNK_C_SHORT (ARG)
#define _THUNK_C_SHORT(ARG)    (*((unsigned short *)_tp)++ = (ARG))
#define _THUNK_C_LONG(ARG)     (*((unsigned long *)_tp)++ = (ARG))
#define _THUNK_C_FLAT(ARG)     _THUNK_C_LONG (_emx_32to16 (ARG))
#define _THUNK_C_FAR16(ARG)    _THUNK_C_LONG (ARG)
#define _THUNK_C_FUNCTION(FUN) _16__##FUN
#define _THUNK_C_CALL(FUN)     _emx_thunk1 (_tb, (void *)(_16__##FUN)); })
#define _THUNK_C_CALLI(FUN)    _emx_thunk1 (_tb, (void *)(FUN)); })

#define _THUNK_PROLOG(SIZE)  _THUNK_PASCAL_PROLOG (SIZE)
#define _THUNK_CHAR(ARG)     _THUNK_PASCAL_CHAR (ARG)
#define _THUNK_SHORT(ARG)    _THUNK_PASCAL_SHORT (ARG)
#define _THUNK_LONG(ARG)     _THUNK_PASCAL_LONG (ARG)
#define _THUNK_FLAT(ARG)     _THUNK_PASCAL_FLAT (ARG)
#define _THUNK_FAR16(ARG)    _THUNK_PASCAL_FAR16 (ARG)
#define _THUNK_FUNCTION(FUN) _THUNK_PASCAL_FUNCTION (FUN)
#define _THUNK_CALL(FUN)     _THUNK_PASCAL_CALL (FUN)
#define _THUNK_CALLI(FUN)    _THUNK_PASCAL_CALLI (FUN)

#define MAKE16P(sel,off)   ((_far16ptr)((sel) << 16 | (off)))
#define MAKEP(sel,off)     _emx_16to32 (MAKE16P (sel, off))
#define SELECTOROF(farptr) ((SEL)((farptr) >> 16))
#define OFFSETOF(farptr)   ((USHORT)(farptr))

/* Return true iff the block of SIZE bytes at PTR does not cross a
   64Kbyte boundary. */

#define _THUNK_PTR_SIZE_OK(ptr,size) \
  (((ULONG)(ptr) & ~0xffff) == (((ULONG)(ptr) + (size) - 1) & ~0xffff))

/* Return true iff the structure pointed to by PTR does not cross a
   64KByte boundary. */

#define _THUNK_PTR_STRUCT_OK(ptr) _THUNK_PTR_SIZE_OK ((ptr), sizeof (*(ptr)))

#endif /* not _OS2THUNK_H */
