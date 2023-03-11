/* Modifed for emx by hv 1994,1996
 *
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
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
 *	from: @(#)if.h	7.11 (Berkeley) 3/19/91
 *	$Id: if.h,v 1.7 1994/02/10 17:16:33 mycroft Exp $
 */

#ifndef _NET_IF_H_
#define _NET_IF_H_

#if defined (__cplusplus)
extern "C" {
#endif

/*
 * Structures defining a network interface, providing a packet
 * transport mechanism (ala level 0 of the PUP protocols).
 *
 * Each interface accepts output datagrams of a specified maximum
 * length, and provides higher level routines with input datagrams
 * received from its medium.
 *
 * Output occurs when the routine if_output is called, with three parameters:
 *	(*ifp->if_output)(ifp, m, dst)
 * Here m is the mbuf chain to be sent and dst is the destination address.
 * The output routine encapsulates the supplied datagram if necessary,
 * and then transmits it on its medium.
 *
 * On input, each interface unwraps the data received by it, and either
 * places it on the input queue of a internetwork datagram routine
 * and posts the associated software interrupt, or passes the datagram to a raw
 * packet input routine.
 *
 * Routines exist for locating interfaces by their addresses
 * or for locating a interface on a certain network, as well as more general
 * routing and gateway routines maintaining information used to locate
 * interfaces.  These routines live in the files if.c and route.c
 */
/*  XXX fast fix for SNMP, going away soon */
#include <sys/time.h>

#ifdef TCPIPV4
#pragma pack(1)
#else
#pragma pack(4)
#endif


/*
 * Structure defining a queue for a network interface.
 *
 * (Would like to call this struct ``if'', but C isn't PL/1.)
 */
/*forward*/ struct mbuf;
/*forward*/ struct ifaddr;
struct ifnet {
	char	*if_name;		/* name, e.g. ``en'' or ``lo'' */
	short	if_unit;		/* sub-unit for lower level driver */
	short	if_mtu;			/* maximum transmission unit */
	short	if_flags;		/* up/down, broadcast, etc. */
	short	if_timer;		/* time 'til if_watchdog called */
	int	if_metric;		/* routing metric (external only) */
	struct	ifaddr *if_addrlist;	/* linked list of addresses per if */
	struct	ifqueue {
		struct	mbuf *ifq_head;
		struct	mbuf *ifq_tail;
#ifndef TCPIPV4
		int	ifq_len;
		int	ifq_maxlen;
		int	ifq_drops;
#else
		short	ifq_len;
		short	ifq_maxlen;
		u_short	ifq_drops;
#endif
	} if_snd;			/* output queue */
/* procedure handles */
	int	(*if_init)(void);	/* IBMSOCKETS */
	int	(*if_output)(void);	/* output routine (enqueue) */
	int	(*if_ioctl)(void);	/* ioctl routine */
	int	(*if_reset)(void);	/* bus reset routine */
	int	(*if_watchdog)(void);	/* timer routine */
/* generic interface statistics */
#ifndef TCPIPV4
	int	if_ipackets;		/* packets received on interface */
	int	if_ierrors;		/* input errors on interface */
	int	if_opackets;		/* packets sent on interface */
	int	if_oerrors;		/* output errors on interface */
	int	if_collisions;		/* collisions on csma interfaces */
#else
	u_short	if_ipackets;		/* packets received on interface */
	u_short	if_ierrors;		/* input errors on interface */
	u_short	if_opackets;		/* packets sent on interface */
	u_short	if_oerrors;		/* output errors on interface */
	u_short	if_collisions;		/* collisions on csma interfaces */
#endif
/* end statistics */
	struct	ifnet *if_next;

/* the following structures are special for OS/2 TCP/IP only */
	u_char	if_adapternum;          /* adapter number */
	u_int	if_adaptype;
	u_int	if_broadcast;
	u_long	if_speed;

#define IF_RTTSCALE	1000
	u_short	if_rtt;                 /* Est interface rtt in ms */
	u_short	if_rttvar;              /* Est interface rttvar in ms */
	u_short	if_rttmin;              /* Fixed interface rttmin in ms */
	u_short	if_sendpipe;            /* Send socket buffer/window size */
	u_short	if_recvpipe;            /* Recv socket buffer/window size */
	u_short	if_ssthresh;            /* Gateway buffer limit (slow strt) */
#ifdef TCPIPV4
	u_long	if_eflags;		/* Extended flags */
	struct ifqueue if_traceq;	/* packet trace queue */
	u_short	if_segsize;		/* segment size for interface */
	u_short if_use576;		/* use 576 or 1460 as def. mss if */
					/* going through a router */
	u_short if_rfc1469;		/* using broadcast or functional */
					/* addr for IP Multicast */
#define	IFF_RFC1469_BC	1		/* use broadcast */
#define	IFF_RFC1469_FA	2		/* use functional address */
#define	IFF_RFC1469_MA	3		/* use multicast address */
#endif
};

#ifndef TCPIPV4
struct ifmib {
	int	ifNumber;		/* number of network interfaces */
	struct iftable {
		int	ifIndex;	/* index of this interface */
		char	ifDescr[45];	/* description */
		int	ifType;		/* type of the interface */
		int	ifMtu;		/* MTU of the interface */
		char	ifPhysAddr[6];	/* MTU of the interface */
		int	ifOperStatus;
		u_long	ifSpeed;
		u_long	ifLastChange;
		u_long	ifInOctets;
		u_long	ifOutOctets;
		u_long	ifOutDiscards;
		u_long	ifInDiscards;
		u_long	ifInErrors;
		u_long	ifOutErrors;
		u_long	ifInUnknownProtos;
		u_long	ifInUcastPkts;
		u_long	ifOutUcastPkts;
		u_long	ifInNUcastPkts;
		u_long	ifOutNUcastPkts;
	} iftable[20];
};
#else /* TCP/IP V4 */

#ifndef IFMIB_ENTRIES
#define IFMIB_ENTRIES 42
#endif

struct ifmib {
	short	ifNumber;		/* number of network interfaces */
	struct iftable {
		short	ifIndex;	/* index of this interface */
		char	ifDescr[45];	/* description */
		short	ifType;		/* type of the interface */
		short	ifMtu;		/* MTU of the interface */
		char	ifPhysAddr[6];	/* MTU of the interface */
		short	ifOperStatus;
		u_long	ifSpeed;
		u_long	ifLastChange;
		u_long	ifInOctets;
		u_long	ifOutOctets;
		u_long	ifOutDiscards;
		u_long	ifInDiscards;
		u_long	ifInErrors;
		u_long	ifOutErrors;
		u_long	ifInUnknownProtos;
		u_long	ifInUcastPkts;
		u_long	ifOutUcastPkts;
		u_long	ifInNUcastPkts;
		u_long	ifOutNUcastPkts;
	} iftable[IFMIB_ENTRIES];
};
#endif /* TCP/IP V4 */
#pragma pack()

#define	IFF_UP		0x1		/* interface is up */
#define	IFF_BROADCAST	0x2		/* broadcast address valid */
#define	IFF_DEBUG	0x4		/* turn on debugging */
#define	IFF_LOOPBACK	0x8		/* is a loopback net */
#define	IFF_POINTOPOINT	0x10		/* interface is point-to-point link */
#define	IFF_NOTRAILERS	0x20		/* avoid use of trailers */
#define	IFF_RUNNING	0x40		/* resources allocated */
#define	IFF_NOARP	0x80		/* no address resolution protocol */
/* next two not supported now, but reserved: */
#define	IFF_PROMISC	0x100		/* receive all packets */
#define	IFF_ALLMULTI	0x200		/* receive all multicast packets */
#define	IFF_OACTIVE	0x400		/* transmission in progress */
#define	IFF_SIMPLEX	0x800		/* can't hear own transmissions */
#define	IFF_BRIDGE	0x1000		/* support token ring routine field */
#define	IFF_SNAP	0x2000		/* support extended SNAP header */
#define	IFF_ETHER	0x4000		/* ethernet interface */
#define IFF_LOOPBRD	0x8000		/* ethernet interface */

/*hv: flags set internally only */
#ifdef BSD_TCPCOMPAT
#define IFF_CANTCHANGE \
	(IFF_BROADCAST|IFF_POINTOPOINT|IFF_RUNNING|IFF_OACTIVE| \
	IFF_SIMPLEX|IFF_MULTICAST)
#else
#define IFF_CANTCHANGE  (IFF_BROADCAST | IFF_POINTOPOINT | IFF_RUNNING)
#endif

#ifdef TCPIPV4
/* packet tracing extension */
#define	IFFE_PKTTRACE	0x00000001	/* trace datalink where possible */
#define	IFFE_IPTRACE	0x00000002	/* trace ONLY IP packets */

struct pkt_trace_hdr {
	u_short		pt_htype;	/* header type */
#define		HT_IP		0x01	/* 	IP */
#define		HT_ETHER	0x06	/* 	Ethernet */
#define		HT_ISO88023	0x07	/* 	CSMA CD */
#define		HT_ISO88025	0x09	/* 	Token Ring */
#define		HT_SLIP		0x1c	/* 	Serial Line IP */
#define		HT_PPP		0x18	/* 	PPP IP */
	u_short		pt_len;		/* in: pt_buf len, out: packet len */
	caddr_t		pt_data;	/* packet ATTN: This is a _Seg16 addr! */
	u_long		pt_tstamp;	/* time stamp in milliseconds */
};

#endif /* TCP/IP V4 */

/*
 * Output queues (ifp->if_snd) and internetwork datagram level (pup level 1)
 * input routines have queues of messages stored on ifqueue structures
 * (defined above).  Entries are added to and deleted from these structures
 * by these macros, which should be called with ipl raised to splimp().
 */
#define	IF_QFULL(ifq)		((ifq)->ifq_len >= (ifq)->ifq_maxlen)
#define	IF_DROP(ifq)		((ifq)->ifq_drops++)
#define	IF_ENQUEUE(ifq, m) {\
        (m)->m_act=0;\
	if ((ifq)->ifq_tail==0)\
		(ifq)->ifq_head=m;\
	else\
		(ifq)->ifq_tail->m_act=m;\
	(ifq)->ifq_tail=m;\
	(ifq)->ifq_len++;\
}
#define	IF_PREPEND(ifq, m) {\
	(m)->m_act=(ifq)->ifq_head;\
	if ((ifq)->ifq_tail==0)\
		(ifq)->ifq_tail=(m);\
	(ifq)->ifq_head=(m);\
	(ifq)->ifq_len++;\
}
#define	IF_DEQUEUE(ifq, m) {\
	(m)=(ifq)->ifq_head;\
	if (m) {\
		if (((ifq)->ifq_head=(m)->m_act)==0)\
			(ifq)->ifq_tail=0;\
		(m)->m_act=0;\
		(ifq)->ifq_len--;\
	}\
}
#define IF_ADJ(m) {\
	(m)->m_off+=sizeof(struct ifnet*);\
	(m)->m_len-=sizeof(struct ifnet*);\
	if ((m)->m_len==0) {\
		struct mbuf *n;\
		MFREE((m), n);\
		(m) = n;\
	}\
}
#define IF_DEQUEUEIF(ifq, m, ifp) {\
	(m)=(ifq)->ifq_head;\
	if (m) {\
		if (((ifq)->ifq_head=(m)->m_act)==0)\
                        (ifq)->ifq_tail=0;\
                (m)->m_act=0;\
                (ifq)->ifq_len--;\
                (ifp)=*(mtod((m), struct ifnet**));\
                IF_ADJ(m);\
        }\
}

#define	IFQ_MAXLEN	50
#define	IFNET_SLOWHZ	1	/* granularity is 1 second */

/*
 * The ifaddr structure contains information about one address
 * of an interface.  They are maintained by the different address families,
 * are allocated and attached when an address is set, and are linked
 * together so all addresses for an interface can be located.
 */
struct ifaddr {
	struct sockaddr	ifa_addr;		/* address of interface */
	union {
		struct sockaddr	ifu_broadaddr;	/* broadcast address interface */
		struct sockaddr	ifu_dstaddr;	/* other end of p-to-p link */
	} ifa_ifu;
#define ifa_broadaddr	ifa_ifu.ifu_broadaddr
#define ifa_dstaddr	ifa_ifu.ifu_dstaddr
	struct ifnet	*ifa_ifp;		/* back-pointer to interface */
	struct ifaddr	*ifa_next;		/* next address for interface */
};

/*
 * Interface request structure used for socket
 * ioctl's.  All interface ioctl's must have parameter
 * definitions which begin with ifr_name.  The
 * remainder may be interface specific.
 */
struct	ifreq {
#define	IFNAMSIZ	16
	char	ifr_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	union {
		struct	sockaddr ifru_addr;
		struct	sockaddr ifru_dstaddr;
		struct	sockaddr ifru_broadaddr;
		short	ifru_flags;
		int	ifru_metric;
		caddr_t	ifru_data;
	} ifr_ifru;
#define	ifr_addr	ifr_ifru.ifru_addr	/* address */
#define	ifr_dstaddr	ifr_ifru.ifru_dstaddr	/* other end of p-to-p link */
#define	ifr_broadaddr	ifr_ifru.ifru_broadaddr	/* broadcast address */
#define	ifr_flags	ifr_ifru.ifru_flags	/* flags */
#define	ifr_metric	ifr_ifru.ifru_metric	/* metric */
#define	ifr_data	ifr_ifru.ifru_data	/* for use by interface */
};

/*
 * Structure used in SIOCGIFCONF request.
 * Used to retrieve interface configuration
 * for machine (useful for programs which
 * must know all networks accessible).
 */
struct	ifconf {
	int	ifc_len;		/* size of associated buffer */
	union {
		caddr_t	ifcu_buf;
		struct	ifreq *ifcu_req;
	} ifc_ifcu;
#define	ifc_buf	ifc_ifcu.ifcu_buf	/* buffer address */
#define	ifc_req	ifc_ifcu.ifcu_req	/* array of structures returned */
};

#include <net/if_arp.h>

#if defined (__cplusplus)
}
#endif

#endif /* _NET_IF_H_ */
