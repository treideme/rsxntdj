#
# Makefile for DLL (no-rte) and stand-alone EXE that is calling this DLL
#

include ..\..\rsxntmak.gnu
## !include <..\..\rsxntmak.msc>

project: dllnrt.dll runtime.exe loadtime.exe

############################################################

DLLFLAGS = -Zdll -Zno-rte

dllnrt.dll: dllnrt.o dllnrt.def
	$(CC) $(LDFLAGS) $(DLLFLAGS) -o dllnrt.dll dllnrt.o -Ttext=0x20001000

dllnrt.o: dllnrt.c
	$(CC) $(CFLAGS) $(DLLFLAGS) -c dllnrt.c -DSKIP_LIBMAIN

dllnrt.a: dllnrt.dll
	-del dllnrt.a
	$(IMPLIB) dllnrt.dll -o dllnrt.a

loadtime.exe: loadtime.o dllnrt.a
	$(CC) $(CFLAGS) -Zsys loadtime.o dllnrt.a -o loadtime.exe

runtime.exe: runtime.o
	$(CC) $(CFLAGS) -Zsys runtime.o -o runtime.exe

