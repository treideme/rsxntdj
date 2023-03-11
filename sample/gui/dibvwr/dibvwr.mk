#
# DOS only, written by Alfons Hoogervorst, 1997, proteus@worldaccess.nl
# Generic make file. Should work with every make utility. If it doesn't
# don't blame me.
#

RESPFILE    = dibvwr.xxx
UOPTS       = -Zwin32
UINCS       = ./include

OBJS        = dibvwr.o dibwin.o    dibfunc.o   dbvabout.o  dibopen.o \
              windbg.o  winfuncs.o  cdlgtool.o  bmpfile.o

COPTS       = $(UOPTS) -I$(UINCS) -DDEBUG=1


all         : openresp dibvwr.exe closeresp
        @echo Done

clean:
            del dibvwr.o
            del dibwin.o
            del dibfunc.o
            del dbvabout.o
            del dibopen.o
            del windbg.o
            del winfuncs.o
            del cdlgtool.o
            del bmpfile.o
            del dibvwr.res

openresp    :
        @echo $(COPTS) > $(RESPFILE)
        @echo dibvwr.o >> $(RESPFILE)
        @echo dibwin.o >> $(RESPFILE)
        @echo dibfunc.o >> $(RESPFILE)
        @echo dbvabout.o >> $(RESPFILE)
        @echo dibopen.o >> $(RESPFILE)
        @echo windbg.o >> $(RESPFILE)
        @echo winfuncs.o >> $(RESPFILE)
        @echo cdlgtool.o >> $(RESPFILE)
        @echo bmpfile.o >> $(RESPFILE)
        @echo -lcomdl >> $(RESPFILE)
        @echo -odibvwr.exe >> $(RESPFILE)

closeresp   :
        del $(RESPFILE)

dibvwr.exe  :   $(OBJS) dibvwr.res
        gcc @$(RESPFILE)
        rsrc dibvwr.res dibvwr.exe

dibvwr.res  :   dibvwr.rc   dibvwr.h    ico100.ico  bmp99.bmp \
    dibfunc.rc  dibopen.rc  bmp016.bmp  bmp256.bmp  bmpgray.bmp \
    dibopen.rh
        grc -r dibvwr.rc    

dibvwr.o    :   dibvwr.c \
    bmpfile.h   dbvabout.h  dibfunc.h   dibopen.h   dibvwr.h \
    dibwin.h    windbg.h    winfuncs.h
        gcc $(COPTS) -c dibvwr.c -odibvwr.o

dibwin.o    :   dibwin.c \
    dibfunc.h   dibwin.h    windbg.h    winfuncs.h
        gcc $(COPTS) -c dibwin.c -odibwin.o

dibfunc.o   :   dibfunc.c \
    dibfunc.h   windbg.h    winfuncs.h
        gcc $(COPTS) -c dibfunc.c -odibfunc.o
    
dbvabout.o  :   dbvabout.c \
    dbvabout.h  dibfunc.h   dibwin.h    windbg.h    winfuncs.h
        gcc $(COPTS) -c dbvabout.c -odbvabout.o

dibopen.o   :   dibopen.c \
    bmpfile.h   cdlgtool.h  dibfunc.h   dibwin.h    dibopen.h \
    dibopen.rh  windbg.h    winfuncs.h
        gcc $(COPTS) -c dibopen.c -odibopen.o

windbg.o    :   windbg.c    windbg.h
        gcc $(COPTS) -c windbg.c -owindbg.o

winfuncs.o  :   winfuncs.c  winfuncs.h
        gcc $(COPTS) -c winfuncs.c -owinfuncs.o

cdlgtool.o  :   cdlgtool.c  cdlgtool.h
        gcc $(COPTS) -c cdlgtool.c -ocdlgtool.o

bmpfile.o   :   bmpfile.c   bmpfile.h   dibfunc.h   windbg.h
        gcc $(COPTS) -c bmpfile.c -obmpfile.o           
