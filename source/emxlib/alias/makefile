#
# /emx/src/lib/alias/makefile
#
.INCLUDE: /emx/src/lib/lib0.mak

.PHONY: clean default alias dstlib alias1 alias2

LIBALIAS=$(L)c_alias.a

default: alias

alias .SETDIR=$(CPU):
	$(MAKE) -f ../makefile dstlib $(PASSDOWN)

dstlib: $(LIBALIAS)

clean:
	-del $(CPU)\*.o $(DELOPT)

access.o:
	emxalias access _access access.o
acosl.o:
	emxalias acosl _acosl acosl.o
alarm.o:
	emxalias alarm _alarm alarm.o
asinl.o:
	emxalias asinl _asinl asinl.o
atan2l.o:
	emxalias atan2l _atan2l atan2l.o
atanl.o:
	emxalias atanl _atanl atanl.o
atold.o:
	emxalias _atold _atofl atold.o
bcmp.o:
	emxalias bcmp _bcmp bcmp.o
bcopy.o:
	emxalias bcopy _bcopy bcopy.o
brk.o:
	emxalias brk _brk brk.o
bzero.o:
	emxalias bzero _bzero bzero.o
cbrt.o:
	emxalias cbrt _cbrt cbrt.o
ceill.o:
	emxalias ceill _ceill ceill.o
cfgetisp.o:
	emxalias cfgetispeed _cfgetispeed cfgetisp.o
cfgetosp.o:
	emxalias cfgetospeed _cfgetospeed cfgetosp.o
cfsetisp.o:
	emxalias cfsetispeed _cfsetispeed cfsetisp.o
cfsetosp.o:
	emxalias cfsetospeed _cfsetospeed cfsetosp.o
chdir.o:
	emxalias chdir _chdir chdir.o
chmod.o:
	emxalias chmod _chmod chmod.o
chsize.o:
	emxalias chsize _chsize chsize.o
close.o:
	emxalias close _close close.o
closedir.o:
	emxalias closedir _closedir closedir.o
copysig.o:
	emxalias copysign _copysign copysig.o
copysigf.o:
	emxalias copysignf _copysignf copysigf.o
copysigl.o:
	emxalias copysignl _copysignl copysigl.o
coshl.o:
	emxalias coshl _coshl coshl.o
cosl.o:
	emxalias cosl _cosl cosl.o
creat.o:
	emxalias creat _creat creat.o
cuserid.o:
	emxalias cuserid _cuserid cuserid.o
daylight.o:
	emxalias daylight _daylight daylight.o
dup.o:
	emxalias dup _dup dup.o
dup2.o:
	emxalias dup2 _dup2 dup2.o
edata.o:
	emxalias edata _edata edata.o
end.o:
	emxalias end _end end.o
endpwent.o:
	emxalias endpwent _endpwent endpwent.o
environ.o:
	emxalias environ _environ environ.o
eof.o:
	emxalias eof _eof eof.o
etext.o:
	emxalias etext _etext etext.o
execl.o:
	emxalias execl _execl execl.o
execle.o:
	emxalias execle _execle execle.o
execlp.o:
	emxalias execlp _execlp execlp.o
execlpe.o:
	emxalias execlpe _execlpe execlpe.o
execv.o:
	emxalias execv _execv execv.o
execve.o:
	emxalias execve _execve execve.o
execvp.o:
	emxalias execvp _execvp execvp.o
execvpe.o:
	emxalias execvpe _execvpe execvpe.o
expl.o:
	emxalias expl _expl expl.o
fabsl.o:
	emxalias fabsl _fabsl fabsl.o
fcloseal.o:
	emxalias fcloseall _fcloseall fcloseal.o
fcntl.o:
	emxalias fcntl _fcntl fcntl.o
fdopen.o:
	emxalias fdopen _fdopen fdopen.o
ffs.o:
	emxalias ffs _ffs ffs.o
fgetchar.o:
	emxalias fgetchar _fgetchar fgetchar.o
fileleng.o:
	emxalias filelength _filelength fileleng.o
flock.o:
	emxalias flock _flock flock.o
floorl.o:
	emxalias floorl _floorl floorl.o
flushall.o:
	emxalias flushall _flushall flushall.o
fmodl.o:
	emxalias fmodl _fmodl fmodl.o
fnmatch.o:
	emxalias fnmatch _fnmatch fnmatch.o
fork.o:
	emxalias fork _fork fork.o
fpathcon.o:
	emxalias fpathconf _fpathconf fpathcon.o
fputchar.o:
	emxalias fputchar _fputchar fputchar.o
frexpl.o:
	emxalias frexpl _frexpl frexpl.o
fstat.o:
	emxalias fstat _fstat fstat.o
fsync.o:
	emxalias fsync _fsync fsync.o
ftime.o:
	emxalias ftime _ftime ftime.o
ftruncat.o:
	emxalias ftruncate _ftruncate ftruncat.o
ftw.o:
	emxalias ftw _ftw ftw.o
gcvt.o:
	emxalias gcvt _gcvt gcvt.o
getcwd.o:
	emxalias getcwd _getcwd getcwd.o
getegid.o:
	emxalias getegid _getegid getegid.o
geteuid.o:
	emxalias geteuid _geteuid geteuid.o
getgid.o:
	emxalias getgid _getgid getgid.o
getgrgid.o:
	emxalias getgrgid _getgrgid getgrgid.o
getgrnam.o:
	emxalias getgrnam _getgrnam getgrnam.o
getgroup.o:
	emxalias getgroups _getgroups getgroup.o
getlogin.o:
	emxalias getlogin _getlogin getlogin.o
getopt.o:
	emxalias getopt _getopt getopt.o
getpages.o:
	emxalias getpagesize _getpagesize getpages.o
getpass.o:
	emxalias getpass _getpass getpass.o
getpgrp.o:
	emxalias getpgrp _getpgrp getpgrp.o
getpid.o:
	emxalias getpid _getpid getpid.o
getppid.o:
	emxalias getppid _getppid getppid.o
getpwent.o:
	emxalias getpwent _getpwent getpwent.o
getpwnam.o:
	emxalias getpwnam _getpwnam getpwnam.o
getpwuid.o:
	emxalias getpwuid _getpwuid getpwuid.o
gettimeo.o:
	emxalias gettimeofday _gettimeofday gettimeo.o
getuid.o:
	emxalias getuid _getuid getuid.o
getw.o:
	emxalias getw _getw getw.o
getwd.o:
	emxalias getwd _getwd getwd.o
glob.o:
	emxalias glob _glob glob.o
globfree.o:
	emxalias globfree _globfree globfree.o
huge.o:
	emxalias HUGE _HUGE_VAL huge.o
hypot.o:
	emxalias hypot _hypot hypot.o
hypotl.o:
	emxalias hypotl _hypotl hypotl.o
index.o:
	emxalias index _index index.o
ioctl.o:
	emxalias ioctl _ioctl ioctl.o
isascii.o:
	emxalias isascii _isascii isascii.o
isatty.o:
	emxalias isatty _isatty isatty.o
kill.o:
	emxalias kill _kill kill.o
ldexpl.o:
	emxalias ldexpl _ldexpl ldexpl.o
lhuge.o:
	emxalias _LHUGE _LHUGE_VAL lhuge.o
log10l.o:
	emxalias log10l _log10l log10l.o
logl.o:
	emxalias logl _logl logl.o
lseek.o:
	emxalias lseek _lseek lseek.o
memccpy.o:
	emxalias memccpy _memccpy memccpy.o
memicmp.o:
	emxalias memicmp _memicmp memicmp.o
mkdir.o:
	emxalias mkdir _mkdir mkdir.o
mkstemp.o:
	emxalias mkstemp _mkstemp mkstemp.o
mktemp.o:
	emxalias mktemp _mktemp mktemp.o
modfl.o:
	emxalias modfl _modfl modfl.o
nextaft.o:
	emxalias nextafter _nextafter nextaft.o
nextaftf.o:
	emxalias nextafterf _nextafterf nextaftf.o
nextaftl.o:
	emxalias nextafterl _nextafterl nextaftl.o
open.o:
	emxalias open _open open.o
opendir.o:
	emxalias opendir _opendir opendir.o
optarg.o:
	emxalias optarg _optarg optarg.o
opterr.o:
	emxalias opterr _opterr opterr.o
optind.o:
	emxalias optind _optind optind.o
optmode.o:
	emxalias optmode _optmode optmode.o
optopt.o:
	emxalias optopt _optopt optopt.o
optswcha.o:
	emxalias optswchar _optswchar optswcha.o
pathconf.o:
	emxalias pathconf _pathconf pathconf.o
pause.o:
	emxalias pause _pause pause.o
pclose.o:
	emxalias pclose _pclose pclose.o
pipe.o:
	emxalias pipe _pipe pipe.o
popen.o:
	emxalias popen _popen popen.o
powl.o:
	emxalias powl _powl powl.o
profil.o:
	emxalias profil _profil profil.o
ptrace.o:
	emxalias ptrace _ptrace ptrace.o
putenv.o:
	emxalias putenv _putenv putenv.o
putw.o:
	emxalias putw _putw putw.o
read.o:
	emxalias read _read read.o
readdir.o:
	emxalias readdir _readdir readdir.o
readv.o:
	emxalias readv _readv readv.o
rewinddi.o:
	emxalias rewinddir _rewinddir rewinddi.o
rindex.o:
	emxalias rindex _rindex rindex.o
rint.o:
	emxalias rint _rint rint.o
rintl.o:
	emxalias rintl _rintl rintl.o
rmdir.o:
	emxalias rmdir _rmdir rmdir.o
sbrk.o:
	emxalias sbrk _sbrk sbrk.o
seekdir.o:
	emxalias seekdir _seekdir seekdir.o
select.o:
	emxalias select _select select.o
setbuffe.o:
	emxalias setbuffer _setbuffer setbuffe.o
setgid.o:
	emxalias setgid _setgid setgid.o
setmode.o:
	emxalias setmode _setmode setmode.o
setnewha.o:
	emxalias set_new_handler _set_new_handler setnewha.o
setpgid.o:
	emxalias setpgid _setpgid setpgid.o
setpwent.o:
	emxalias setpwent _setpwent setpwent.o
settimeo.o:
	emxalias settimeofday _settimeofday settimeo.o
setuid.o:
	emxalias setuid _setuid setuid.o
sigactio.o:
	emxalias sigaction _sigaction sigactio.o
sigaddse.o:
	emxalias sigaddset _sigaddset sigaddse.o
sigdelse.o:
	emxalias sigdelset _sigdelset sigdelse.o
sigempty.o:
	emxalias sigemptyset _sigemptyset sigempty.o
sigfills.o:
	emxalias sigfillset _sigfillset sigfills.o
sigismem.o:
	emxalias sigismember _sigismember sigismem.o
siglongj.o:
	emxalias siglongjmp _siglongjmp siglongj.o
sigpendi.o:
	emxalias sigpending _sigpending sigpendi.o
sigprocm.o:
	emxalias sigprocmask _sigprocmask sigprocm.o
sigsetjm.o:
	emxalias sigsetjmp _sigsetjmp sigsetjm.o
sigsuspe.o:
	emxalias sigsuspend _sigsuspend sigsuspe.o
sinhl.o:
	emxalias sinhl _sinhl sinhl.o
sinl.o:
	emxalias sinl _sinl sinl.o
sleep.o:
	emxalias sleep _sleep sleep.o
snprintf.o:
	emxalias snprintf _snprintf snprintf.o
sopen.o:
	emxalias sopen _sopen sopen.o
spawnl.o:
	emxalias spawnl _spawnl spawnl.o
spawnle.o:
	emxalias spawnle _spawnle spawnle.o
spawnlp.o:
	emxalias spawnlp _spawnlp spawnlp.o
spawnlpe.o:
	emxalias spawnlpe _spawnlpe spawnlpe.o
spawnv.o:
	emxalias spawnv _spawnv spawnv.o
spawnve.o:
	emxalias spawnve _spawnve spawnve.o
spawnvp.o:
	emxalias spawnvp _spawnvp spawnvp.o
spawnvpe.o:
	emxalias spawnvpe _spawnvpe spawnvpe.o
sqrtl.o:
	emxalias sqrtl _sqrtl sqrtl.o
stat.o:
	emxalias stat _stat stat.o
strdup.o:
	emxalias strdup _strdup strdup.o
stricmp.o:
	emxalias stricmp _stricmp stricmp.o
strlwr.o:
	emxalias strlwr _strlwr strlwr.o
strnicmp.o:
	emxalias strnicmp _strnicmp strnicmp.o
strnset.o:
	emxalias strnset _strnset strnset.o
strptime.o:
	emxalias strptime _strptime strptime.o
strrev.o:
	emxalias strrev _strrev strrev.o
strset.o:
	emxalias strset _strset strset.o
strtof.o:
	emxalias strtof _strtof strtof.o
strtold.o:
	emxalias strtold _strtold strtold.o
strupr.o:
	emxalias strupr _strupr strupr.o
swab.o:
	emxalias swab _swab swab.o
sysconf.o:
	emxalias sysconf _sysconf sysconf.o
syserrli.o:
	emxalias sys_errlist _sys_errlist syserrli.o
sysnerr.o:
	emxalias sys_nerr _sys_nerr sysnerr.o
tanhl.o:
	emxalias tanhl _tanhl tanhl.o
tanl.o:
	emxalias tanl _tanl tanl.o
tcdrain.o:
	emxalias tcdrain _tcdrain tcdrain.o
tcflow.o:
	emxalias tcflow _tcflow tcflow.o
tcflush.o:
	emxalias tcflush _tcflush tcflush.o
tcgetatt.o:
	emxalias tcgetattr _tcgetattr tcgetatt.o
tcgetpgr.o:
	emxalias tcgetpgrp _tcgetpgrp tcgetpgr.o
tcsendbr.o:
	emxalias tcsendbreak _tcsendbreak tcsendbr.o
tcsetatt.o:
	emxalias tcsetattr _tcsetattr tcsetatt.o
tcsetpgr.o:
	emxalias tcsetpgrp _tcsetpgrp tcsetpgr.o
tell.o:
	emxalias tell _tell tell.o
telldir.o:
	emxalias telldir _telldir telldir.o
tempnam.o:
	emxalias tempnam _tempnam tempnam.o
times.o:
	emxalias times _times times.o
timezone.o:
	emxalias timezone _timezone timezone.o
toascii.o:
	emxalias toascii _toascii toascii.o
trunc.o:
	emxalias trunc _trunc trunc.o
truncl.o:
	emxalias truncl _truncl truncl.o
truncate.o:
	emxalias truncate _truncate truncate.o
ttyname.o:
	emxalias ttyname _ttyname ttyname.o
tzname.o:
	emxalias tzname _tzname tzname.o
tzset.o:
	emxalias tzset _tzset tzset.o
ulimit.o:
	emxalias ulimit _ulimit ulimit.o
umask.o:
	emxalias umask _umask umask.o
uname.o:
	emxalias uname _uname uname.o
unlink.o:
	emxalias unlink _unlink unlink.o
utime.o:
	emxalias utime _utime utime.o
utimes.o:
	emxalias utimes _utimes utimes.o
vsnprint.o:
	emxalias vsnprintf _vsnprintf vsnprint.o
wait.o:
	emxalias wait _wait wait.o
waitpid.o:
	emxalias waitpid _waitpid waitpid.o
write.o:
	emxalias write _write write.o
writev.o:
	emxalias writev _writev writev.o


alias1: access.o acosl.o alarm.o asinl.o atan2l.o atanl.o atold.o \
    bcmp.o bcopy.o brk.o bzero.o cbrt.o ceill.o cfgetisp.o cfgetosp.o \
    cfsetisp.o cfsetosp.o chdir.o chmod.o chsize.o close.o closedir.o \
    copysig.o copysigf.o copysigl.o \
    coshl.o cosl.o creat.o cuserid.o daylight.o dup.o dup2.o edata.o \
    end.o endpwent.o environ.o eof.o etext.o execl.o execle.o execlp.o \
    execlpe.o execv.o execve.o execvp.o execvpe.o expl.o fabsl.o fcloseal.o \
    fcntl.o fdopen.o ffs.o fgetchar.o fileleng.o flock.o floorl.o flushall.o \
    fmodl.o fnmatch.o fork.o fpathcon.o fputchar.o frexpl.o fstat.o fsync.o \
    ftime.o ftruncat.o ftw.o gcvt.o getcwd.o getegid.o geteuid.o getgid.o \
    getgrgid.o getgrnam.o getgroup.o getlogin.o getopt.o getpages.o \
    getpass.o getpgrp.o getpid.o getppid.o getpwent.o getpwnam.o \
    getpwuid.o gettimeo.o getuid.o getw.o getwd.o glob.o globfree.o huge.o \
    hypot.o hypotl.o index.o ioctl.o isascii.o isatty.o kill.o ldexpl.o \
    lhuge.o log10l.o logl.o lseek.o memccpy.o memicmp.o mkdir.o mkstemp.o \
    mktemp.o modfl.o nextaft.o nextaftf.o nextaftl.o

alias2: open.o opendir.o optarg.o opterr.o optind.o optmode.o \
    optopt.o optswcha.o pathconf.o pause.o pclose.o pipe.o popen.o powl.o \
    profil.o ptrace.o putenv.o putw.o read.o readdir.o readv.o rewinddi.o \
    rindex.o rint.o rintl.o rmdir.o sbrk.o seekdir.o select.o setbuffe.o \
    setgid.o setmode.o setnewha.o setpgid.o setpwent.o settimeo.o setuid.o \
    sigactio.o sigaddse.o sigdelse.o sigempty.o sigfills.o sigismem.o \
    siglongj.o sigpendi.o sigprocm.o sigsetjm.o sigsuspe.o sinhl.o sinl.o \
    sleep.o snprintf.o sopen.o spawnl.o spawnle.o spawnlp.o spawnlpe.o \
    spawnv.o spawnve.o spawnvp.o spawnvpe.o sqrtl.o stat.o strdup.o \
    stricmp.o strlwr.o strnicmp.o strnset.o strptime.o strrev.o strset.o \
    strtof.o strtold.o strupr.o swab.o sysconf.o syserrli.o sysnerr.o \
    tanhl.o tanl.o tcdrain.o tcflow.o tcflush.o tcgetatt.o tcgetpgr.o \
    tcsendbr.o tcsetatt.o tcsetpgr.o tell.o telldir.o tempnam.o times.o \
    timezone.o toascii.o trunc.o truncl.o truncate.o ttyname.o tzname.o \
    tzset.o ulimit.o umask.o uname.o unlink.o utime.o utimes.o vsnprint.o \
    wait.o waitpid.o write.o writev.o
$(LIBALIAS): alias1 alias2
	-del $(LIBALIAS)
	$(AR) r $(LIBALIAS) *.o
