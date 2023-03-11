/*
    Static linking of DLL functions

    This application uses a DLL without Runtime-Environment (and rsxnt.dll).
    This allows you to compile this application with other Win32 compilers.
    For static linking you must create a import library.
*/

#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include "dllnrt.h"

int caller (char * msg, char * title)
{
    return MessageBox (NULL, msg, title, MB_OK);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance,
		   LPSTR lpszCmdParam, int nCmdShow)
{
    char buf[260];
    int x1, x2;

    x1 = 2;
    x2 = 3;

    callme (caller);

    sprintf(buf, "add(%d,%d) = %d\n", x1, x2, _add(x1,x2));
    MessageBox(NULL, buf, "test1", MB_OK);

    sprintf(buf, "sub(%d,%d) = %d\n", x1, x2, _sub(x1,x2));
    MessageBox(NULL, buf, "test2", MB_OK);

    sprintf(buf, "Maximum (%d,%d) = %d\n", x1, x2, Maximum(x1, x2));
    MessageBox(NULL, buf, "Dll Maximum", MB_OK);

    sprintf(buf, "Minimum (%d,%d) = %d\n", x1, x2, Minimum(x1, x2));
    MessageBox(NULL, buf, "Dll Minimum", MB_OK);

    return 0;
}
