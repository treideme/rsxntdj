##
# Makefile for stand-alone DLL and stand-alone EXE that is calling this DLL
#

include ..\..\rsxntmak.gnu
## !include <..\..\rsxntmak.msc>

project: dllso.dll runtime.exe

############################################################

DLLFLAGS = -Zsys -Zdll -Zso

dllso.dll: dllso.o dllso.def
	$(CC) $(LDFLAGS) $(DLLFLAGS) dllso.o -o dllso.dll -Ttext=0x20001000

dllso.o: dllso.c
	$(CC) $(CFLAGS) $(DLLFLAGS) -c dllso.c

runtime.exe: runtime.o
	$(CC) $(CFLAGS) -Zsys runtime.o -o runtime.exe
