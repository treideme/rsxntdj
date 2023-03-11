/* Copyright (C)1996 by Holger Veit
 * This file may be freely used within the EMX development system
 */

/* NETBIOS declarations */

#ifndef _NETNB_NB_H_
#define _NETNB_NB_H_

#include <sys/socket.h>
#include <netinet/in.h>

#define	NBPROTO_NB	1
#define	NB_FAMILY	AF_NETBIOS
#define	NB_ADDRSIZE	sizeof(struct sockaddr_nb)
#define	NB_UNIQUE	0
#define	NB_GROUP	1
#define	NB_BROAD	2
#define	NB_NAMELEN	16
#define	NB_NETIDLEN	8
#define	NB_HOSTLEN	12
#define	NB_PORTLEN	4
/*                       1234567890123456 */
#define	NB_BCAST_NAME	"*               "
#define	NB_BLANK_NAME	"                "
#define NB_NULL_NAME	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"

#define	NBPORT_RESERVED	IPPORT_RESERVED
#define	NBPORT_USERRESERVED IPPORT_USERRESERVED

/* address format for netbios */
struct sockaddr_nb {
	short	snb_family;		/* protocol family */
	short	snb_type;		/* unique/multicast */
	char	snb_netid[NB_NETIDLEN];	/* netid */
	char	snb_name[NB_NAMELEN];	/* name */
};

#endif /* !_NETNB_NB_H_ */

