# makefile for emx

CC = gcc
RC = rc
RSRC = rsrc
CFLAGS = -O2 -Wall -mprobe
AFLAGS =
LDFLAGS = -Zwin32 -s

.c.o:
        $(CC) -c $(CFLAGS) $<

OBJS = \
        rsxide.o   \
        editdde.o  \
        idedlg.o   \
        runw32.o   \
        runw32s.o  \
        tgtflags.o

rsxide.exe: $(OBJS) rsxide.res
        $(CC) $(LDFLAGS) -o rsxide.exe $(OBJS) -lcomdlg32 -lcomctl32 -lshell32
        $(RSRC) rsxide.res rsxide.exe

rsxide.res: rsxide.rc
        $(RC) -r rsxide.rc
