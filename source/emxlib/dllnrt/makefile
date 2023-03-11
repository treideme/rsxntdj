#
# /emx/src/lib/dllnrt/makefile
#
DSTLIB=$(L)c_dllnrt.lib
.INCLUDE: /emx/src/lib/lib0.mak

.SOURCE.c: ..
.SOURCE.h: ..
.SOURCE.s: ..

.PHONY: dllnrt dstlib

default: dllnrt

dllnrt:
	$(MAKE) -f ../makefile dstlib $(PASSDOWN)

dstlib: $(DSTLIB)

crt3.o: crt3.s
	$(GCC) -c crt.s

dllinit.o: ..\dllinit.c
	$(GCC) -c ..\dllinit.c

getenv.o: ..\getenv.c
	$(GCC) -c ..\getenv.c

$(DSTLIB): crt3.o dllinit.o getenv.o
	ar r $(DSTLIB) *.o

clean:
	-del $(CPU)\*.obj
