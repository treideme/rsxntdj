#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "dllnrt.h"

/*
    LibMain is called if Windows (un)load the DLL or threads are created

    The function LibMain is also defined in the library
*/

#ifndef SKIP_LIBMAIN

int APIENTRY LibMain(HANDLE hInst, DWORD fdwReason, LPVOID lpReserved)
{
    return 1;
    if (fdwReason == DLL_PROCESS_ATTACH)
        MessageBox(NULL, "LibMain(): DLL loaded", "Attach", MB_OK);
    else if (fdwReason == DLL_PROCESS_DETACH)
        MessageBox(NULL, "LibMain(): DLL unloaded", "Detach", MB_OK);

    return 0;//TRUE;
}
#endif

int WINAPI Minimum(int x1, int x2)
{
    return (x1 < x2) ? x1 : x2;
}

int WINAPI Maximum(int x1, int x2)
{
    return (x1 > x2) ? x1 : x2;
}

int WINAPI _add(int x1, int x2)
{
    return x1 + x2;
}

int WINAPI _sub(int x1, int x2)
{
    return x1 - x2;
}

int WINAPI callme (FUNC2 f)
{
    (*f) ("Hello world", "title");
    return 0;
}
