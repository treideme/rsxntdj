/*
    Load-time linking of DLL function

    shares handle (app/dll)
*/

#include <crtrsxnt.h> /* required for -Zcrtdll=crtrsxnt */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "dllcrt.h"

int main(int argc, char **argv)
{
    int handle = DllOpenFile();

    if (handle >= 0)
    {
	char buf [80];
	int n;

	printf("handle is %d\n", handle);

	while ((n = read (handle, buf, sizeof (buf))) > 0)
            write (fileno(stdout), buf, n);

	DllCloseFile(handle);
    }
    else
	perror ("dll open");
    return 0;
}
