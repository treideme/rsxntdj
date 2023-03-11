/*- Modified for emx by hv and em 1994-1997
 *
 * Copyright (c) 1980, 1983, 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)netdb.h	5.15 (Berkeley) 4/3/91
 *	$Id: netdb.h,v 1.2 1993/08/01 18:44:45 mycroft Exp $
 */

#ifndef _NETDB_H_
#define _NETDB_H_

#if defined (__cplusplus)
extern "C" {
#endif

#ifndef _EMX_TCPIP
#define _EMX_TCPIP
#endif

#ifdef __RSXNT__    /* convert some int values to short */
#define __INT_T short
#pragma pack(1)
#else /* emx */
#define __INT_T int
#endif

extern int h_errno;

#define	_PATH_HEQUIV	"/tcpip/etc/hosts.equiv"
#define	_PATH_HOSTS	"/tcpip/etc/hosts"
#define	_PATH_NETWORKS	"/tcpip/etc/networks"
#define	_PATH_PROTOCOLS	"/tcpip/etc/protocols"
#define	_PATH_SERVICES	"/tcpip/etc/services"

/*
 * Structures returned by network data base library.  All addresses are
 * supplied in host order, and returned in network order (suitable for
 * use in system calls).
 */
struct	hostent {
	char	*h_name;	/* official name of host */
	char	**h_aliases;	/* alias list */
	__INT_T	h_addrtype;	/* host address type */
	__INT_T	h_length;	/* length of address */
	char	**h_addr_list;	/* list of addresses from name server */
#define	h_addr	h_addr_list[0]	/* address, for backward compatiblity */
};

/*
 * Assumption here is that a network number
 * fits in 32 bits -- probably a poor one.
 */
struct	netent {
	char		*n_name;	/* official name of net */
	char		**n_aliases;	/* alias list */
	__INT_T		n_addrtype;	/* net address type */
	unsigned long	n_net;		/* network # */
};

struct	servent {
	char	*s_name;	/* official service name */
	char	**s_aliases;	/* alias list */
	__INT_T	s_port;		/* port # */
	char	*s_proto;	/* protocol to use */
};

struct	protoent {
	char	*p_name;	/* official protocol name */
	char	**p_aliases;	/* alias list */
	__INT_T	p_proto;	/* protocol # */
};

/*
 * Error return codes from gethostbyname() and gethostbyaddr()
 * (left in extern int h_errno).
 */
#if 0
#define h_errno (tcp_h_errno())	/* thread safe */
#endif
#define	HOST_NOT_FOUND	1 /* Authoritative Answer Host not found */
#define	TRY_AGAIN	2 /* Non-Authoritive Host not found, or SERVERFAIL */
#define	NO_RECOVERY	3 /* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
#define	NO_DATA		4 /* Valid name, no data record of requested type */
#define	NO_ADDRESS	NO_DATA		/* no address, look for MX record */

int		gethostname (char *, int);
void		endhostent (void);
void		endnetent (void);
void		endprotoent (void);
void		endservent (void);
struct hostent	*gethostbyaddr (__const__ char *, int, int);
struct hostent	*gethostbyname (__const__ char *);
struct hostent	*gethostent (void);
struct netent	*getnetbyaddr (u_long, int);
struct netent	*getnetbyname (__const__ char *);
struct netent	*getnetent (void);
struct protoent	*getprotobyname (__const__ char *);
struct protoent	*getprotobynumber (int);
struct protoent	*getprotoent (void);
struct servent	*getservbyname (__const__ char *, __const__ char *);
struct servent	*getservbyport (int, __const__ char *);
struct servent	*getservent (void);
void		herror (__const__ char *);
void		sethostent (int);
void		setnetent (int);
void		setprotoent (int);
void		setservent (int);

#ifdef NETDB_IBM_ADDENDUM

/* IBM addendum structures and functions */
#define	_HOSTBUFSIZE	(4096+1)
#define	_MAXADDRS	35
#define	_MAXALIASES	35
#define	_MAXLINELEN	1024

/* this is the internally used data structure to which pointers of 
 * struct hostent ponit to, after gethostbyname_r/gethostbyaddr_r were
 * called. ATTENTION EMX: The component _opaque_ is a pointer to a data
 * structure which is not accessible by EMX
 */
struct hostent_data {
	struct in_addr	host_addr;		/* host address pointer */
	char	*h_addr_ptrs[_MAXADDRS+1];	/* host address */
	char	hostaddr[_MAXADDRS];
	char	hostbuf[_HOSTBUFSIZE+1];	/* host data */
	char	*host_aliases[_MAXALIASES];
	char	*host_addrs[2];
	void	*_opaque_;			/* EMX: dead component! */
	int	stayopen;			/* AIX addon */
	u_long	host_addresses[_MAXADDRS];	/* Actual Addresses. */
};                                              

struct servent_data {
	void	*_opaque_;
	char	line[_MAXLINELEN];
	char	*serv_aliases[_MAXALIASES];
	int	_serv_stayopen;
};

int gethostbyname_r(char*, struct hostent*, struct hostent_data*);
int gethostbyaddr_r(char*, int, int, struct hostent*, struct hostent_data*);
int getservbyname_r(char*, char*, struct servent*, struct servent_data*);
struct hostent *_gethtbyname(char*);
struct hostent *_gethtbyaddr(char*, int, int);
int tcp_h_errno(void);	/* thread safe h_errno */

#endif /* NETDB_IBM_ADDENDUM */

#ifdef __RSXNT__
#pragma pack()
#endif
#undef __INT_T

#if defined (__cplusplus)
}
#endif

#endif /* !_NETDB_H_ */
