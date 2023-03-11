/* winsock.h
   Definitions are in a different layout than MS headers
   This file includes our windows.h which in turn should include the
   normal contents of this header file (and the other Win32 headers).

   If you include this file, you will not be able to use the cygwin32
   select function.  Also, the cygwin32 socket functions will be
   misdeclared, so you will only be able to use the winsock functions.
   This should only be used if you know what you are doing.  */

#ifndef _PLACEHOLDER_WINSOCK_H
#define _PLACEHOLDER_WINSOCK_H

#include <windows.h>
#include <Sockets.h>

#endif /* _PLACEHOLDER_WINSOCK_H */
