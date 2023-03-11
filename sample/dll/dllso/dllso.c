/*
    This demo builds a stand-alone DLL

    This DLL has it's own runtime environment and does
    not need rsxnt.dll. The application that will use
    this DLL can be compiled with every Win32 compiler.

    Required switches: -Zwin32 -Zdll -Zso -Zsys

    We should use __stdcall to support other compilers
    Perhaps they expect that exported functions have the
    attributes WINAPI or CALLBACK.
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int __stdcall DllTest(void)
{
    int handle = open (__FILE__, O_RDONLY | O_TEXT);

    if (handle >= 0)
    {
        char buf [80];
        int n;

        printf("handle is %d\n", handle);

        while ((n = read (handle, buf, sizeof (buf))) > 0)
            write (fileno(stdout), buf, n);

        close(handle);
    }
    else
        perror ("open");

    return 0;
}
