/* emx/syscalls.h (emx+gcc) */

#ifndef _EMX_SYSCALLS_H
#define _EMX_SYSCALLS_H

#if defined (__cplusplus)
extern "C" {
#endif

/* __findfirst(), __findnext() */

#define _A_NORMAL 0x00  /* No attributes */
#define _A_RDONLY 0x01  /* Read-only     */
#define _A_HIDDEN 0x02  /* Hidden        */
#define _A_SYSTEM 0x04  /* System        */
#define _A_VOLID  0x08  /* Volume label  */
#define _A_SUBDIR 0x10  /* Directory     */
#define _A_ARCH   0x20  /* Archive       */

/* __open() */

#define _SO_CREAT       0x00010000
#define _SO_EXCL        0x00020000
#define _SO_TRUNC       0x00040000
#define _SO_NOINHERIT   0x00080000
#define _SO_SYNC        0x00100000
#define _SO_SIZE        0x00200000

/* For debugging of signal handlers. */
#define _SIG_MAGIC1     0xfeed6666
#define _SIG_MAGIC2     0x47dead11
#define _SIG_MAGIC3     0x9999beef
#define _SIG_MAGIC4     0xaffe0815

#if !defined (_SIGSET_T)
#define _SIGSET_T
typedef unsigned long sigset_t;
#endif

#if !defined (_SIZE_T)
#define _SIZE_T
typedef unsigned long size_t;
#endif


struct hostent;
struct netent;
struct protoent;
struct servent;
struct sigaction;
struct sockaddr;
struct stat;
struct timeb;
struct timeval;
struct _fd_set;

struct _find
{
  char           reserved[21];
  unsigned char  attr;
  unsigned short time;
  unsigned short date;
  unsigned short size_lo;         /* split due to alignment problems */
  unsigned short size_hi;
  char name[257];                 /* Big buffer for OS/2             */
};

struct _new_proc
{
  unsigned long  arg_off;
  unsigned long  env_off;
  unsigned long  fname_off;
  unsigned short arg_sel;
  unsigned short env_sel;
  unsigned short fname_sel;
  unsigned short arg_count;
  unsigned short arg_size;
  unsigned short env_count;
  unsigned short env_size;
  unsigned short mode;
  unsigned short mode2;         /* Present only if (mode & 0x8000) */
};

struct _profil
{
  unsigned cb;
  void *buff;
  unsigned bufsiz;
  unsigned offset;
  unsigned scale;
};

struct _recvfrom
{
  int handle;
  void *buf;
  int len;
  unsigned flags;
  struct sockaddr *from;
  int *pfromlen;
};

struct _select
{
  int              nfds;
  struct _fd_set * readfds;
  struct _fd_set * writefds;
  struct _fd_set * exceptfds;
  struct timeval * timeout;
};

struct _sendto
{
  int handle;
  __const__ void *buf;
  int len;
  unsigned flags;
  __const__ struct sockaddr *to;
  int tolen;
};


int __accept (int handle, struct sockaddr *addr, int *paddrlen);
unsigned __alarm (unsigned sec);
int __bind (int handle, __const__ struct sockaddr *addr, int addrlen);
void *__brk (void *addr);
void __cgets (char *buffer);
int __chdir (__const__ char *name);
int __chmod (__const__ char *name, int flag, int attr);
int __chdrive (char drive);
int __chsize (int handle, long length);
long long __clock (void);
int __close (int handle);
int __connect (int handle, __const__ struct sockaddr *addr, int addrlen);
int __core (int handle);
int __dup (int handle);
int __dup2 (int handle1, int handle2);
int __endthread (int tid);
int __execname (char *buf, size_t bufsize);
void __exit (int ret) __attribute__ ((__noreturn__));
int __fcntl (int handle, int request, int arg);
int __filesys (__const__ char *drive, char *name, size_t size);
int __findfirst (__const__ char *name, int attr, struct _find *fp);
int __findnext (struct _find *fp);
int __fork (void);
int __fstat (int handle, struct stat *buffer);
int __fsync (int handle);
void __ftime (struct timeb *ptr);
int __ftruncate (int handle, long length);
int __getcwd (char *buffer, char drive);
char __getdrive (void);
int __gethostbyaddr (__const__ char *addr, int len, int type,
    struct hostent **dst);
int __gethostbyname (__const__ char *name, struct hostent **dst);
int __gethostid (int *dst);
int __gethostname (char *name, int len);
int __getnetbyname (__const__ char *name, struct netent **dst);
int __getnetbyaddr (long net, struct netent **dst);
int __getpeername (int handle, struct sockaddr *name, int *pnamelen);
int __getpid (void);
int __getppid (void);
int __getprotobyname (__const__ char *name, struct protoent **dst);
int __getprotobynumber (int prot, struct protoent **dst);
int __getservbyname (__const__ char *name, __const__ char *proto,
    struct servent **dst);
int __getservbyport (int port, __const__ char *proto, struct servent **dst);
int __getsockhandle (int handle);
int __getsockname (int handle, struct sockaddr *name, int *pnamelen);
int __getsockopt (int handle, int level, int optname, void *optval,
    int *poptlen);
int __imphandle (int handle);
int __impsockhandle (int handle, int flags);
int __initthread (void *preg);
int __ioctl1 (int handle, int code);
int __ioctl2 (int handle, int request, int arg);
int __kill (int pid, int sig);
int __listen (int handle, int backlog);
int __lseek (int handle, long offset, int origin);
void *__memaccess (unsigned first, unsigned last, int flag);
int __memavail (void);
int __mkdir (__const__ char *name);
int __newthread (int tid);
int __nls_ctype (unsigned char *buf);
void __nls_memupr (unsigned char *buf, size_t size);
int __open (__const__ char *name, int flags, unsigned long size);
void __pause (void);
int __pipe (int *two_handles, int pipe_size);
int __portaccess (unsigned first, unsigned last);
int __profil (__const__ struct _profil *p);
int __ptrace (int request, int pid, int addr, int data);
int __raise (int sig);
int __read (int handle, void *buf, size_t nbyte);
int __read_kbd (int echo, int wait, int sig);
int __recv (int handle, void *buf, int len, unsigned flags);
int __recvfrom (__const__ struct _recvfrom *args);
int __remove (__const__ char *name);
int __rename (__const__ char *old_name, __const__ char *new_name);
int __rmdir (__const__ char *name);
void *__sbrk (int incr);
void __scrsize (int *dst);
int __select (struct _select *args);
int __send (int handle, __const__ void *buf, int len, unsigned flags);
int __sendto (__const__ struct _sendto *args);
int __setsockopt (int handle, int level, int optname, __const__ void *optval,
    int optlen);
int __setsyserrno (int e);
int __settime (const struct timeval *tp);
int __shutdown (int handle, int how);
int __sigaction (int _sig, __const__ struct sigaction *_iact,
    struct sigaction *_oact);
void (*__signal (int sig, void (*handler)()))(int sig);
int __sigpending (sigset_t *_set);
int __sigprocmask (int _how, __const__ sigset_t *_iset, sigset_t *_oset);
int __sigsuspend (__const__ sigset_t *_mask);
unsigned __sleep (unsigned sec);
unsigned __sleep2 (unsigned millisec);
int __socket (int domain, int type, int protocol);
int __spawnve (struct _new_proc *np);
int __stat (__const__ char *name, struct stat *buffer);
int __swchar (int flag, int new_char);
int __syserrno (void);
int __uflags (int mask, int new_flags);
long __ulimit (int cmd, long new_limit);
int __umask (int pmode);
void __unwind2 (void *xcpt_reg_ptr);
int __utimes (__const__ char *name, __const__ struct timeval *tvp);
int __ttyname (int handle, char *buf, size_t buf_size);
int __wait (int *status);
int __waitpid (int pid, int *status, int options);
int __write (int handle, __const__ void *buf, size_t nbyte);



#if defined (__cplusplus)
}
#endif

#endif /* not _EMX_SYSCALLS_H */
