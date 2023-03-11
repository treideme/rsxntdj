/* Copyright (c)1996 by Holger Veit
 * May be freely used with EMX 
 */

#ifndef _SYS_UN_H_
#define _SYS_UN_H_

struct  sockaddr_un {
	u_short	sun_family;	/* socket family: AF_UNIX */
	char	sun_path[108];	/* path name (not used) */
};

#endif /* !_SYS_UN_H_ */
