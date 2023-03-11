/*
    RsxwBind:

        - Dialog usage
        - Uses CommDlg library (link:static)
        - Load CTL3D library (link:dynamic)
        - Win32/Win16 code

    Copyright (c) Rainer Schnitker
*/

#ifdef __GNUC__
#include <crtrsxnt.h>
#endif

#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commdlg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rsxwbind.h"

#ifdef __EMX__
#define ltoa _ltoa
#endif

static char rsxw_file[256];
static char aout_file[256];
static char exe_file[256];

static DWORD heapsize;
static DWORD stacksize;
static BOOL  bChangeOnlySize;

static HINSTANCE hInstance;

BOOL CALLBACK Dialog(HWND hWnd, UINT wMsg, WPARAM wPar, LPARAM lPar)
{
    static char szFile[256];
    static char szDirName[256];
    char szText[40];
    OPENFILENAME ofn;
    int id, bRet;

    switch (wMsg)
    {
        case WM_COMMAND:

            switch (LOWORD(wPar))
            {
                case ID_SAVE:
                    bChangeOnlySize = IsDlgButtonChecked(hWnd, ID_ONLYSIZE);

                    GetDlgItemText(hWnd, ID_HEAP, szText, 40);
                    heapsize = atol(szText);
                    GetDlgItemText(hWnd, ID_STACK, szText, 40);
                    stacksize = atol(szText);

                    GetDlgItemText(hWnd, ID_RSXW, rsxw_file, 256);
                    GetDlgItemText(hWnd, ID_AOUT, aout_file, 256);
                    GetDlgItemText(hWnd, ID_EXE, exe_file, 256);

                    EndDialog(hWnd, TRUE);
                    return TRUE;

                case ID_NOTSAVE :
                    EndDialog(hWnd, FALSE);
                    return TRUE;

                case ID_BROWSE_RSXW :
                case ID_BROWSE_AOUT :
                case ID_BROWSE_EXE :

                    if (! *szDirName)
                        GetSystemDirectory(szDirName, sizeof(szDirName));

                    *szFile = '\0';
                    memset(&ofn, 0, sizeof(ofn));

                    ofn.lStructSize = sizeof(ofn);
                    ofn.hwndOwner = hWnd;
                    ofn.hInstance = hInstance;
                    ofn.nFilterIndex = 1;
                    ofn.lpstrFile = szFile;
                    ofn.nMaxFile = sizeof(szFile);
                    ofn.lpstrInitialDir = szDirName;

                    if (wPar == ID_BROWSE_RSXW) {
                        ofn.lpstrFilter = "RSXW32 (*.exe)\0*.exe\0";
                        ofn.lpstrTitle = "Select RSXW extender";
                        ofn.Flags = OFN_SHOWHELP | OFN_FILEMUSTEXIST;
                        id = ID_RSXW;
                        bRet = GetOpenFileName(&ofn);
                    }
                    else if (wPar == ID_BROWSE_AOUT) {
                        ofn.lpstrFilter = "GNU-C OUTPUT (*.W32)\0*.w32\0All files (*.exe)\0*.exe\0";
                        ofn.lpstrTitle = "Select a.out file";
                        ofn.Flags = OFN_SHOWHELP | OFN_FILEMUSTEXIST;
                        id = ID_AOUT;
                        bRet = GetOpenFileName(&ofn);
                    }
                    else /* if (wPar == ID_BROWSE_EXE) */ {
                        heapsize = stacksize = 0;
                        bChangeOnlySize = IsDlgButtonChecked(hWnd, ID_ONLYSIZE);

                        ofn.lpstrFilter = "Release Name (*.exe)\0*.exe\0";
                        ofn.lpstrTitle = "Select EXE filename";
                        id = ID_EXE;
                        if (bChangeOnlySize) {
                            ofn.Flags = OFN_SHOWHELP | OFN_FILEMUSTEXIST;
                            bRet = GetOpenFileName(&ofn);
                            if (bRet) {
                                ltoa(heapsize, szText, 10);
                                SetDlgItemText(hWnd, ID_HEAP, szText);
                                ltoa(stacksize, szText, 10);
                                SetDlgItemText(hWnd, ID_STACK, szText);
                            }
                        }
                        else {
                            ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;
                            bRet = GetSaveFileName(&ofn);
                        }
                        /* get size of heap & data */
                    }

                    if (bRet) {
                        char *s;

                        /* display browsed file */
                        SetDlgItemText(hWnd, id, szFile);

                        /* set standard Directory Path */
                        strcpy(szDirName, szFile);
                        s = szDirName + strlen(szDirName);
                        while (s > szDirName && *--s != '\\')
                            ;
                        *s = '\0';
                    }
                    return TRUE;

            } /* switch (wPar) */

            break;

        case WM_SYSCOMMAND :
            if (wPar == SC_CLOSE) {
                EndDialog(hWnd, FALSE);
                return TRUE;
            }
            break;

    } /* switch (wMsg)*/

    return FALSE;
}

static void register_ctl3d(BOOL init, HINSTANCE hInst)
{
#ifdef _WIN32
#define CTL3D_LIB "CTL3D32.DLL"
#else
#define CTL3D_LIB "CTL3DV2.DLL"
#endif

    typedef BOOL (WINAPI * CTL3D_REGISTER)   (HINSTANCE hModule);
    typedef BOOL (WINAPI * CTL3D_UNREGISTER) (HINSTANCE hModule);
    typedef BOOL (WINAPI * CTL3D_AUTOSUBCLASS) (HINSTANCE hModule);

    static CTL3D_REGISTER       pRegister3d;
    static CTL3D_UNREGISTER     pUnRegister3d;
    static CTL3D_AUTOSUBCLASS   pAutoSubclass3d;
    static HANDLE               hCtl3d;
    static BOOL                 bCtl3d;

    if (init == FALSE) {
        if (bCtl3d == TRUE)
            (*pUnRegister3d)(hInst);
        bCtl3d = FALSE;
    } else {
        UINT error_mode = SetErrorMode(SEM_NOOPENFILEERRORBOX);
        hCtl3d = LoadLibrary( CTL3D_LIB );
        SetErrorMode(error_mode);

        if ((int) hCtl3d > 32) {    /* SDK32: error = NULL */
            pRegister3d = (CTL3D_REGISTER)
                    GetProcAddress( hCtl3d, "Ctl3dRegister" );
            pUnRegister3d = (CTL3D_UNREGISTER)
                    GetProcAddress( hCtl3d, "Ctl3dUnregister");
            pAutoSubclass3d = (CTL3D_AUTOSUBCLASS)
                    GetProcAddress( hCtl3d, "Ctl3dAutoSubclass");

            if ( !pRegister3d || !pUnRegister3d || !pAutoSubclass3d) {
                bCtl3d = FALSE;
            } else if ((*pRegister3d)(hInst) == TRUE) {
                bCtl3d = TRUE;
                (*pAutoSubclass3d)(hInst);
            }
        }
    }
}

#ifdef _WIN32
#define MAINENTRY WINAPI
#else
#define MAINENTRY PASCAL
#endif

int MAINENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nCmd)
{
    DLGPROC     lpfnDialog ;
    DWORD       ver;
    int         need3d;

    ver = GetVersion();
    need3d = ((ver & 0xff) < 0x04) ? 1 : 0;     /* not 4.0 */

    if (need3d)
        register_ctl3d(TRUE, hInst);

    hInstance = hInst;

// MakeProcInstance is only useful for WIN16
#ifdef _WIN32
    lpfnDialog = Dialog;
#else      
    lpfnDialog = (DLGPROC) MakeProcInstance((FARPROC) Dialog, hInst);
#endif

    DialogBox(hInst, (LPSTR) "DIALOG_1", NULL, lpfnDialog);
    
// FreeProcInstance is only useful for WIN16
#ifndef _WIN32    
    FreeProcInstance((FARPROC) lpfnDialog);
#endif

    if (need3d)
        register_ctl3d(FALSE, hInst);

    return 0;
}
