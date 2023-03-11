/*
    Run-time dynamic linking of DLL functions
*/

#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <crtrsxnt.h> /* required for -Zcrtdll=crtrsxnt */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "dllcrt.h"

int main(int argc, char **argv)
{
    HINSTANCE hLib;                     /* handle of the DLL */
    DLLOPENFILE lpfnOpenFile;		/* address of DLL function */
    DLLCLOSEFILE lpfnCloseFile; 	/* address of DLL function */
    int handle;

    /* --- load the library --- */

    hLib = LoadLibrary("dllcrt.dll");
    if (!hLib) {
	DWORD err = GetLastError();
	printf("Cannot load dll fails err=0x%lX = %ld\n", err, err);
	exit(1);
    }

    /* --- get the address of the exported functions --- */

    lpfnOpenFile = (DLLOPENFILE) GetProcAddress(hLib, DLLOPENFILE_NAME);
    if (!lpfnOpenFile) {
	printf("Error: GetProcAddress(Maximum)\n");
	exit(1);
    }
    lpfnCloseFile = (DLLCLOSEFILE) GetProcAddress(hLib, DLLCLOSEFILE_NAME);
    if (!lpfnCloseFile) {
	printf("Error: GetProcAddress(Minimum)\n");
	exit(1);
    }

    /* --- access the dll --- */

    handle = (*lpfnOpenFile)();

    if (handle >= 0)
    {
	char buf [80];
	int n;

	printf("handle is %d\n", handle);

	while ((n = read (handle, buf, sizeof (buf))) > 0)
            write (fileno(stdout), buf, n);

	if ((*lpfnCloseFile)(handle) < 0)
	    perror ("dll close");
    }
    else
	perror ("dll open");

    FreeLibrary(hLib);

    return 0;
}
