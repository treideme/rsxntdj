/* runw32s.c - run win32s process in a window

   Copyright (c) 1996-1999 Rainer Schnitker

   This file is part of RSXIDE.

   RSXIDE is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   RSXIDE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with RSXIDE; see the file COPYING.  If not, write to
   the Free Software Foundation, 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA. */

#include "master.h"
#include "rsxide.h"

typedef int (WINAPI *INITFUNC)(void);
typedef int (WINAPI *READFUNC)(int, void *, int);

static INITFUNC pInitFunc;
static READFUNC pReadFunc;

static BOOL error(char *text)
{
    MessageBox(NULL, text, "compile process", MB_OK);
    return (FALSE);
}

BOOL run_cmd_win32s(LPSTR lpszCmdLine, HWND hListWnd, HWND hIdeWnd, LPSTR lpszDir)
{
    static HANDLE   hLibRsxnt = NULL;
    STARTUPINFO     si;
    PROCESS_INFORMATION procinfo;
    UINT            error_mode;
    char            cline[160];
    int             len;

    if (hLibRsxnt == NULL) {
        error_mode = SetErrorMode(SEM_NOOPENFILEERRORBOX);
        hLibRsxnt = LoadLibrary("RSXNT.DLL");
        SetErrorMode(error_mode);

        if ((int) hLibRsxnt > 32) {
            pInitFunc = (INITFUNC) GetProcAddress(hLibRsxnt, "win32s_init");
            if (!pInitFunc)
                return error("compile: cannot load rsxnt.dll function1");

            pReadFunc = (READFUNC) GetProcAddress(hLibRsxnt, "win32s_read");
            if (!pReadFunc)
                return error("compile: cannot load rsxnt.dll function3");
        } else
            return error("compile: cannot load rsxnt.dll library");
    }

    (*pInitFunc)();

    memset(&si, 0, sizeof (STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (CreateProcess(NULL, lpszCmdLine, NULL, NULL,
            TRUE, DETACHED_PROCESS,
            NULL, lpszDir, &si, &procinfo) == FALSE) {
        return error("compile: cannot create process");
    }
    else
        for (;;) {
            DWORD dw;
            if (GetExitCodeProcess(procinfo.hProcess, &dw) == FALSE)
                break;
            else if (dw != STILL_ACTIVE)
                break;
            Sleep(500);
        }

    while ((len = (*pReadFunc)(0, cline, sizeof(cline))) > 0) {
        cline[len-1] = 0;
        OemToChar(cline, cline);
        ListBox_AddString(hListWnd, cline);
    }

    PostUserMessage(hIdeWnd, WMUSER_COMPILER_STOP);
    return TRUE;
}
