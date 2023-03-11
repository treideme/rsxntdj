#
# /emx/src/lib/dllso/makefile
#
LIBBASE=c_dllso
.INCLUDE: /emx/src/lib/libc0.mak
APP=../../app/

local: ;

crt3.o: /emx/src/lib/dllso/386/crt3.s
	gcc -c -O /emx/src/lib/dllso/386/crt3.s

dllinit.o: /emx/src/lib/dllso/dllinit.c
	gcc -c -O /emx/src/lib/dllso/dllinit.c

iodata.o: $(APP)iodata.c
	gcc -c -O -D_NFILES=40 $(APP)iodata.c

stdio.o: $(APP)stdio.c
	gcc -c -O -D_NFILES=40 $(APP)stdio.c

getenv.o: /emx/src/lib/dllso/getenv.c
	gcc -c -O /emx/src/lib/dllso/getenv.c

$(DSTLIB): crt3.o dllinit.o getenv.o iodata.o stdio.o
	ar r $(DSTLIB) *.o
