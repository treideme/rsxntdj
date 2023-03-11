#
# /emx/src/lib/emx_386/makefile
#
.INCLUDE: /emx/src/lib/lib0.mak

.PHONY: clean default dstlib emx emx2 emxio emxmt emxst

.SOURCE.c: ..
.SOURCE.h: ..
.SOURCE.s: ..

LIBEMX2  = $(L)emx2.a
LIBEMXIO = $(L)emxio.a

DSTLIB=$(L)$(DIRNAME)\emx.a
LIBC_CCFLAGS=-I..

default:    emx

emx .SEQUENTIAL: emx2 emxst emxmt

emx2: $(LIBEMX2)

emxio: $(LIBEMXIO)

emxmt .SETDIR=mt:
	$(MAKE) -f ../makefile dstlib DIRNAME=mt MT_CCFLAGS=-Zmt

emxst .SETDIR=st:
	$(MAKE) -f ../makefile dstlib DIRNAME=st MT_CCFLAGS=

dstlib: $(DSTLIB)

clean:
	-del *.o $(DELOPT)
	-del mt\*.o $(DELOPT)
	-del st\*.o $(DELOPT)

accept.o: accept.s syscalls.h $(ASM386H)
alarm.o: alarm.s syscalls.h $(ASM386H)
bind.o: bind.s syscalls.h $(ASM386H)
brk.o: brk.s syscalls.h $(ASM386H)
cgets.o: cgets.s syscalls.h $(ASM386H)
chdir.o: chdir.s syscalls.h $(ASM386H)
chdrive.o: chdrive.s syscalls.h $(ASM386H)
chmod.o: chmod.s syscalls.h $(ASM386H)
chsize.o: chsize.s syscalls.h $(ASM386H)
clock.o: clock.s syscalls.h $(ASM386H)
close.o: close.s syscalls.h $(ASM386H)
connect.o: connect.s syscalls.h $(ASM386H)
core.o: core.s syscalls.h $(ASM386H)
dos.o: dos.s
dup.o: dup.s syscalls.h $(ASM386H)
dup2.o: dup2.s syscalls.h $(ASM386H)
emx_ver.o: emx_ver.s syscalls.h $(ASM386H)
endthrea.o: endthrea.s syscalls.h $(ASM386H)
execname.o: execname.s syscalls.h $(ASM386H)
exit.o: exit.s syscalls.h $(ASM386H)
fcntl.o: fcntl.s syscalls.h $(ASM386H)
filesys.o: filesys.s syscalls.h $(ASM386H)
findfirs.o: findfirs.s syscalls.h $(ASM386H)
findnext.o: findnext.s syscalls.h $(ASM386H)
fork.o: fork.s syscalls.h $(ASM386H)
fstat.o: fstat.s syscalls.h $(ASM386H)
fsync.o: fsync.s syscalls.h $(ASM386H)
ftime.o: ftime.s syscalls.h $(ASM386H)
ftruncat.o: ftruncat.s syscalls.h $(ASM386H)
getcwd.o: getcwd.s syscalls.h $(ASM386H)
getdrive.o: getdrive.s syscalls.h $(ASM386H)
gethosti.o: gethosti.s syscalls.h $(ASM386H)
gethostn.o: gethostn.s syscalls.h $(ASM386H)
getpeern.o: getpeern.s syscalls.h $(ASM386H)
getpid.o: getpid.s syscalls.h $(ASM386H)
getppid.o: getppid.s syscalls.h $(ASM386H)
getsockh.o: getsockh.s syscalls.h $(ASM386H)
getsockn.o: getsockn.s syscalls.h $(ASM386H)
getsocko.o: getsocko.s syscalls.h $(ASM386H)
ghostbya.o: ghostbya.s syscalls.h $(ASM386H)
ghostbyn.o: ghostbyn.s syscalls.h $(ASM386H)
gnetbyad.o: gnetbyad.s syscalls.h $(ASM386H)
gnetbyna.o: gnetbyna.s syscalls.h $(ASM386H)
gprotbna.o: gprotbna.s syscalls.h $(ASM386H)
gprotbnu.o: gprotbnu.s syscalls.h $(ASM386H)
gservbyn.o: gservbyn.s syscalls.h $(ASM386H)
gservbyp.o: gservbyp.s syscalls.h $(ASM386H)
imphandl.o: imphandl.s syscalls.h $(ASM386H)
impsockh.o: impsockh.s syscalls.h $(ASM386H)
initthre.o: initthre.s syscalls.h $(ASM386H)
ioctl1.o: ioctl1.s syscalls.h $(ASM386H)
ioctl2.o: ioctl2.s syscalls.h $(ASM386H)
kill.o: kill.s syscalls.h $(ASM386H)
listen.o: listen.s syscalls.h $(ASM386H)
lseek.o: lseek.s syscalls.h $(ASM386H)
memacces.o: memacces.s syscalls.h $(ASM386H)
memavail.o: memavail.s syscalls.h $(ASM386H)
mkdir.o: mkdir.s syscalls.h $(ASM386H)
newthrea.o: newthrea.s syscalls.h $(ASM386H)
nls_memu.o: nls_memu.s syscalls.h $(ASM386H)
nls_ctyp.o: nls_ctyp.s syscalls.h $(ASM386H)
open.o: open.s syscalls.h $(ASM386H)
os_ver.o: os_ver.s syscalls.h $(ASM386H)
pause.o: pause.s syscalls.h $(ASM386H)
pipe.o: pipe.s syscalls.h $(ASM386H)
portacce.o: portacce.s syscalls.h $(ASM386H)
profil.o: profil.s syscalls.h $(ASM386H)
ptrace.o: ptrace.s syscalls.h $(ASM386H)
raise.o: raise.s syscalls.h $(ASM386H)
read.o: read.s syscalls.h $(ASM386H)
read_kbd.o: read_kbd.s syscalls.h $(ASM386H)
recv.o: recv.s syscalls.h $(ASM386H)
recvfrom.o: recvfrom.s syscalls.h $(ASM386H)
remove.o: remove.s syscalls.h $(ASM386H)
rename.o: rename.s syscalls.h $(ASM386H)
rmdir.o: rmdir.s syscalls.h $(ASM386H)
sbrk.o: sbrk.s syscalls.h $(ASM386H)
scrsize.o: scrsize.s syscalls.h $(ASM386H)
select.o: select.s syscalls.h $(ASM386H)
send.o: send.s syscalls.h $(ASM386H)
sendto.o: sendto.s syscalls.h $(ASM386H)
setsocko.o: setsocko.s syscalls.h $(ASM386H)
settime.o: settime.s syscalls.h $(ASM386H)
shutdown.o: shutdown.s syscalls.h $(ASM386H)
sigactio.o: sigactio.s syscalls.h $(ASM386H)
signal.o: signal.s syscalls.h $(ASM386H)
sigpendi.o: sigpendi.s syscalls.h $(ASM386H)
sigprocm.o: sigprocm.s syscalls.h $(ASM386H)
sigsuspe.o: sigsuspe.s syscalls.h $(ASM386H)
sleep.o: sleep.s syscalls.h $(ASM386H)
sleep2.o: sleep2.s syscalls.h $(ASM386H)
socket.o: socket.s syscalls.h $(ASM386H)
spawnve.o: spawnve.s syscalls.h $(ASM386H)
stat.o: stat.s syscalls.h $(ASM386H)
swchar.o: swchar.s syscalls.h $(ASM386H)
syserrno.o: syserrno.s syscalls.h $(ASM386H)
ttyname.o: ttyname.s syscalls.h $(ASM386H)
uflags.o: uflags.s syscalls.h $(ASM386H)
ulimit.o: ulimit.s syscalls.h $(ASM386H)
umask.o: umask.s syscalls.h $(ASM386H)
unwind.o: unwind.s syscalls.h $(ASM386H)
utimes.o: utimes.s syscalls.h $(ASM386H)
wait.o: wait.s syscalls.h $(ASM386H)
waitpid.o: waitpid.s syscalls.h $(ASM386H)
write.o: write.s syscalls.h $(ASM386H)


$(DSTLIB): accept.o alarm.o bind.o brk.o cgets.o chdir.o chdrive.o \
    chmod.o chsize.o clock.o close.o connect.o core.o dup.o dup2.o \
    emx_ver.o endthrea.o execname.o exit.o fcntl.o filesys.o \
    findfirs.o findnext.o fork.o fstat.o fsync.o ftime.o ftruncat.o \
    getcwd.o getdrive.o gethosti.o gethostn.o getpeern.o getpid.o \
    getppid.o getsockh.o getsockn.o getsocko.o ghostbya.o ghostbyn.o \
    gnetbyad.o gnetbyna.o gprotbna.o gprotbnu.o gservbyn.o gservbyp.o \
    imphandl.o impsockh.o initthre.o ioctl1.o ioctl2.o kill.o listen.o \
    lseek.o memacces.o memavail.o mkdir.o newthrea.o nls_ctyp.o nls_memu.o \
    open.o os_ver.o pause.o pipe.o portacce.o profil.o ptrace.o raise.o \
    read.o read_kbd.o recv.o recvfrom.o remove.o rename.o rmdir.o sbrk.o \
    scrsize.o select.o send.o sendto.o setsocko.o settime.o shutdown.o \
    sigactio.o signal.o sigpendi.o sigprocm.o sigsuspe.o sleep.o \
    sleep2.o socket.o spawnve.o stat.o swchar.o syserrno.o ttyname.o \
    uflags.o ulimit.o umask.o unwind.o utimes.o wait.o waitpid.o write.o
	-del $(DSTLIB)
	$(AR) r $(DSTLIB) *.o

$(LIBEMX2): emx.imp dos.o
	ar r $(LIBEMX2) dos.o

