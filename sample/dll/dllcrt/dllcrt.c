/*

  This demo builds a Win32 DLL that uses the CRT Dll.

  This dll can share handles and other C functions with the
  application.

  Compile with -Zcrtdll to use the CRT DLL

  LibMain() is missing here, it is also defined in the C library

*/

#include <crtrsxnt.h> /* required for -Zcrtdll=crtrsxnt */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "dllcrt.h"

int DllOpenFile()
{
    return open (__FILE__, O_RDONLY | O_TEXT);
}

int DllCloseFile(int handle)
{
    return close (handle);
}
