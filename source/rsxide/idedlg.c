/* idedlg.c - ide dialogs (except target)

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
#include "editdde.h"

static int Type2Idd (int type)
{
    int idd;

    switch (type)
    {
        case type_win32:
            idd = IDD_TARGET_WIN32;
            break;
        case type_dll:
            idd = IDD_TARGET_DLL;
            break;
        case type_lib:
            idd = IDD_TARGET_LIB;
            break;
        case type_rsx:
            idd = IDD_TARGET_RSX;
            break;
        case type_emx:
            idd = IDD_TARGET_EMX;
            break;
        default:
            idd = IDD_TARGET_WIN32;
    }
    return idd;
}

static int Idd2Type (int idd)
{
    int type;
    
    switch (idd)
    {
        case IDD_TARGET_WIN32:
            type = type_win32;
            break;
        case IDD_TARGET_DLL:
            type = type_dll;
            break;
        case IDD_TARGET_LIB:
            type = type_lib;
            break;
        case IDD_TARGET_RSX:
            type = type_rsx;
            break;
        case IDD_TARGET_EMX:
            type = type_emx;
            break;
        default:
            type = type_win32;
    }
    return type;
}

BOOL CALLBACK DialogTarget(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static struct target * target;
    static int type;
    int iCmdId, len, i;
    
    switch (message) {

        case WM_INITDIALOG :
            target = (struct target *) lParam;
            type = target->type;
            CheckRadioButton(hWnd, IDD_TARGET_WIN32, IDD_TARGET_EMX, Type2Idd(type));
            SetDlgItemText(hWnd, IDD_TARGET_NAME, target->szTargetName);
            return TRUE;

        case WM_COMMAND:
            iCmdId = GET_WM_COMMAND_ID(wParam, lParam); 
            switch (iCmdId) {

                case IDOK:
                    GetDlgItemText(hWnd, IDD_TARGET_NAME, target->szTargetName, MAX_PATH);
                    if (!strchr(target->szTargetName, '.')) {
                        len = strlen(target->szTargetName);
                        target->szTargetName[len] = '.';
                        strcpy(target->szTargetName + len + 1,
                          target_desc[type].ext);
                    }
                    target->type = type;
                    EndDialog(hWnd, TRUE);
                    return TRUE;

                case IDCANCEL:
                    EndDialog(hWnd, FALSE);
                    return TRUE;

                case IDD_TARGET_WIN32:
                case IDD_TARGET_DLL:
                case IDD_TARGET_LIB:
                case IDD_TARGET_RSX:
                case IDD_TARGET_EMX:
                    type = Idd2Type(iCmdId);
                    GetDlgItemText(hWnd, IDD_TARGET_NAME, target->szTargetName, MAX_PATH);

                    len = strlen(target->szTargetName);
                    for (i = len - 1; i > 0; i--)
                       if (target->szTargetName[i] == '.')
                           break;
                    if (!i)
                        target->szTargetName[i = len] = '.';

                    strcpy(target->szTargetName + i + 1, target_desc[type].ext);
                    SetDlgItemText(hWnd, IDD_TARGET_NAME, target->szTargetName);
                    return TRUE;

            }
            break;

        case WM_CHAR :
            if (wParam == VK_ESCAPE) {
                EndDialog(hWnd, 0);
                return TRUE;
            }
            break;

        case WM_SYSCOMMAND :
            if (wParam == SC_CLOSE) {
                EndDialog(hWnd, 0);
                return TRUE;
            }
            break;
    }
    return FALSE;
}

BOOL CALLBACK DialogIdeFlags(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    unsigned long test;
    char szItem[NCHAR_DDE];
    struct dde_editor *dde_e;

    switch (message) {

        case WM_INITDIALOG :
            SetDlgItemText(hWnd, IDD_DDE_EDITOR, dde_editor);
            SetDlgItemText(hWnd, IDD_DDE_SERVICE, dde_service);
            SetDlgItemText(hWnd, IDD_DDE_TOPIC, dde_topic);
            SetDlgItemText(hWnd, IDD_DDE_FILEOPEN, dde_fileopen);
            SetDlgItemText(hWnd, IDD_DDE_GOTO, dde_goto);
            SetDlgItemText(hWnd, IDD_DDE_MARKLINE, dde_markline);

            dde_e = dde_editors;
            while (dde_e->dde_name) {
                ComboBox_AddString(GetDlgItem(hWnd, IDD_DDE_COMBO), dde_e->dde_name);
                dde_e++;
            }
            return TRUE;

        case WM_COMMAND :
            switch (GET_WM_COMMAND_ID(wParam, lParam)) {

                case IDD_DDE_COMBO:

                    if (GET_WM_COMMAND_CMD(wParam, lParam) == CBN_SELCHANGE) {

                        if (!GetDlgItemText(hWnd, IDD_DDE_COMBO, szItem, NCHAR_DDE))
                            return FALSE;

                        dde_e = dde_editors;

                        while (dde_e->dde_name) {
                            if (strcmp(szItem, dde_e->dde_name) == 0) {

                                SetDlgItemText(hWnd, IDD_DDE_EDITOR, dde_e->dde_editor);
                                SetDlgItemText(hWnd, IDD_DDE_SERVICE, dde_e->dde_service);
                                SetDlgItemText(hWnd, IDD_DDE_TOPIC, dde_e->dde_topic);
                                SetDlgItemText(hWnd, IDD_DDE_FILEOPEN, dde_e->dde_fileopen);
                                SetDlgItemText(hWnd, IDD_DDE_GOTO, dde_e->dde_goto);
                                SetDlgItemText(hWnd, IDD_DDE_MARKLINE, dde_e->dde_markline);
                                SendDlgItemMessage(hWnd, IDD_DDE_EDITOR, EM_SETMODIFY, TRUE, 0);
                                break;
                            } else
                                ++dde_e;
                        }
                        return TRUE;
                    }
                    break;

                case IDOK :
                    test = 0;
                    if (SendDlgItemMessage(hWnd, IDD_DDE_EDITOR, EM_GETMODIFY, 0, 0))
                        test |= 1;
                    if (SendDlgItemMessage(hWnd, IDD_DDE_SERVICE, EM_GETMODIFY, 0, 0))
                        test |= 2;
                    if (SendDlgItemMessage(hWnd, IDD_DDE_TOPIC, EM_GETMODIFY, 0, 0))
                        test |= 4;
                    if (SendDlgItemMessage(hWnd, IDD_DDE_FILEOPEN, EM_GETMODIFY, 0, 0))
                        test |= 8;
                    if (SendDlgItemMessage(hWnd, IDD_DDE_GOTO, EM_GETMODIFY, 0, 0))
                        test |= 16;
                    if (SendDlgItemMessage(hWnd, IDD_DDE_MARKLINE, EM_GETMODIFY, 0, 0))
                        test |= 32;

                    if (test) {
                        connect_editor(FALSE);
                        GetDlgItemText(hWnd, IDD_DDE_MARKLINE, dde_markline, NCHAR_DDE);
                        GetDlgItemText(hWnd, IDD_DDE_SERVICE, dde_service, NCHAR_DDE);
                        GetDlgItemText(hWnd, IDD_DDE_TOPIC, dde_topic, NCHAR_DDE);
                        GetDlgItemText(hWnd, IDD_DDE_FILEOPEN, dde_fileopen, NCHAR_DDE);
                        GetDlgItemText(hWnd, IDD_DDE_GOTO, dde_goto, NCHAR_DDE);
                        GetDlgItemText(hWnd, IDD_DDE_EDITOR, dde_editor, NCHAR_DDE);
                    }
                    EndDialog(hWnd, test);
                    return TRUE;

                case IDCANCEL :
                    EndDialog(hWnd, 0);
                    return TRUE;

            }
            break;

        case WM_CHAR :
            if (wParam == VK_ESCAPE) {
                EndDialog(hWnd, 0);
                return TRUE;
            }
            break;

        case WM_SYSCOMMAND :
            if (wParam == SC_CLOSE) {
                EndDialog(hWnd, 0);
                return TRUE;
            }
            break;
    }

    return FALSE;
}

BOOL CALLBACK DialogAbout(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        case WM_COMMAND :
            if (wParam == IDOK) {
                EndDialog(hWnd, 0);
                return TRUE;
            }
            break;

        case WM_CHAR :
            if (wParam == VK_ESCAPE) {
                EndDialog(hWnd, 0);
                return TRUE;
            }
            break;

        case WM_SYSCOMMAND :
            if (wParam == SC_CLOSE) {
                EndDialog(hWnd, 0);
                return TRUE;
            }
            break;
    }
    return FALSE;
}

BOOL CALLBACK DialogInfo(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HBITMAP hBitmap;
    static HBITMAP hOldBitmap;
    static HDC hMemoryDC;
    HDC hDC;
    PAINTSTRUCT ps;
    RECT rect;

    switch (message) {

        case WM_INITDIALOG:
            /* load bitmap */
            hBitmap = LoadBitmap(hInstance, "bmp_about");

            /* get memory DC */
            hDC = GetDC(hWnd);
            hMemoryDC = CreateCompatibleDC(hDC);
            ReleaseDC(hWnd, hDC);

            /* select bitmap */
            hOldBitmap = SelectObject(hMemoryDC, hBitmap);

            /* DlgBox = 200 x 273 pixel */
            GetWindowRect(hWnd, &rect);
            MoveWindow(hWnd, rect.left, rect.top,
                    200 + 2 * GetSystemMetrics(SM_CXDLGFRAME),
                    290 + 2 * GetSystemMetrics(SM_CYDLGFRAME) + GetSystemMetrics(SM_CYBORDER),
                    FALSE);
            return TRUE;

        case WM_PAINT:
            hDC = BeginPaint(hWnd, &ps);
            BitBlt(hDC, 0, 0, 300, 300, hMemoryDC, 0, 0, SRCCOPY);
            EndPaint(hWnd, &ps);
            return TRUE;

        case WM_COMMAND :
            if (GET_WM_COMMAND_ID(wParam, lParam) == IDOK) {
                EndDialog(hWnd, 0);
                return TRUE;
            }
            break;

        case WM_CHAR :
            if (wParam == VK_ESCAPE) {
                EndDialog(hWnd, 0);
                return TRUE;
            }
            break;

        case WM_SYSCOMMAND :
            if (wParam == SC_CLOSE) {
                EndDialog(hWnd, 0);
                return TRUE;
            }
            break;

        case WM_DESTROY:
            /* select old bitmap */
            SelectObject(hMemoryDC, hOldBitmap);

            /* free memory DC */
            DeleteDC(hMemoryDC);

            /* free bitmap */
            DeleteObject(hBitmap);

            return TRUE;
    }
    return FALSE;
}

BOOL CALLBACK DialogInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static char command[MAX_PATH];

    switch (message) {

        case WM_INITDIALOG :
            SetWindowText(hWnd, (LPSTR) lParam);
            return TRUE;

        case WM_COMMAND :
            switch (GET_WM_COMMAND_ID(wParam, lParam))
                {
                case IDOK :
                    GetDlgItemText(hWnd, IDD_EDIT, command, MAX_PATH);
                    EndDialog(hWnd, (int) command);
                    return TRUE;

                case IDCANCEL :
                    EndDialog(hWnd, 0);
                    return TRUE;
                }
            break;

        case WM_CHAR :
            if (wParam == VK_ESCAPE) {
                EndDialog(hWnd, 0);
                return TRUE;
            }
            break;

        case WM_SYSCOMMAND :
            if (wParam == SC_CLOSE) {
                EndDialog(hWnd, 0);
                return TRUE;
            }
            break;

    }
    return FALSE;
}

