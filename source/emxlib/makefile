#
# /emx/src/lib/makefile
#
# This makefile has been designed for dmake 3.8.
#
# Don't forget to SET SWITCHAR=-
#
# Targets:
#
# mkdir         Create directories
# c-st          Single-thread common C library:      st/c.a
# c-st-p        Ditto, for profiling:                st/c_p.a
# c-mt          Multithread common C library:        mt/c.a
# c_alias       Aliases                              c_alias.{a,lib}
# c_static      Static modules                       c_static.{a,lib}
# c_app-st      Single-thread application C library: st/c_app.a
# c_app-st-p    Ditto, for profiling:                st/c_app_p.a
# c_app-mt      Multithread application C library:   mt/c_app.a
# c_dllrt-st    Single-thread DLL C library:         st/c_dllrt.a
# c_dllrt-mt    Multithread DLL C library:           mt/c_dllrt.a
# c_dllso-st    Single-thread DLL C library (-Zso):  st/c_dllso.lib
# c_dllso-mt    Multithread DLL C library (-Zso):    mt/c_dllso.lib
# c_import-st   Single-thread import library:        st/c_import.{a,lib}
# c_import-mt   Multithread import library:          mt/c_import.{a,lib}
# c_dllnrt      DLL without runtime environment:     c_dllnrt.lib
# libgcc        GCC helper functions:                gcc.a
# libgcc-p	Ditto, with profiling:		     gcc_p.a
# socket        Socket library:                      socket.a
# graph         Graphics library:                    graph.a
# video         Video library:                       video.a
# moddef        moddef library:                      moddef.a
# omflib        omflib library:                      omflib.a
# tmalloc       tmalloc wrapper library:             tmalloc.a
# malloc1-st	Old single-thread malloc library:    st/malloc1.a
# malloc1-mt	Old multithread malloc library:	     mt/malloc1.a
# end		etext/edata/end library for LINK386: end.lib
# os2           OS/2 API import library:             os2.a
# os2-p         Ditto, for profiling:                os2_p.a
# dll-fwd       Create forwarder DLL                 emxlibc.dll
# dll-mt        Create multithread C runtime DLL     emxlibcm.dll
# dll-st        Create single-thread C runtime DLL   emxlibcs.dll
# sys           System call emulation library:       st/sys.lib mt/sys.lib
# o-crt         Startup modules (.o)                 crt0.o dll0.o ...
# o-crt-bsd     Ditto, BSD stuff                     gcrt0.o
# o-opt         Optional object files (.o)           binmode.o sigbsd.o ...
# obj-crt       Startup modules (.obj)               crt0.obj dll0.obj ...
# obj-opt       Optional object files (.obj)         binmode.obj sigbsd.obj ...
# emxwrap       emxwrap.dll, wrap.a, and wrap.lib
# all-dos       All libraries and object files for DOS
# all-os2       Ditto, plus libraries, object files, and DLLs for OS/2
# all-dos-bsd   Like all-dos, plus BSD stuff
# all-os2-bsd   Like all-os2, plus BSD stuff
# omf           Build .lib and .obj files from .a and .o files
# trace		Build .tdf and .tff files	     emxlibc?.tdf trc00??.tff
# clean         Remove files created in the build process
# cleanall      Remove target files and files created in the build process
#
##############################################################################

.IF $(CPU)
.ELSE
CPU=386
.ENDIF

##############################################################################

GCC=gcc -O2 -Wall -mprobe -fstack-check
ASM=gcc -c -Wall -x assembler-with-cpp
AR=ar
I=/emx/include/
S=$(I)sys/
E=$(S)emx.h
L=\emx\lib\ #
DLL=\emx\dll\ #

##############################################################################

PASSDOWN=CPU=$(CPU) DELOPT=$(DELOPT)

##############################################################################

.SUFFIXES: .a .lib

.a.lib:
	emxomf -sl $<

.PHONY: all-dos all-os2 all-bsd all-dos-bsd all-os2-bsd clean cleanall \
        default emx_386 libgcc libgcc-p c_static c_alias \
        c-st c-st-p c-mt c_app-st c_app-st-p c_app-mt c_dllrt-st c_dllrt-mt \
        c_dllso-st c_dllso-mt c_import-st c_import-mt c_dllnrt \
        socket tmalloc end graph os2_386 os2_386-p sys video moddef \
	omflib emxwrap trace \
        malloc1-st malloc1-mt mkdir mkdir-cpu \
        omf dll-int o-crt o-crt-bsd o-opt obj-crt obj-opt recurse os2 os2-p \
        rec-all rec-c rec-app rec-conv rec-ctype rec-emx_386 \
        rec-emxload rec-gcc rec-graph rec-io rec-cdll rec-malloc rec-math \
        rec-misc rec-moddef rec-nls rec-os2_386 rec-process rec-socket \
        rec-startup rec-str rec-sys rec-termios rec-time rec-tmalloc \
        rec-video rec-locale rec-mbyte rec-omflib rec-end rec-malloc1



##############################################################################

default .SWAP .SEQUENTIAL: all-os2-bsd trace

os2: os2_$(CPU)

os2-p: os2_$(CPU)-p

all-dos .SEQUENTIAL .SWAP: o-crt o-opt c-st c_alias c_app-st libgcc os2_$(CPU) \
    emx_$(CPU) graph video moddef omflib $(L)g.a $(L)m.a \
    malloc1-st

all-os2 .SWAP .SEQUENTIAL: all-dos c-mt c_app-mt c_dllrt-st c_dllrt-mt \
    c_dllso-st c_dllso-mt c_import-st c_import-mt c_dllnrt \
    sys end dll-int emxwrap socket tmalloc malloc1-mt omf

all-dos-bsd .SWAP .SEQUENTIAL: all-dos o-crt-bsd

all-os2-bsd .SWAP .SEQUENTIAL: all-os2 o-crt-bsd

omf .SWAP .SEQUENTIAL: obj-crt obj-opt \
        $(L)gcc.lib $(L)g.lib $(L)m.lib $(L)c_alias.lib \
        $(L)st\c.lib $(L)st\c_app.lib $(L)st\c_dllrt.lib $(L)st\emx.lib \
        $(L)mt\c.lib $(L)mt\c_app.lib $(L)mt\c_dllrt.lib $(L)mt\emx.lib \
        $(L)os2.lib $(L)emx2.lib $(L)emxio.lib $(L)graph.lib $(L)video.lib \
        $(L)moddef.lib $(L)tmalloc.lib $(L)omflib.lib $(L)c_static.lib \
        $(L)socket.lib $(L)st\malloc1.lib $(L)mt\malloc1.lib

o-crt .SWAP .SETDIR=startup:
	$(MAKE) o-crt $(PASSDOWN)

o-crt-bsd .SWAP .SETDIR=startup:
	$(MAKE) o-crt-bsd $(PASSDOWN)

obj-crt .SWAP .SETDIR=startup:
	$(MAKE) obj-crt $(PASSDOWN)

o-opt: $(L)binmode.o $(L)sigsysv.o $(L)sigbsd.o $(L)smallcnv.o

obj-opt: $(L)binmode.obj $(L)sigsysv.obj $(L)sigbsd.obj $(L)smallcnv.obj

clean:
	$(MAKE) recurse RDIR=all RTARGET=clean $(PASSDOWN)

cleanall .IGNORE: clean
	del $(L)*.o $(DELOPT)
	del $(L)*.obj $(DELOPT)
	del $(L)*.lib $(DELOPT)
	del $(L)*.a $(DELOPT)
	del $(L)mt\*.a $(DELOPT)
	del $(L)mt\*.lib $(DELOPT)
	del $(L)st\*.a $(DELOPT)
	del $(L)st\*.lib $(DELOPT)

##############################################################################

recurse: rec-$(RDIR)

RECURSE=$(RTARGET) $(PASSDOWN)

rec-all .SWAP .SEQUENTIAL: rec-c rec-os2_$(CPU) rec-gcc rec-emx_$(CPU) rec-sys \
                     rec-alias rec-app rec-cdll rec-dllrt rec-dllso \
                     rec-dllnrt rec-moddef rec-omflib rec-graph rec-video \
                     rec-socket rec-static rec-tmalloc rec-end rec-malloc1

rec-c .SWAP .SEQUENTIAL: rec-conv rec-ctype rec-emxload rec-io \
                   rec-locale rec-malloc rec-math rec-mbyte rec-misc \
                   rec-nls rec-process rec-startup rec-str rec-termios \
                   rec-time

rec-alias .SWAP .SETDIR=alias:
	$(MAKE) $(RECURSE)

rec-app .SWAP .SETDIR=app:
	$(MAKE) $(RECURSE)

rec-cdll .SWAP .SETDIR=cdll:
	$(MAKE) $(RECURSE)

rec-conv .SWAP .SETDIR=conv:
	$(MAKE) $(RECURSE)

rec-ctype .SWAP .SETDIR=ctype:
	$(MAKE) $(RECURSE)

rec-dllnrt .SWAP .SETDIR=dllnrt:
	$(MAKE) $(RECURSE)

rec-dllrt .SWAP .SETDIR=dllrt:
	$(MAKE) $(RECURSE)

rec-dllso .SWAP .SETDIR=dllso:
	$(MAKE) $(RECURSE)

rec-emx_$(CPU) .SWAP .SETDIR=emx_$(CPU):
	$(MAKE) $(RECURSE)

rec-emxload .SWAP .SETDIR=emxload:
	$(MAKE) $(RECURSE)

rec-end .SWAP .SETDIR=end:
	$(MAKE) $(RECURSE)

rec-gcc .SWAP .SETDIR=gcc:
	$(MAKE) $(RECURSE)

rec-graph .SWAP .SETDIR=graph:
	$(MAKE) $(RECURSE)

rec-io .SWAP .SETDIR=io:
	$(MAKE) $(RECURSE)

rec-locale .SWAP .SETDIR=locale:
	$(MAKE) $(RECURSE)

rec-malloc .SWAP .SETDIR=malloc:
	$(MAKE) $(RECURSE)

rec-malloc1 .SWAP .SETDIR=malloc1:
	$(MAKE) $(RECURSE)

rec-math .SWAP .SETDIR=math:
	$(MAKE) $(RECURSE)

rec-mbyte .SWAP .SETDIR=mbyte:
	$(MAKE) $(RECURSE)

rec-moddef .SWAP .SETDIR=moddef:
	$(MAKE) $(RECURSE)

rec-static .SWAP .SETDIR=static:
	$(MAKE) $(RECURSE)

rec-tmalloc .SWAP .SETDIR=tmalloc:
	$(MAKE) $(RECURSE)

rec-omflib .SWAP .SETDIR=omflib:
	$(MAKE) $(RECURSE)

rec-misc .SWAP .SETDIR=misc:
	$(MAKE) $(RECURSE)

rec-nls .SWAP .SETDIR=nls:
	$(MAKE) $(RECURSE)

rec-os2_$(CPU) .SWAP .SETDIR=os2_$(CPU):
	$(MAKE) $(RECURSE)

rec-process .SWAP .SETDIR=process:
	$(MAKE) $(RECURSE)

rec-socket .SWAP .SETDIR=socket:
	$(MAKE) $(RECURSE)

rec-startup .SWAP .SETDIR=startup:
	$(MAKE) $(RECURSE)

rec-str .SWAP .SETDIR=str:
	$(MAKE) $(RECURSE)

rec-sys .SWAP .SETDIR=sys:
	$(MAKE) $(RECURSE)

rec-termios .SWAP .SETDIR=termios:
	$(MAKE) $(RECURSE)

rec-time .SWAP .SETDIR=time:
	$(MAKE) $(RECURSE)

rec-video .SWAP .SETDIR=video:
	$(MAKE) $(RECURSE)

##############################################################################

$(L)binmode.o: io/$(CPU)/binmode.s
	$(ASM) -o $(L)binmode.o io/$(CPU)/binmode.s

$(L)sigsysv.o: process/sigsysv.c $(S)uflags.h
	$(GCC) -c -o $(L)sigsysv.o process/sigsysv.c

$(L)sigbsd.o: process/sigbsd.c $(S)uflags.h
	$(GCC) -c -o $(L)sigbsd.o process/sigbsd.c

$(L)smallcnv.o: conv/$(CPU)/smallcnv.s
	$(ASM) -o $(L)smallcnv.o conv/$(CPU)/smallcnv.s

$(L)binmode.obj: $(L)binmode.o
	emxomf -sl $(L)binmode.o

$(L)sigbsd.obj: $(L)sigbsd.o
	emxomf -sl $(L)sigbsd.o

$(L)sigsysv.obj: $(L)sigsysv.o
	emxomf -sl $(L)sigsysv.o

$(L)smallcnv.obj: $(L)smallcnv.o
	emxomf -sl $(L)smallcnv.o

$(L)crt0.obj: obj-crt
$(L)mcrt0.obj: obj-crt
$(L)dll0.obj: obj-crt
$(L)res0.obj: obj-crt

##############################################################################

c-st .SWAP:
	$(MAKE) recurse RDIR=c RTARGET=lib-st $(PASSDOWN)

c-st-p:
	$(MAKE) recurse RDIR=c RTARGET=lib-st-p $(PASSDOWN)

c-mt .SWAP:
	$(MAKE) recurse RDIR=c RTARGET=lib-mt $(PASSDOWN)

c_alias .SWAP:
	$(MAKE) recurse RDIR=alias RTARGET=alias $(PASSDOWN)

c_app-st $(L)st\c_app.a .SWAP:
	$(MAKE) recurse RDIR=app RTARGET=lib-st $(PASSDOWN)

c_app-st-p $(L)st\c_app_p.a:
	$(MAKE) recurse RDIR=app RTARGET=lib-st-p $(PASSDOWN)

c_app-mt $(L)mt\c_app.a .SWAP:
	$(MAKE) recurse RDIR=app RTARGET=lib-mt $(PASSDOWN)

c_dllrt-st .SWAP:
	$(MAKE) recurse RDIR=dllrt RTARGET=lib-st $(PASSDOWN)

c_dllrt-mt .SWAP:
	$(MAKE) recurse RDIR=dllrt RTARGET=lib-mt $(PASSDOWN)

c_dllso-st .SWAP:
	$(MAKE) recurse RDIR=dllso RTARGET=lib-st $(PASSDOWN)

c_dllso-mt .SWAP:
	$(MAKE) recurse RDIR=dllso RTARGET=lib-mt $(PASSDOWN)

c_import-st .SWAP: c_static
	$(MAKE) recurse RDIR=cdll RTARGET=import-st $(PASSDOWN)

c_import-mt .SWAP: c_static
	$(MAKE) recurse RDIR=cdll RTARGET=import-mt $(PASSDOWN)

c_dllnrt .SWAP:
	$(MAKE) recurse RDIR=dllnrt RTARGET=dllnrt $(PASSDOWN)

c_static .SWAP:
	$(MAKE) recurse RDIR=static RTARGET=static $(PASSDOWN)


##############################################################################

libgcc .SWAP .SETDIR=gcc:
	$(MAKE) libgcc $(PASSDOWN)

libgcc-p .SWAP .SETDIR=gcc:
	$(MAKE) libgcc-p $(PASSDOWN)

os2_$(CPU) .SWAP .SETDIR=os2_$(CPU):
	$(MAKE) os2 $(PASSDOWN)

os2_$(CPU)-p .SWAP .SETDIR=os2_$(CPU):
	$(MAKE) os2-p $(PASSDOWN)

emx_$(CPU) .SWAP .SETDIR=emx_$(CPU):
	$(MAKE) emx $(PASSDOWN)

sys .SWAP .SETDIR=sys:
	$(MAKE) sys $(PASSDOWN)

graph .SWAP .SETDIR=graph:
	$(MAKE) graph $(PASSDOWN)

video .SWAP .SETDIR=video:
	$(MAKE) video $(PASSDOWN)

moddef .SWAP .SETDIR=moddef:
	$(MAKE) moddef $(PASSDOWN)

tmalloc .SWAP .SETDIR=tmalloc:
	$(MAKE) tmalloc $(PASSDOWN)

omflib .SWAP .SETDIR=omflib:
	$(MAKE) omflib $(PASSDOWN)

socket .SWAP .SETDIR=socket:
	$(MAKE) socket $(PASSDOWN)

end .SWAP .SETDIR=end:
	$(MAKE) end $(PASSDOWN)

malloc1-st $(L)st\malloc1.a:
	$(MAKE) recurse RDIR=malloc1 RTARGET=lib-st $(PASSDOWN)

malloc1-mt $(L)mt\malloc1.a:
	$(MAKE) recurse RDIR=malloc1 RTARGET=lib-mt $(PASSDOWN)


##############################################################################

$(L)g.a:
	$(AR) rs $(L)g.a

$(L)m.a:
	$(AR) rs $(L)m.a

##############################################################################

$(L)gcc.lib: $(L)gcc.a
$(L)st\c.lib: $(L)st\c.a
$(L)mt\c.lib: $(L)mt\c.a
$(L)st\c_app.lib: $(L)st\c_app.a
$(L)mt\c_app.lib: $(L)mt\c_app.a
$(L)st\c_dllrt.lib: $(L)st\c_dllrt.a
$(L)mt\c_dllrt.lib: $(L)mt\c_dllrt.a
$(L)st\emx.lib: $(L)st\emx.a
$(L)mt\emx.lib: $(L)mt\emx.a
$(L)st\malloc1.lib: $(L)st\malloc1.a
$(L)mt\malloc1.lib: $(L)mt\malloc1.a
$(L)c_alias.lib: $(L)c_alias.a
$(L)c_static.lib: $(L)c_static.a
$(L)emx2.lib: $(L)emx2.a
$(L)emxio.lib: $(L)emxio.a
$(L)graph.lib: $(L)graph.a
$(L)video.lib: $(L)video.a
$(L)moddef.lib: $(L)moddef.a
$(L)tmalloc.lib: $(L)tmalloc.a
$(L)omflib.lib: $(L)omflib.a
$(L)socket.lib: $(L)socket.a
$(L)os2.lib: $(L)os2.a
$(L)g.lib: $(L)g.a
$(L)m.lib: $(L)m.a

##############################################################################

dll-int .SWAP .SEQUENTIAL: $(L)gcc.lib $(L)os2.lib $(L)dll0.obj \
    $(L)res0.obj $(L)emx2.lib $(L)c_static.lib $(L)end.lib \
    $(L)st\c.lib $(L)st\c_dllrt.lib $(L)st\emx.lib \
    $(L)mt\c.lib $(L)mt\c_dllrt.lib $(L)mt\emx.lib
	$(MAKE) recurse RDIR=cdll RTARGET=dll-all $(PASSDOWN)

dll-st .SWAP .SEQUENTIAL: libgcc c-st c_dllrt-st emx_$(CPU) os2_$(CPU) dll-st-int

dll-st-int .SWAP .SEQUENTIAL: $(L)gcc.lib $(L)emx2.lib $(L)os2.lib $(L)dll0.obj \
    $(L)st\c.lib $(L)st\c_dllrt.lib $(L)st\emx.lib
	$(MAKE) recurse RDIR=cdll RTARGET=dll-st $(PASSDOWN)

dll-mt .SWAP .SEQUENTIAL: libgcc c-mt c_dllrt-mt emx_$(CPU) os2_$(CPU) dll-mt-int

dll-mt-int .SWAP .SEQUENTIAL: $(L)gcc.lib $(L)emx2.lib $(L)os2.lib $(L)dll0.obj \
    $(L)mt\c.lib $(L)mt\c_dllrt.lib $(L)mt\emx.lib
	$(MAKE) recurse RDIR=cdll RTARGET=dll-mt $(PASSDOWN)

dll-fwd .SWAP .SEQUENTIAL: c_import-mt emx_$(CPU) $(L)c_static.lib dll-fwd-int

dll-fwd-int: $(L)dll0.obj $(L)emx2.lib
	$(MAKE) recurse RDIR=cdll RTARGET=dll-fwd $(PASSDOWN)

emxwrap .SWAP .SEQUENTIAL: $(L)res0.obj emxwrap-int

emxwrap-int .SWAP .SETDIR=os2_$(CPU):
	$(MAKE) emxwrap $(PASSDOWN)

#
# Requires trcust.exe of os2pdp.zip
#
trace:
	$(MAKE) recurse RDIR=cdll RTARGET=trace $(PASSDOWN)

##############################################################################

mkdir .IGNORE:
	mkdir alias\$(CPU)
	mkdir app\mt_$(CPU)
	mkdir app\st_$(CPU)
	mkdir app\st_p_$(CPU)
	mkdir cdll\$(CPU)
	mkdir conv\mt_$(CPU)
	mkdir conv\st_$(CPU)
	mkdir conv\st_p_$(CPU)
	mkdir ctype\mt_$(CPU)
	mkdir ctype\st_$(CPU)
	mkdir ctype\st_p_$(CPU)
	mkdir dllnrt\$(CPU)
	mkdir dllrt\mt_$(CPU)
	mkdir dllrt\st_$(CPU)
	mkdir dllso\mt_$(CPU)
	mkdir dllso\st_$(CPU)
	mkdir emx_$(CPU)\mt
	mkdir emx_$(CPU)\st
	mkdir emxload\mt_$(CPU)
	mkdir emxload\st_$(CPU)
	mkdir emxload\st_p_$(CPU)
	mkdir gcc\st_$(CPU)
	mkdir gcc\st_p_$(CPU)
	mkdir graph\$(CPU)
	mkdir io\mt_$(CPU)
	mkdir io\st_$(CPU)
	mkdir io\st_p_$(CPU)
	mkdir locale\mt_$(CPU)
	mkdir locale\st_$(CPU)
	mkdir locale\st_p_$(CPU)
	mkdir malloc\mt_$(CPU)
	mkdir malloc\st_$(CPU)
	mkdir malloc\st_p_$(CPU)
	mkdir malloc1\mt_$(CPU)
	mkdir malloc1\st_$(CPU)
	mkdir math\mt_$(CPU)
	mkdir math\st_$(CPU)
	mkdir math\st_p_$(CPU)
	mkdir mbyte\mt_$(CPU)
	mkdir mbyte\st_$(CPU)
	mkdir mbyte\st_p_$(CPU)
	mkdir misc\mt_$(CPU)
	mkdir misc\st_$(CPU)
	mkdir misc\st_p_$(CPU)
	mkdir moddef\$(CPU)
	mkdir nls\mt_$(CPU)
	mkdir nls\st_$(CPU)
	mkdir nls\st_p_$(CPU)
	mkdir omflib\$(CPU)
	mkdir os2_$(CPU)\st
	mkdir os2_$(CPU)\st_p
	mkdir process\mt_$(CPU)
	mkdir process\st_$(CPU)
	mkdir process\st_p_$(CPU)
	mkdir socket\$(CPU)
	mkdir startup\mt_$(CPU)
	mkdir startup\st_$(CPU)
	mkdir startup\st_p_$(CPU)
	mkdir static\$(CPU)
	mkdir str\mt_$(CPU)
	mkdir str\st_$(CPU)
	mkdir str\st_p_$(CPU)
	mkdir sys\mt_$(CPU)
	mkdir sys\st_$(CPU)
	mkdir termios\mt_$(CPU)
	mkdir termios\st_$(CPU)
	mkdir termios\st_p_$(CPU)
	mkdir time\mt_$(CPU)
	mkdir time\st_$(CPU)
	mkdir time\st_p_$(CPU)
	mkdir tmalloc\$(CPU)
	mkdir video\$(CPU)
