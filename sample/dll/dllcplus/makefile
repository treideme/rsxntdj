#
# This makefile is created by rsxide
#

.SUFFIXES: .exe .res .a .o .c .cpp .cc .cxx .m .rc .p .f .F .r .y .l .s .S .def .h

all: dllcplus.dll loadtime.exe

CC_TARGET_01=-Zdll -Zsys -Zso 
CFLAGS_TARGET_01=-O2 -Wall 

dllcplus.a: dllcplus.dll
	makelib dllcplus.dll -o dllcplus.a

dllcplus.dll: dllcplus.o dllcplus.def
	gccw32 $(CC_TARGET_01) -o dllcplus.dll dllcplus.o -lstdcx -Ttext=0x20001000

dllcplus.o: dllcplus.cc
	gccw32 -c -o dllcplus.o dllcplus.cc $(CC_TARGET_01)  $(CFLAGS_TARGET_01)

CC_TARGET_02=
CFLAGS_TARGET_02=-O2 -Wall 

loadtime.exe: loadtime.o dllcplus.a
	gccw32 $(CC_TARGET_02) -o loadtime.exe loadtime.o dllcplus.a

loadtime.o: loadtime.cc
	gccw32 -c -o loadtime.o loadtime.cc $(CC_TARGET_02)  $(CFLAGS_TARGET_02)

