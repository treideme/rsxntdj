/*
    Run-time dynamic linking of DLL functions

    This application uses a DLL without Runtime-Environment (and rsxnt.dll).
    This allows you to compile this application with other Win32 compilers.
*/

#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include "dllnrt.h"

typedef int WINAPI (*DLLFUNC) (int, int);

/*
    Emx 0.9c does not understand WINAPI inside a typedef definition (stack).
    The functions save_stdcall will restore the bad stack

    NT09c does not contain this error.
*/
int save_stdcall(DLLFUNC func, int a, int b)
{
    return (*func) (a,b);
}

int test (HANDLE hLib)
{
    DLLFUNC lpfnMin, lpfnMax, lpfnOrd;
    int x1, x2, x3;
    char buf[260];
    int i;

    lpfnMax = (DLLFUNC) GetProcAddress(hLib, "Maximum");
    if (!lpfnMax) {
	sprintf(buf, "Error: GetProcAddress(Maximum)");
	MessageBox(NULL, buf, NULL, MB_OK);
	return(1);
    }
    lpfnMin = (DLLFUNC) GetProcAddress(hLib, "Minimum");
    if (!lpfnMin) {
	sprintf(buf, "Error: GetProcAddress(Minimum)");
	MessageBox(NULL, buf, NULL, MB_OK);
	return(1);
    }

    x1 = 2;
    x2 = 3;

    x3 = save_stdcall(lpfnMax, x1, x2);
    sprintf(buf, "Maximum (%d,%d) = %d\n", x1, x2, x3);
    MessageBox(NULL, buf, "dll Minimum", MB_OK);

    x3 = save_stdcall(lpfnMin, x1, x2);
    sprintf(buf, "Minimum (%d,%d) = %d\n", x1, x2, x3);
    MessageBox(NULL, buf, "dll Minimum", MB_OK);

    for (i = 11; i <= 14;++i)
    {
        lpfnOrd = (DLLFUNC) GetProcAddress(hLib, (LPSTR) i);
        if (!lpfnOrd) {
            sprintf(buf, "Error: GetProcAddress(@%i)", i);
            MessageBox(NULL, buf, NULL, MB_OK);
            return(1);
        }
        x3 = save_stdcall(lpfnOrd, x1, x2);
        sprintf(buf, "Ordinal %i func (%d,%d) = %d\n", i, x1, x2, x3);
        MessageBox(NULL, buf, "GetProcAddress Ordinal", MB_OK);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    HINSTANCE hLib;

    hLib = LoadLibrary("dllnrt.dll");
    if (!hLib) {
        MessageBox(NULL, "Error loading dll", NULL, MB_OK);
	return(1);
    }
    test (hLib);
    FreeLibrary(hLib);
    return 0;
}
