/* sys/errno.h (emx+gcc) */

#ifndef _SYS_ERRNO_H
#define _SYS_ERRNO_H

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (__ASSEMBLER__) && !defined (_ERRNO)
#define _ERRNO
#if defined (__MT__) || defined (__ST_MT_ERRNO__)
extern int *_errno (void);
#define errno (*_errno ())
#else
extern int errno;
#endif
#endif

#define EPERM           1   /* Operation not permitted              */
#define ENOENT          2   /* No such file or directory            */
#define ESRCH           3   /* No such process                      */
#define EINTR           4   /* Interrupted system call              */
#define EIO             5   /* I/O error                            */
#define ENXIO           6   /* No such device or address            */
#define E2BIG           7   /* Arguments or environment too big     */
#define ENOEXEC         8   /* Invalid executable file format       */
#define EBADF           9   /* Bad file number                      */
#define ECHILD          10  /* No child processes                   */
#define EAGAIN          11  /* Resource temporarily unavailable     */
#define ENOMEM          12  /* Not enough memory                    */
#define EACCES          13  /* Permission denied                    */
#define EFAULT          14  /* Bad address                          */
#define ENOLCK          15  /* No locks available                   */
#define EBUSY           16  /* Resource busy                        */
#define EEXIST          17  /* File exists                          */
#define EXDEV           18  /* Cross-device link                    */
#define ENODEV          19  /* No such device                       */
#define ENOTDIR         20  /* Not a directory                      */
#define EISDIR          21  /* Is a directory                       */
#define EINVAL          22  /* Invalid argument                     */
#define ENFILE          23  /* Too many open files in system        */
#define EMFILE          24  /* Too many open files                  */
#define ENOTTY          25  /* Inappropriate ioctl                  */
#define EDEADLK         26  /* Resource deadlock avoided            */
#define EFBIG           27  /* File too large                       */
#define ENOSPC          28  /* Disk full                            */
#define ESPIPE          29  /* Invalid seek                         */
#define EROFS           30  /* Read-only file system                */
#define EMLINK          31  /* Too many links                       */
#define EPIPE           32  /* Broken pipe                          */
#define EDOM            33  /* Domain error                         */
#define ERANGE          34  /* Result too large                     */
#define ENOTEMPTY       35  /* Directory not empty                  */
#define EINPROGRESS     36  /* Operation now in progress            */
#define ENOSYS          37  /* Function not implemented             */
#define ENAMETOOLONG    38  /* File name too long                   */
#define EDESTADDRREQ    39  /* Destination address required         */
#define EMSGSIZE        40  /* Message too long                     */
#define EPROTOTYPE      41  /* Protocol wrong type for socket       */
#define ENOPROTOOPT     42  /* Option not supported by protocol     */
#define EPROTONOSUPPORT 43  /* Protocol not supported               */
#define ESOCKTNOSUPPORT 44  /* Socket type not supported            */
#define EOPNOTSUPP      45  /* Operation not supported on socket    */
#define EPFNOSUPPORT    46  /* Protocol family not supported        */
#define EAFNOSUPPORT    47  /* Address family not supported by protocol family */
#define EADDRINUSE      48  /* Address already in use               */
#define EADDRNOTAVAIL   49  /* Can't assigned requested address     */
#define ENETDOWN        50  /* Network is down                      */
#define ENETUNREACH     51  /* Network is unreachable               */
#define ENETRESET       52  /* Network dropped connection on reset  */
#define ECONNABORTED    53  /* Software caused connection abort     */
#define ECONNRESET      54  /* Connection reset by peer             */
#define ENOBUFS         55  /* No buffer space available            */
#define EISCONN         56  /* Socket is already connected          */
#define ENOTCONN        57  /* Socket is not connected              */
#define ESHUTDOWN       58  /* Can't send after socket shutdown     */
#define ETOOMANYREFS    59  /* Too many references: can't splice    */
#define ETIMEDOUT       60  /* Connection timed out                 */
#define ECONNREFUSED    61  /* Connection refused                   */
#define ELOOP           62  /* Too many levels of symbolic links    */
#define ENOTSOCK        63  /* Socket operation on non-socket       */
#define EHOSTDOWN       64  /* Host is down                         */
#define EHOSTUNREACH    65  /* No route to host                     */
#define EALREADY        66  /* Operation already in progress        */

#define EWOULDBLOCK     EAGAIN

#if (!defined (__STRICT_ANSI__) && !defined (_POSIX_SOURCE)) \
    || defined (_WITH_UNDERSCORE)

#if !defined (__ASSEMBLER__)
int *_errno (void);
#endif

#endif


#if defined (__cplusplus)
}
#endif

#endif /* not _SYS_ERRNO_H */
