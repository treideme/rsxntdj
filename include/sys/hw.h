/* sys/hw.h (emx+gcc) */

#ifndef _SYS_HW_H
#define _SYS_HW_H

#if defined (__cplusplus)
extern "C" {
#endif

void *_memaccess (unsigned, unsigned, int);
int _portaccess (unsigned, unsigned);

unsigned _inp8 (unsigned);
unsigned _inp16 (unsigned);
unsigned _inp32 (unsigned);
void _inps8 (unsigned, unsigned char *, unsigned);
void _inps16 (unsigned, unsigned short *, unsigned);
void _inps32 (unsigned, unsigned long *, unsigned);

void _outp8 (unsigned, unsigned value);
void _outp16 (unsigned, unsigned value);
void _outp32 (unsigned, unsigned value);
void _outps8 (unsigned, __const__ unsigned char *, unsigned);
void _outps16 (unsigned, __const__ unsigned short *, unsigned);
void _outps32 (unsigned, __const__ unsigned long *, unsigned);
void _outpt (__const__ void *);
void _outps8dac (unsigned, __const__ unsigned char *, unsigned);

void _wait0 (unsigned, unsigned);
void _wait1 (unsigned, unsigned);
void _wait01 (unsigned, unsigned);
void _wait10 (unsigned, unsigned);

#if defined (__cplusplus)
}
#endif

#endif /* not SYS_HW_H */
