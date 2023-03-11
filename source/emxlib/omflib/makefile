#
# /emx/src/lib/omflib/makefile
#
.INCLUDE: /emx/src/lib/lib0.mak

.SOURCE.c: ..
.SOURCE.h: ..

.PHONY: clean realclean default dstlib omflib

OMFLIB=$(L)omflib.a
DEP=$(S)omflib.h omflib0.h
OBJECTS=omflibam.o omflibap.o omflibcl.o omflibcp.o omflibcr.o \
	omflibdl.o omflibex.o omflibpb.o omflibrd.o omflibut.o \
	omflibwr.o

default:	omflib

omflib .SETDIR=$(CPU):
	$(MAKE) -f ../makefile dstlib $(PASSDOWN)

dstlib: $(OMFLIB)

$(OMFLIB):	$(OBJECTS)
	-del $(OMFLIB)
	$(AR) r $(OMFLIB) *.o

omflibam.o:	omflibam.c $(DEP)
omflibap.o:	omflibap.c $(DEP) $(ERRNO)
omflibcl.o:	omflibcl.c $(DEP) $(ERRNO)
omflibcp.o:	omflibcp.c $(DEP)
omflibcr.o:	omflibcr.c $(DEP) $(ERRNO)
omflibdl.o:	omflibdl.c $(DEP)
omflibex.o:	omflibex.c $(DEP)
omflibpb.o:	omflibpb.c $(DEP)
omflibrd.o:	omflibrd.c $(DEP) $(ERRNO)
omflibut.o:	omflibut.c $(DEP)
omflibwr.o:	omflibwr.c $(DEP)

clean:
	-del $(CPU)\*.o

realclean: clean
	-del $(OMFLIB)
