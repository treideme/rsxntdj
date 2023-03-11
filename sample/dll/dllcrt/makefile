#
# Makefile for DLL with CRT DLL
#

#crt=1

include ..\..\rsxntmak.gnu
## !include <..\..\rsxntmak.msc>

project: loadtime.exe runtime.exe dllcrt.dll

############################################################


dllcrt.dll: dllcrt.o dllcrt.def
	$(CC) $(LDFLAGS) $(DLLFLAGS) dllcrt.o -o dllcrt.dll -Ttext=0x20001000

dllcrt.o: dllcrt.c
	$(CC) $(CFLAGS) $(DLLFLAGS) -c dllcrt.c

dllcrt.a: dllcrt.dll
	-del dllcrt.a
	$(IMPLIB) dllcrt.dll -o dllcrt.a

loadtime.exe: loadtime.o dllcrt.a
	$(CC) $(CFLAGS) -o loadtime.exe loadtime.o dllcrt.a

runtime.exe: runtime.o
	$(CC) $(CFLAGS) -o runtime.exe runtime.o

