/* runw32.c - run win32 process in a window

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
int CompileListBox_AddString(char *s);

/* pipe read, pipe write */
#define P_READ  0
#define P_WRITE 1

static HWND     hWndList;
static HWND     hWndIde;
static HANDLE   input_handles[2];
static HANDLE   output_handles[2];
static PROCESS_INFORMATION procinfo;
static HANDLE   output_error;

static BOOL error(char *text)
{
    char buf [80];
    sprintf (buf, "error = %ld\n", GetLastError());
    MessageBox(NULL, text, buf, MB_OK|MB_ICONERROR|MB_SETFOREGROUND);
    return (FALSE);
}

static HANDLE InheritHandle(HANDLE hin, BOOL bInherit)
{
    HANDLE hproc;
    HANDLE hout = INVALID_HANDLE_VALUE;

    hproc = GetCurrentProcess();
    DuplicateHandle(hproc, hin, hproc, &hout, 0, bInherit,
            DUPLICATE_CLOSE_SOURCE|DUPLICATE_SAME_ACCESS);

    return hout;
}

static HANDLE DupHandle(HANDLE hin)
{
    HANDLE hproc;
    HANDLE hout = INVALID_HANDLE_VALUE;

    hproc = GetCurrentProcess();
    DuplicateHandle(hproc, hin, hproc, &hout, 0, TRUE, DUPLICATE_SAME_ACCESS);

    return hout;
}

static BOOL connect_process(LPSTR lpszCmdLine, LPSTR lpszDir)
{
    STARTUPINFO si;
    BOOL r;

    /* create pipes with inherit = false */
    if (CreatePipe(&input_handles[P_READ], &input_handles[P_WRITE],
            NULL, 256) == FALSE)
        return error("compile: cannot create pipe");

    if (CreatePipe(&output_handles[P_READ], &output_handles[P_WRITE],
            NULL, 8192) == FALSE)
        return error("compile: cannot create pipe");

    /* inherit client handles */
    input_handles[P_READ] = InheritHandle(input_handles[P_READ], TRUE);
    output_handles[P_WRITE] = InheritHandle(output_handles[P_WRITE], TRUE);
    output_error = DupHandle(output_handles[P_WRITE]);

    memset(&si, 0, sizeof (STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    si.hStdInput = input_handles[P_READ];
    si.hStdOutput = output_handles[P_WRITE];
    si.hStdError = output_error;

    r = CreateProcess(NULL, lpszCmdLine, NULL, NULL,
            TRUE, CREATE_SUSPENDED,
            NULL, lpszDir, &si, &procinfo);

    /* close client handles */
    CloseHandle(input_handles[P_READ]);
    CloseHandle(output_handles[P_WRITE]);
    CloseHandle(output_error);

    if (r == FALSE)
        return error("compile: cannot create process");
    else
        return TRUE;
}

static DWORD WINAPI output_thread(LPVOID lpThreadParameter)
{
    static unsigned char buf2[513];
    char *b2 = buf2;
    unsigned char c;
    DWORD r;

    while (ReadFile(output_handles[P_READ], &c, 1, &r, NULL) == TRUE) {
        if (r > 0) {
            if (c == '\n') {
                *b2 = 0;
                CompileListBox_AddString(buf2);
                b2 = buf2;
            } else if (c == '\t') {
                int i, t;
                t = ((int)b2 - (int)buf2) % 8;
                for (i = 0; i < 8 - t; ++i)
                    *b2++ = ' ';
            } else if (c != '\r') {
                *b2++ = c;
            }
        }
    }
    CloseHandle(input_handles[P_WRITE]);
    CloseHandle(output_handles[P_READ]);
    CloseHandle(output_error);
    return 0;
}

static DWORD WINAPI waiting_thread(LPVOID lpThreadParameter)
{
    WaitForSingleObject (procinfo.hThread, INFINITE);   
    CloseHandle (procinfo.hThread);
    PostUserMessage(hWndIde, WMUSER_COMPILER_STOP);
    return 0;
}

BOOL run_cmd_win32(LPSTR lpszCmdLine, HWND hListWnd, HWND hIdeWnd, LPSTR lpszDir)
{
    DWORD tid;

    hWndList = hListWnd;
    hWndIde = hIdeWnd;

    if (connect_process(lpszCmdLine, lpszDir) == TRUE) {
        CloseHandle (CreateThread(NULL, 0, output_thread, 0, 0, &tid));
        ResumeThread(procinfo.hThread);
        CloseHandle (CreateThread(NULL, 0, waiting_thread, 0, 0, &tid));
        return TRUE;
    }
    else {
        CloseHandle(input_handles[P_WRITE]);
        CloseHandle(output_handles[P_READ]);
        CloseHandle(output_error);
        return FALSE;
    }
}

