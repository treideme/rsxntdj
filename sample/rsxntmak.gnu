###############################################################################
#
# Makefile include file for rsxnt
#
# Default: no crtdll, no syslib, no debug info, Optimize
#
# Call 'make crt=1' to use the C runtime dll
# Call 'make multi=1' to build multithread app / use multithread dll
# Call 'make dual=1' to build dual-mode win32/dos32 program
# Call 'make sys=1' to build stand-alone exe
# Call 'make debug=1' to include debug info
#
###############################################################################

ifdef crt
ifdef dual
dual=
endif
endif

ifdef dual
GCCFLAGS=
else
ifdef crt
GCCFLAGS=-Zcrtdll=crtrs
else
ifdef sys
GCCFLAGS=-Zsys
else
GCCFLAGS=
endif
endif
endif

ifdef multi
MTFLAG = -Zmt
else
MTFLAG =
endif

ifdef debug
CFLAGS	= -Wall -g
LDFLAGS = -g
else
CFLAGS	= -Wall -O
LDFLAGS =
endif

DLLFLAGS = -Zdll

###############################################################################

CC      = gccw32 $(GCCFLAGS) $(MTFLAG)
CXX     = gccw32 $(GCCFLAGS) $(MTFLAG)
LD      = gccw32 $(GCCFLAGS) $(MTFLAG)
RC      = grc
RCFLAGS = -r
RES	= rsrc
RSRC	= rsrc
RESFLAGS=
IMPLIB	= makelib
RSXNTOPT= rsxntopt

.SUFFIXES: .exe .res .a .o .c .cpp .cc .rc .p .f .F .r .y .l .s .S .def .h

.o.exe:
	$(CC) $(LDFLAGS) $<

.c.o:
	$(CC) -c $(CFLAGS) $<

.cc.o:
	$(CC) -c $(CFLAGS) $<

.cpp.o:
	$(CC) -c $(CFLAGS) $<

.rc.res:
	$(RC) $(RCFLAGS) $<


###############################################################################

ifdef PROJECT

LINKCMD = $(CC) $(LDFLAGS) -o $(PROJECT).exe $(OBJS) $(LIBS)
RESCMD  = $(RSRC) -o $(PROJECT).exe $(PROJECT).res
OPTCMD	= $(RSXNTOPT) -b $(PROJECT).exe

ifdef RESOURCES
        LINK2 = $(RESCMD)
	RESES = $(PROJECT).res
else
        LINK2 =
	RESES = 
endif

ifdef BIND
        LINK3 = $(OPTCMD) $(BIND)
else
        LINK3 =
endif

$(PROJECT).exe: $(OBJS) $(RESES)
	$(LINKCMD)
	$(LINK2)
	$(LINK3)
endif
