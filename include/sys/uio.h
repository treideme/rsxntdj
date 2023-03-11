/* sys/uio.h (emx+gcc) */

#ifndef _SYS_UIO_H
#define _SYS_UIO_H

#if defined (__cplusplus)
extern "C" {
#endif

struct iovec
{
  caddr_t iov_base;
  int     iov_len;
};

/* needed for sys\socket.h TCPIPV4 now */
#ifdef TCPIPV4
struct uio {
	struct iovec	*uio_iov;
	int		uio_iovcnt;
	off_t		uio_offset;
	int		uio_segflg;
	unsigned int	uio_resid;
};
enum	uio_rw { UIO_READ, UIO_WRITE };
#define FREAD   1
#define FWRITE  2
#endif

int readv (int, __const__ struct iovec *, int);
int writev (int, __const__ struct iovec *, int);

int _readv (int, __const__ struct iovec *, int);
int _writev (int, __const__ struct iovec *, int);

#if defined (__cplusplus)
}
#endif

#endif /* not _SYS_UIO_H */
