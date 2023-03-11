/* WinMain.c - Defines main() function for GUI progs, calls WinMain()

   Copyright (c) 1995-1999 Rainer Schnitker

   This file is part of RSXNT.

   RSXNT is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   RSXNT is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with RSXNT; see the file COPYING.  If not, write to
   the Free Software Foundation, 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA. */

#include <windows.h>
#include <stdlib.h>
#include <alloca.h>

/* Globals for Win32 GUI programs */
int         _argc;
int         __argc;
char **     _argv;
char **     __argv;
unsigned    _osver;
unsigned    _winmajor;
unsigned    _winminor;
unsigned    _winver;

static int my_isspace(unsigned char c)
{
    switch (c) {
        case 0x09:
        case 0x0A:
        case 0x0B:
        case 0x0C:
        case 0x0D:
        case 0x20:
            return 1;
        default:
            return 0;
    }
}

static __inline__ size_t strlen(__const__ char *s)
{
    register int __res __asm__("cx");
    __asm__(
        "cld\n\t"
        "repne\n\t"
        "scasb\n\t"
        "notl %0\n\t"
        "decl %0"
        : "=c" (__res) : "D" (s), "a" (0), "0" (0xffffffff)  );
    return __res;
}

static __inline__ char *strcpy(char *dest, __const__ char *src)
{
    __asm__(
        "cld\n"
        "1:\tlodsb\n\t"
        "stosb\n\t"
        "testb %%al,%%al\n\t"
        "jne 1b"
        : /* no output */
        : "S" (src), "D" (dest) : "ax", "memory");
    return dest;
}

int main(int argc, char **argv, char **env)
{
    STARTUPINFO StartupInfo;
    char *str;
    char *cmdline;

    /* Set globals */
    _argc = __argc = argc;
    _argv = __argv = argv;
    _winver = GetVersion() & 0xffff;
    _winminor = _winver >> 8;
    _winmajor = _winver & 0xff;

    /* Get command-line (!Ansi, not Unicode - Win32 help file) */
    cmdline = GetCommandLineA();

    /* remove arg0 (program name) from cmdline */

    if (*cmdline == '\"') {
        ++cmdline;
        while (*cmdline != '\"' && *cmdline != 0)
            cmdline++;
        if (*cmdline == '\"')
            cmdline++;
    }
    else
        while (!my_isspace(*cmdline) && *cmdline != 0)
            cmdline++;
    while(my_isspace(*cmdline))
        cmdline++;

    /* use alloca, strdup calls malloc() */
    str = alloca(strlen(cmdline) + 1);
    strcpy(str, cmdline);

    StartupInfo.cb = sizeof(STARTUPINFO);
    GetStartupInfo (&StartupInfo);

    __asm__(".stabs\"_WinMain\",5,0,0,_WinMain");

    return WinMain(GetModuleHandle(NULL), 0, str,
                    (StartupInfo.dwFlags & STARTF_USESHOWWINDOW)
                     ? StartupInfo.wShowWindow
                     : SW_SHOWDEFAULT);
}
