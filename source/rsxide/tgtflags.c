/* tgtflags.c - target flags dialog

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
#include "iddlg.h"
#include "idedlg.h"

enum { DLG_GCC = 0, DLG_CPP, DLG_CC1, DLG_LD };
enum { ACTION_INIT, ACTION_CTRL, ACTION_EXIT };

struct target * target;

void get_opt_text (HWND hWnd, char ** pszOpt)
{
    char pszTmp[512];

    GetWindowText (hWnd, pszTmp, sizeof(pszTmp)-1);

    if (*pszOpt != NULL) {
        if (strcmp (pszTmp, *pszOpt) == 0)
            return;
        else {
            free (*pszOpt);
            *pszOpt = NULL;
        }
    }
    if (pszTmp[0])
        *pszOpt = strdup (pszTmp);
}

static void gcc_flags (HWND hWnd, int iId, int iAction)
{
    static const char * cb_text [] =
    {
        "Static C library",
        "C runtime DLL (-Zcrtdll)",
        "No runtime env (-Zno-rte)",
        "System library (-Zsys/-Zso)"
    };
    int i;
    
    if (iAction == ACTION_INIT)
    {
        for (i = 0; i < (sizeof(cb_text)/sizeof(char *)); ++i)
            ComboBox_AddString(GetDlgItem(hWnd, IDD_OPT_COMBO), cb_text[i]);
        ComboBox_SetCurSel (GetDlgItem(hWnd, IDD_OPT_COMBO), target->flags.s.gcc_runtime);

        if (target->flags.s.gcc_debug)
            CheckDlgButton(hWnd, IDD_OPT_DEBUG, BST_CHECKED);
        if (target->flags.s.gcc_multithread)
            CheckDlgButton(hWnd, IDD_OPT_MULTI, BST_CHECKED);
        if (target->flags.s.gcc_print)
            CheckDlgButton(hWnd, IDD_OPT_PRINT, BST_CHECKED);
        if (target->flags.s.gcc_pipe)
            CheckDlgButton(hWnd, IDD_OPT_PIPE, BST_CHECKED);
        if (target->flags.s.gcc_other)
            SetDlgItemText(hWnd, IDD_OPT_GCCOTHER, target->flags.s.gcc_other);
        if (target->flags.s.second_link_cmd)
            SetDlgItemText(hWnd, IDD_OPT_BIND, target->flags.s.second_link_cmd);
    }
    else if (iAction == ACTION_EXIT)
    {
        if (target->type == type_win32 || target->type == type_dll)
            target->flags.s.gcc_runtime = ComboBox_GetCurSel(GetDlgItem(hWnd, IDD_OPT_COMBO));
        else
            target->flags.s.gcc_runtime = 0;

        target->flags.s.gcc_debug =
            (IsDlgButtonChecked(hWnd, IDD_OPT_DEBUG) == BST_CHECKED) ? 1 : 0;
        target->flags.s.gcc_multithread =
            (IsDlgButtonChecked(hWnd, IDD_OPT_MULTI) == BST_CHECKED) ? 1 : 0;
        target->flags.s.gcc_print =
            (IsDlgButtonChecked(hWnd, IDD_OPT_PRINT) == BST_CHECKED) ? 1 : 0;
        target->flags.s.gcc_pipe =
            (IsDlgButtonChecked(hWnd, IDD_OPT_PIPE) == BST_CHECKED) ? 1 : 0;

        get_opt_text (GetDlgItem(hWnd, IDD_OPT_GCCOTHER), & target->flags.s.gcc_other);
        get_opt_text (GetDlgItem(hWnd, IDD_OPT_BIND), & target->flags.s.second_link_cmd);
    }
}

static void cpp_flags (HWND hWnd, int iId, int iAction)
{
    if (iAction == ACTION_INIT)
    {
        if (target->flags.s.cpp_nostdinc)
            CheckDlgButton(hWnd, IDD_OPT_NOSTDINC, BST_CHECKED);
        if (target->flags.s.cpp_include)
            SetDlgItemText(hWnd, IDD_OPT_INC, target->flags.s.cpp_include);
        if (target->flags.s.cpp_macros)
            SetDlgItemText(hWnd, IDD_OPT_MACROS, target->flags.s.cpp_macros);
        if (target->flags.s.cpp_umacros)
            SetDlgItemText(hWnd, IDD_OPT_UMACROS, target->flags.s.cpp_umacros);
        if (target->flags.s.cpp_other)
            SetDlgItemText(hWnd, IDD_OPT_CPPOTHER, target->flags.s.cpp_other);
        if (target->flags.s.cpp_incfile)
            SetDlgItemText(hWnd, IDD_OPT_INCFILE, target->flags.s.cpp_incfile);
        if (target->flags.s.cpp_incmac)
            SetDlgItemText(hWnd, IDD_OPT_INCMAC, target->flags.s.cpp_incmac);
    }
    else if (iAction == ACTION_EXIT)
    {
        get_opt_text (GetDlgItem(hWnd, IDD_OPT_INC), & target->flags.s.cpp_include);
        get_opt_text (GetDlgItem(hWnd, IDD_OPT_MACROS), & target->flags.s.cpp_macros);
        get_opt_text (GetDlgItem(hWnd, IDD_OPT_UMACROS), & target->flags.s.cpp_umacros);
        get_opt_text (GetDlgItem(hWnd, IDD_OPT_CPPOTHER), & target->flags.s.cpp_other);
        get_opt_text (GetDlgItem(hWnd, IDD_OPT_INCFILE), & target->flags.s.cpp_incfile);
        get_opt_text (GetDlgItem(hWnd, IDD_OPT_INCMAC), & target->flags.s.cpp_incmac);
        target->flags.s.cpp_nostdinc =
            (IsDlgButtonChecked(hWnd, IDD_OPT_NOSTDINC) == BST_CHECKED) ? 1 : 0;
    }
}

static void cc1_flags (HWND hWnd, int iId, int iAction)
{
    if (iAction == ACTION_INIT)
    {
        CheckDlgButton(hWnd,  
            (target->flags.s.cc1_opt == opt_none) ? IDD_OPT_OPTNO :
            (target->flags.s.cc1_opt == opt_l1) ? IDD_OPT_OPT1 :
            (target->flags.s.cc1_opt == opt_l3) ? IDD_OPT_OPT3 : IDD_OPT_OPT2,
              BST_CHECKED);
        CheckDlgButton(hWnd,  
            (target->flags.s.cc1_warnings == warn_none) ? IDD_OPT_WARNNO :
            (target->flags.s.cc1_warnings == warn_extra) ? IDD_OPT_WARNEXT : IDD_OPT_WARNALL,
              BST_CHECKED);
        CheckDlgButton(hWnd,  
            (target->flags.s.cc1_style == style_ansi) ? IDD_OPT_ANSI :
            (target->flags.s.cc1_style == style_traditional) ? IDD_OPT_TRADI : IDD_OPT_GNU,
              BST_CHECKED);
        if (target->flags.s.cc1_486)
            CheckDlgButton(hWnd, IDD_OPT_486, BST_CHECKED);
        if (target->flags.s.cc1_ebp)
            CheckDlgButton(hWnd, IDD_OPT_EBP, BST_CHECKED);
        if (target->flags.s.cc1_pedantic)
            CheckDlgButton(hWnd, IDD_OPT_WARNPED, BST_CHECKED);
        if (target->flags.s.cc1_error)
            CheckDlgButton(hWnd, IDD_OPT_WARNERR, BST_CHECKED);
        if (target->flags.s.cc1_other)
            SetDlgItemText(hWnd, IDD_OPT_CC1OTHER, target->flags.s.cc1_other);
        if (target->flags.s.cc1_sigchar)
            CheckDlgButton(hWnd, IDD_OPT_SIGCHAR, BST_CHECKED);
        if (target->flags.s.cc1_unsigbit)
            CheckDlgButton(hWnd, IDD_OPT_UNSIGBIT, BST_CHECKED);
        if (target->flags.s.cc1_writestr)
            CheckDlgButton(hWnd, IDD_OPT_WRITESTR, BST_CHECKED);
    }
    else if (iAction == ACTION_EXIT)
    {
        target->flags.s.cc1_opt =
            (IsDlgButtonChecked(hWnd, IDD_OPT_OPTNO)) ? opt_none :
            (IsDlgButtonChecked(hWnd, IDD_OPT_OPT1)) ? opt_l1 :
            (IsDlgButtonChecked(hWnd, IDD_OPT_OPT3)) ? opt_l3 : opt_l2;
        target->flags.s.cc1_warnings =
            (IsDlgButtonChecked(hWnd, IDD_OPT_WARNNO)) ? warn_none :
            (IsDlgButtonChecked(hWnd, IDD_OPT_WARNEXT)) ? warn_extra : warn_all;
        target->flags.s.cc1_style =
            (IsDlgButtonChecked(hWnd, IDD_OPT_ANSI)) ? style_ansi :
            (IsDlgButtonChecked(hWnd, IDD_OPT_TRADI)) ? style_traditional : style_gnu;
        target->flags.s.cc1_486 =
            (IsDlgButtonChecked(hWnd, IDD_OPT_486) == BST_CHECKED) ? 1 : 0;
        target->flags.s.cc1_ebp =
            (IsDlgButtonChecked(hWnd, IDD_OPT_EBP) == BST_CHECKED) ? 1 : 0;
        target->flags.s.cc1_pedantic =
            (IsDlgButtonChecked(hWnd, IDD_OPT_WARNPED) == BST_CHECKED) ? 1 : 0;
        target->flags.s.cc1_error =
            (IsDlgButtonChecked(hWnd, IDD_OPT_WARNERR) == BST_CHECKED) ? 1 : 0;
        get_opt_text (GetDlgItem(hWnd, IDD_OPT_CC1OTHER), & target->flags.s.cc1_other);
        target->flags.s.cc1_sigchar =
            (IsDlgButtonChecked(hWnd, IDD_OPT_SIGCHAR) == BST_CHECKED) ? 1 : 0;
        target->flags.s.cc1_unsigbit =
            (IsDlgButtonChecked(hWnd, IDD_OPT_UNSIGBIT) == BST_CHECKED) ? 1 : 0;
        target->flags.s.cc1_writestr =
            (IsDlgButtonChecked(hWnd, IDD_OPT_WRITESTR) == BST_CHECKED) ? 1 : 0;
    }
}

static void ld_flags (HWND hWnd, int iId, int iAction)
{
    if (iAction == ACTION_INIT)
    {
        if (target->flags.s.ld_libs)
            SetDlgItemText(hWnd, IDD_OPT_LIBS, target->flags.s.ld_libs);
        if (target->flags.s.ld_ldir)
            SetDlgItemText(hWnd, IDD_OPT_LDIR, target->flags.s.ld_ldir);
        if (target->flags.s.ld_other)
            SetDlgItemText(hWnd, IDD_OPT_LDOTHER, target->flags.s.ld_other);
        if (target->flags.s.ld_nostdo)
            CheckDlgButton(hWnd, IDD_OPT_NOSTDO, BST_CHECKED);
        if (target->flags.s.ld_nostdlib)
            CheckDlgButton(hWnd, IDD_OPT_NOSTDLIB, BST_CHECKED);
    }
    else if (iAction == ACTION_EXIT)
    {
        get_opt_text (GetDlgItem(hWnd, IDD_OPT_LIBS), & target->flags.s.ld_libs);
        get_opt_text (GetDlgItem(hWnd, IDD_OPT_LDIR), & target->flags.s.ld_ldir);
        get_opt_text (GetDlgItem(hWnd, IDD_OPT_LDOTHER), & target->flags.s.ld_other);
        target->flags.s.ld_nostdo =
            (IsDlgButtonChecked(hWnd, IDD_OPT_NOSTDO) == BST_CHECKED) ? 1 : 0;
        target->flags.s.ld_nostdlib =
            (IsDlgButtonChecked(hWnd, IDD_OPT_NOSTDLIB) == BST_CHECKED) ? 1 : 0;
    }
}

BOOL CALLBACK
DialogPropertyPage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, int iPage)
{
    static union target_flags target_flags_undo;
    
    switch (message) {

        case WM_INITDIALOG :
            target = (struct target *) (((LPPROPSHEETPAGE)lParam)->lParam);
            memcpy (& target_flags_undo, & target->flags, sizeof(target_flags_undo));

            if (iPage == DLG_GCC)
                gcc_flags(hWnd, 0, ACTION_INIT);
            else if (iPage == DLG_CPP)
                cpp_flags(hWnd, 0, ACTION_INIT);
            else if (iPage == DLG_CC1)
                cc1_flags(hWnd, 0, ACTION_INIT);
            else if (iPage == DLG_LD)
                ld_flags(hWnd, 0, ACTION_INIT);

            return TRUE;

        case WM_NOTIFY:
            switch (((NMHDR *) lParam)->code) {

               // case PSN_ACTIVATE:
                
                case PSN_APPLY:
                    if (iPage == DLG_GCC)
                        gcc_flags(hWnd, 0, ACTION_EXIT);
                    else if (iPage == DLG_CPP)
                        cpp_flags(hWnd, 0, ACTION_EXIT);
                    else if (iPage == DLG_CC1)
                        cc1_flags(hWnd, 0, ACTION_EXIT);
                    else if (iPage == DLG_LD)
                        ld_flags(hWnd, 0, ACTION_EXIT);
                    SetWindowLong (hWnd, DWL_MSGRESULT, FALSE);
                    return TRUE;
                                
                case PSN_RESET:
                    memcpy (& target->flags, & target_flags_undo, sizeof(target_flags_undo));
                    SetWindowLong (hWnd, DWL_MSGRESULT, FALSE);
                    return TRUE;
            }
            break;
        
        case WM_COMMAND :
        {
            int iCmdId = GET_WM_COMMAND_ID(wParam, lParam); 
            
            if (iPage == DLG_GCC)
                gcc_flags(hWnd, iCmdId, ACTION_CTRL);
            else if (iPage == DLG_CPP)
                cpp_flags(hWnd, iCmdId, ACTION_CTRL);
            else if (iPage == DLG_CC1)
                cc1_flags(hWnd, iCmdId, ACTION_CTRL);
            else if (iPage == DLG_LD)
                ld_flags(hWnd, iCmdId, ACTION_CTRL);
        }
            break;
    }
    return FALSE;
}

BOOL CALLBACK DialogTargetGCCFlags(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DialogPropertyPage(hWnd, message, wParam, lParam, DLG_GCC);
}

BOOL CALLBACK DialogTargetCPPFlags(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DialogPropertyPage(hWnd, message, wParam, lParam, DLG_CPP);
}

BOOL CALLBACK DialogTargetCCFlags(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DialogPropertyPage(hWnd, message, wParam, lParam, DLG_CC1);
}

BOOL CALLBACK DialogTargetLDFlags(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DialogPropertyPage(hWnd, message, wParam, lParam, DLG_LD);
}

