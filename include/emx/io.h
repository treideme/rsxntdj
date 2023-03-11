/* emx/io.h (emx+gcc) */

#ifndef _EMX_IO_H
#define _EMX_IO_H

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (NULL)
#if defined (__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#if !defined (_SIZE_T)
#define _SIZE_T
typedef unsigned long size_t;
#endif

/* Low-level i/o */

/*      O_ACCMODE   0x00000003 */
/*      O_NDELAY    0x00000004 */
/*      O_APPEND    0x00000008 */
/*      O_TEXT      0x00000010 */
#define F_EOF       0x00000020
#define F_TERMIO    0x00000040
#define F_DEV       0x00000080
/*      O_BINARY    0x00000100 */
/*      O_CREAT     0x00000200 */
/*      O_TRUNC     0x00000400 */
/*      O_EXCL      0x00000800 */
/*      O_NOINHERIT 0x00001000 */
/*      O_SYNC      0x00002000 */
/*      O_NOCTTY    0x00004000 */
/*      O_SIZE      0x00008000 */
#define F_SOCKET    0x10000000
#define F_PIPE      0x20000000
#define F_WRCRPEND  0x40000000
#define F_CRLF      0x80000000

/* stdio */

/*      _IOREAD     0x00000001 */
/*      _IOWRT      0x00000002 */
/*      _IORW       0x00000004 */
/*      _IOEOF      0x00000008 */
/*      _IOERR      0x00000010 */
/*      _IOLBF      0x00000020 */
/*      _IONBF      0x00000040 */

/* This bit is set if the stream is open. */

#define _IOOPEN     0x00000080

/* Mask for the buffer type. */

#define _IOBUFMASK  0x00000700

/* This buffer type is set until a buffer has been assigned. */

#define _IOBUFNONE  0x00000000

/* This buffer type is set by setvbuf() if a user-allocated buffer is
   used. */

#define _IOBUFUSER  0x00000100

/* This buffer type is set by _fbuf() if a single-character buffer is
   used. */

#define _IOBUFCHAR  0x00000200

/* This buffer type is set by _fbuf() if the stream buffer has been
   allocated by the library, with malloc().  The buffer will be
   deallocated by fclose(). */

#define _IOBUFLIB   0x00000300

/* This buffer type is set by _tmpbuf1() to indicate that a temporary
   buffer has been assigned to the stream. */

#define _IOBUFTMP   0x00000400

/* This bit is set by tmpfile() to indicate a temporary file, to be
   deleted by fclose(). */

#define _IOTMP      0x00000800

/* This bit is set for special streams which don't have an underlying
   file. */

#define _IOSPECIAL  0x00001000

/* This bit is set by ungetc() to indicate that pushed-back characters
   have been stored to the stream buffer -- fseek() must cause the
   buffer to be reread. */

#define _IOUNGETC   0x00002000

/* This bit is set by _newstream() to avoid reusing the same slot in
   another thread. */

#define _IONEW      0x00004000

/* This bit is set for byte-oriented streams. */

#define _IOBYTE     0x00008000

/* This bit is set for wide-oriented streams. */

#define _IOWIDE     0x00010000


#define _FLUSH_FLUSH  (-1)
#define _FLUSH_FILL   (-2)

struct _FILE;

struct _file2
{
  struct _FILE *owner;
#if defined (_SYS_RMUTEX_H)
  _rmutex rsem;
#else
  char rsem_ersatz[16];
#endif
};

#define nbuf(s) (((s)->_flags & _IOBUFMASK) == _IOBUFNONE)
#define cbuf(s) (((s)->_flags & _IOBUFMASK) == _IOBUFCHAR)
#define ubuf(s) (((s)->_flags & _IOBUFMASK) == _IOBUFUSER)
#define lbuf(s) (((s)->_flags & _IOBUFMASK) == _IOBUFLIB)
#define tbuf(s) (((s)->_flags & _IOBUFMASK) == _IOBUFTMP)

#define bbuf(s) (ubuf (s) || lbuf (s) || tbuf (s))

#define _tmpbuf(s,b) (nbuf (s) || cbuf (s) \
                      ? b = alloca (BUFSIZ), _tmpbuf1 (s, b) : 0)
#define _endbuf(s) (tbuf (s) ? _endbuf1 (s) : 0)

#define alloca(x) __builtin_alloca(x)

struct streamvec
{
  struct _FILE *vec;
  struct streamvec *next;
  int n;
};

struct fdvec
{
  int *flags;
  int *lookahead;
  struct fdvec *next;
  int n;
};

extern struct streamvec _streamvec_head;

extern int _io_ninherit;
extern struct fdvec _fdvec_head;

#if defined (__MT__)

/* This is currently used only in the multi-thread libraries.  We
   can't use and reallocate a single array because rmutex semaphores
   cannot be moved. */

struct streamvec2
{
  struct _file2 *vec;
  struct streamvec2 *next;
  int n;
};

extern struct streamvec2 _streamvec2_head;

#if defined (_SYS_RMUTEX_H)

/* This semaphore (defined in app/stdio.c) protects _streamv[].  Only
   concurrent access by _newstream(), _setmore(), and freopen() in
   different threads must be prevented to avoid using one element of
   _streamv[] for multiple streams (in different threads).  All other
   functions may concurrently access _streamv[], even concurrently to
   _newstream(), _setmore(), and freopen(). */

extern _rmutex _streamv_rmutex;

#define STREAMV_LOCK    _rmutex_checked_request (&_streamv_rmutex, _FMR_IGNINT)
#define STREAMV_UNLOCK  _rmutex_checked_release (&_streamv_rmutex)

#define STREAM_LOCK(f) \
  (_rmutex_request (&(f)->_more->rsem, _FMR_IGNINT) != 0 \
   ? abort () : (void)0)

#define STREAM_UNLOCK(f) \
  (_rmutex_release (&(f)->_more->rsem) != 0 ? abort () : (void)0)

#define STREAM_LOCK_NOWAIT(f) \
  (_rmutex_request (&(f)->_more->rsem, _FMR_NOWAIT) == 0)

#define STREAM_UNLOCKED(f) _rmutex_available (&(f)->_more->rsem)

#endif /* defined (_SYS_RMUTEX_H) */

#else /* !defined (__MT__) */

#define STREAMV_LOCK            (void)0
#define STREAMV_UNLOCK          (void)0

#define STREAM_LOCK(f)          (void)0
#define STREAM_UNLOCK(f)        (void)0
#define STREAM_LOCK_NOWAIT(f)   1
#define STREAM_UNLOCKED(f)      1

#endif /* !defined (__MT__) */


int _endbuf1 (struct _FILE *);
void _fbuf (struct _FILE *);
int *_fd_flags (int);
int *_fd_init (int);
int *_fd_lookahead (int);
struct _FILE *_fopen (struct _FILE *, __const__ char *, __const__ char *,
    int, int);
int _flushstream (struct _FILE *, int);
void _closestream (struct _FILE *);
int _fflush_nolock (struct _FILE *);
int _fseek_nolock (struct _FILE *, long, int);
long _ftell_nolock (struct _FILE *);
size_t _fwrite_nolock (const void *, size_t, size_t, struct _FILE *);
int _input (struct _FILE *, __const__ char *, char *);
struct _FILE *_newstream (void);
int _output (struct _FILE *, __const__ char *, char *);
void _setdummymore (struct _FILE *, struct _file2 *);
int _setmore (struct _FILE *, int);
int _stream_read (int, void *, size_t);
int _stream_write (int, __const__ void *, size_t);
int _tmpbuf1 (struct _FILE *, void *);
int _trslash (__const__ char *, size_t, int);
int _ungetc_nolock (int, struct _FILE *);
int _vsopen (__const__ char *, int, int, char *);


#if defined (__cplusplus)
}
#endif

#endif /* not _EMX_IO_H */
