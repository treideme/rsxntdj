RSXDIR := $(subst \,/,$(RSXNTDJ))
LIBMAIN := $(RSXDIR)/lib/libmain.a
DLLMAIN := $(RSXDIR)/lib/libdll.a
DLL0W32 := $(RSXDIR)/lib/dll0w32.o
CRT0W32 := $(RSXDIR)/lib/crt0w32.o
LIB := $(RSXDIR)/lib

all: $(LIBMAIN) $(DLL) $(DLL0W32) $(CRT0W32) $(LIB)/excpt.a $(LIB)/excpt2.a

.c.o:
	gccw32 -c -O2 $<

.s.o:
	gccw32 -c $<

$(LIBMAIN): winmain.o
	-del $(LIBMAIN)
	ar r $(LIBMAIN) winmain.o
	ar s $(LIBMAIN)

$(DLL): dllentry.o libmain.o
	-del $(DLL)
	ar r $(DLL) dllentry.o libmain.o

$(DLL0W32): dll0w32.s
	gccw32 -c -x assembler-with-cpp -o $(DLL0W32) dll0w32.s

$(CRT0W32): crt0w32.s
	gccw32 -c -x assembler-with-cpp -o $(CRT0W32) crt0w32.s

$(LIB)/excpt.a: excpt.o excpt1.o
	-del $(LIB)/excpt.a
	ar -r $(LIB)/excpt.a excpt.o excpt1.o

$(LIB)/excpt2.a: excptex.o excpt2.o
	-del $(LIB)/excpt2.a
	ar -r $(LIB)/excpt2.a excptex.o excpt2.o

excpt.o: excpt.c
	gccw32 -c -Wall -O2 excpt.c

excptex.o: excpt.c
	gccw32 -c -Wall -O2 -DRSXNT_SEH -o excptex.o excpt.c