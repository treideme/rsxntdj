#
# /emx/src/lib/process/makefile
#
.INCLUDE: /emx/src/lib/libc.mak

local: ;

beginthr.o: beginthr.c $(I)stdlib.h $(ERRNO) $(I)os2emx.h $(I)emx/syscalls.h \
		$(I)emx/thread.h
execl.o: execl.c $(PROCESS) $(I)stddef.h $(I)stdarg.h
execle.o: execle.c $(PROCESS) $(I)stddef.h $(I)stdarg.h
execlp.o: execlp.c $(PROCESS) $(I)stddef.h $(I)stdarg.h
execlpe.o: execlpe.c $(PROCESS) $(I)stddef.h $(I)stdarg.h
execv.o: execv.c $(PROCESS)
execve.o: execve.c $(PROCESS)
execvp.o: execvp.c $(PROCESS)
execvpe.o: execvpe.c $(PROCESS)
fmutex.o: fmutex.c $(I)os2emx.h $(I)stdlib.h $(BUILTIN) $(S)fmutex.h \
		$(S)smutex.h
fmutex2.o: fmutex2.c $(I)stdlib.h $(BUILTIN) $(S)fmutex.h
fork.o: fork.c $(I)emx/syscalls.h $(PROCESS)
getpid.o: getpid.c $(I)emx/syscalls.h $(PROCESS)
getppid.o: getppid.c $(I)emx/syscalls.h $(PROCESS)
gettid.o: gettid.c $(ASM386H)
kill.o: kill.c $(I)emx/syscalls.h $(SIGNAL)
pause.o: pause.c $(I)emx/syscalls.h $(SIGNAL) $(ERRNO)
profil.o: profil.c $(I)emx/syscalls.h $(I)stdlib.h $(I)stddef.h $(ERRNO)
ptrace.o: ptrace.c $(I)sys/ptrace.h
raise.o: raise.c $(I)emx/syscalls.h $(SIGNAL)
rmutex.o: rmutex.c $(I)stdlib.h $(BUILTIN) $(S)fmutex.h $(S)rmutex.h
sigactio.o: sigactio.c $(I)emx/syscalls.h $(SIGNAL)
sigaddse.o: sigaddse.c $(SIGNAL) $(ERRNO)
sigdelse.o: sigdelse.c $(SIGNAL) $(ERRNO)
sigempty.o: sigempty.c $(SIGNAL)
sigfills.o: sigfills.c $(SIGNAL)
sigismem.o: sigismem.c $(SIGNAL) $(ERRNO)
signal.o: signal.c $(I)emx/syscalls.h $(SIGNAL)
sigpendi.o: sigpendi.c $(I)emx/syscalls.h $(SIGNAL)
sigprocm.o: sigprocm.c $(I)emx/syscalls.h $(SIGNAL)
sigsuspe.o: sigsuspe.c $(I)emx/syscalls.h $(SIGNAL)
smutex.o: smutex.c $(I)os2emx.h $(BUILTIN) $(S)smutex.h
spawnl.o: spawnl.c $(PROCESS) $(I)stddef.h $(I)stdarg.h
spawnle.o: spawnle.c $(PROCESS) $(I)stddef.h $(I)stdarg.h
spawnlp.o: spawnlp.c $(PROCESS) $(I)stddef.h $(I)stdarg.h
spawnlpe.o: spawnlpe.c $(PROCESS) $(I)stddef.h $(I)stdarg.h
spawnv.o: spawnv.c $(PROCESS) $(I)stddef.h
spawnve.o: spawnve.c $(I)emx/syscalls.h $(I)stdlib.h $(PROCESS) $(I)string.h \
		$(ERRNO) $(I)emx/startup.h
spawnvp.o: spawnvp.c $(PROCESS) $(I)stddef.h
spawnvpe.o: spawnvpe.c $(PROCESS) $(I)stdlib.h
system.o: system.c $(PROCESS) $(I)stdlib.h $(I)string.h $(ERRNO) $(I)io.h
thread.o: thread.c $(ASM386H)
threadid.o: threadid.c $(ASM386H)
threadst.o: threadst.c $(I)stdlib.h $(I)emx/syscalls.h $(I)emx/thread.h
wait.o: wait.c $(I)emx/syscalls.h $(I)stdlib.h $(PROCESS) $(ERRNO)
waitpid.o: waitpid.c $(I)emx/syscalls.h $(I)stdlib.h $(PROCESS) $(ERRNO)
_errno.o: _errno.c $(ASM386H)

$(DSTLIB): beginthr.o execl.o execle.o execlp.o execlpe.o \
    execv.o execve.o execvp.o execvpe.o fmutex.o fmutex2.o fork.o getpid.o \
    getppid.o gettid.o kill.o pause.o profil.o ptrace.o raise.o rmutex.o \
    sigactio.o sigaddse.o sigdelse.o sigempty.o sigfills.o sigismem.o \
    signal.o sigpendi.o sigprocm.o sigsuspe.o smutex.o spawnl.o spawnle.o \
    spawnlp.o spawnlpe.o spawnv.o spawnve.o spawnvp.o spawnvpe.o system.o \
    thread.o threadid.o threadst.o wait.o waitpid.o _errno.o
	$(AR) r $(DSTLIB) *.o
