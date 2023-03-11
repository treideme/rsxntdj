/*
    This application will use a stand-alone DLL.

    This allows you to compile this application with other Win32 compilers.
*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

typedef int WINAPI (*DLLFUNC) (void);

int main(int argc, char **argv)
{
    HINSTANCE hLib;		/* handle of the DLL */
    DLLFUNC lpfnDllTest;        /* address of DLL function */
    int iRes;

    hLib = LoadLibrary("dllso.dll");
    if (!hLib) {
	DWORD err = GetLastError();
	printf("Cannot load dll fails err=0x%lX = %ld\n", err, err);
	exit(1);
    }

    lpfnDllTest = (DLLFUNC) GetProcAddress(hLib, "DllTest");
    if (!lpfnDllTest) {
	printf("Error: GetProcAddress(Maximum)\n");
	exit(1);
    }

    iRes = (*lpfnDllTest)();
    printf("APP: dll returns %d\n", iRes);

    FreeLibrary(hLib);

    return 0;
}
