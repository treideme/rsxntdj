# dmake.ini

__.SILENT := $(.SILENT)
.SILENT   := yes

.IMPORT: COMSPEC
.IMPORT .IGNORE: MAKE_SH

DIRSEPSTR   := /

#
# Do not define MAKE_SH if you want to use the standard command processor
#
.IF $(MAKE_SH) == $(NULL)

SHELL       := $(COMSPEC)
SHELLFLAGS  := /c
GROUPFLAGS  := $(SHELLFLAGS)
SHELLMETAS  := *"?<>|&
DIVFILE      = $(TMPFILE:s,/,\)

.IF $(COMSPEC:s,.,/,:f) == COM
GROUPSUFFIX := .bat
.ELIF $(COMSPEC:s,.,/,:f) == com
GROUPSUFFIX := .bat
.ELSE
GROUPSUFFIX := .cmd
.END

#
# Define MAKE_SH (path name) to use a Unix-like shell
#
.ELSE

SHELL       := $(MAKE_SH)
SHELLFLAGS  := -c
GROUPFLAGS  :=
SHELLMETAS  := *"?<>|()&][$$\#`'
GROUPSUFFIX := .sh
DIVFILE      = $(TMPFILE:s,/,${DIVSEP_shell_${USESHELL}})
DIVSEP_shell_yes := \\\
DIVSEP_shell_no  := \\

.END

GROUPSHELL  := $(SHELL)

.USESHELL :

CC          := gcc
AS          := as
LD          := gcc
AR          := ar
RANLIB      := ar s
RM          := del
YACC        := bison
LEX         := flex

MAKE         = $(MAKECMD) $(MFLAGS)

%.o : %.c ; $(CC) $(CFLAGS) -o $@ -c $<

%.o : %.s ; $(AS) $(ASFLAGS) -o $@ $<

%.exe : %.o ; $(LD) $(LDFLAGS) -o $@ $< $(LDLIBS)

%.c : %.y ; $(YACC) -o $@ $(YFLAGS) $<

%.c : %.l ; $(LEX)  -o $@ $(LFLAGS) $<

.SILENT := $(__.SILENT)
