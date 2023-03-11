/* cdlgtool.c - Common dialog tools by Alfons Hoogervorst
 *
 * Written by Alfons Hoogervorst, 1995-1997, proteus@worldaccess.nl.        */

/*
 * @DOC
 * @module cdlgtool.c |
 * Functions and routines that will help you to get the selected
 * file's path. The only obvious nontrivial way I could come
 * up with. It enlarges stc1 (the static control with the currently
 * selected path), hides it and moves it out of the common dialogs
 * client area. Because it's enlarged, the COMMDLG DLL will NOT
 * abbreviate the current path. So getting the file path is just
 * as easy as getting the text of stc1. There's one catch: we have
 * to make our own static to mimic stc1's purpose.
 *
 * @index cdlgtool.c | func
 *
 * ASSUMPTIONS:
 *
 * - stc1 gets a WM_SETTEXT whenever the path is changed and
 *   does abbreviate the text when the path doesn't fit in
 *   the stc1's client rectangle.
 *
 * - Does not check if common dialog is of an explorer type
 *   (can handle this in WM_INITDIALOG though)
 *
 * - Uses private message to communicate wit subclassed
 *   stc1 (could have used a registered window message)
 *
 * - Properties of subclass are deleted on a WM_NCDESTROY,
 *   assuming WM_NCDESTROY is the last message ever received
 *   by a window. This should be true for all Windows versions,
 *   but you'll never know.
 *
 * - For properties I could have used unique names.
 */

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include "compiler.h"
#include <windows.h>
#include <commdlg.h>
#include <dlgs.h>
/* Bombs  ^^^^^^ this header? Remove the include and it should work fine. */
#include <string.h>
#include <stdarg.h>
#include "cdlgtool.h"

/* Configurables */

/* ANSI C macro for debugging. If defined, CDLGTOOL will not output diag
 * messages with OutputDebugString().                                       */
#define NDEBUG

/* Maximum number of characters to output to OutputDebugString()            */
#define MAX_LOG_ERROR_TEXT  512

/* Last message received by a window. Used to delete properties attached to
 * the subclassed stc1. Should be WM_NCDESTROY; don't expect this to change */
#define WM_LAST_WINDOW_MESSAGE      WM_NCDESTROY

/* Identifier for static control we add to the dialog. This control mimics
 * the behaviour of stc1.                                                   */
#define IDC_NEW_STATIC      600

/* The message posted whenever IDC_NEW_STATIC should try to abbreviate the
 * currently selected file name. This message is posted from the subclassed
 * stc1. WM_PATHCHANGE may be a variable for a registered windows message.
 * (I do not use a switch(), because it only allows for constant expressions). */
#define WM_PATHCHANGE       WM_USER + 0xABA

#ifndef NDEBUG
#define WinTrace        WinLogError
/* Nifty code stolen from my INJDLL.. */
void WinLogError(LPCSTR Message, ...)
{
    char buf[MAX_LOG_ERROR_TEXT];
    va_list start;
    va_start(start, Message);
    wvsprintf(buf, Message, start);
    OutputDebugString(buf);
    va_end(start);
}
#else
#define WinTrace        1 == 1 ? 0 :
#endif

/* Define things if not defined by dlgs.h and/or commdlg.h */
#ifndef OFN_EXPLORER
#define OFN_EXPLORER    0x00080000
#endif

#ifndef stc1
#define stc1            0x0440
#endif

#ifndef lst2
#define lst2            1121
#endif

#ifndef lst1
#define lst1            1120
#endif

/* PropHandler - Stores the handler for WM_PATHCHANGEs                      */
#define PropHandler         "HF9FOS::Handler"
#define GetHandler(hwnd)    (HWND)GetProp(hwnd, PropHandler)
#define PostPathChange(hwnd)    \
        PostMessage(GetHandler(hwnd), WM_PATHCHANGE, 0, 0)

#if defined (WIN32) || defined(_WIN32)
#define PropOldProc         "HF9FOS::OldProc"
#define CallOldProc(hwnd, msg, wp, lp) \
    CallWindowProc((LPVOID)(WNDPROC)GetProp(hwnd, PropOldProc), hwnd, msg, wp, lp)
#else
#define PropOldProcLo        "HF9FOS::OPLo"
#define PropOldProcHi        "HF9FOS::OPHi"
#define CallOldProc(hwnd, msg, wp, lp) \
    CallWindowProc((LPVOID)(WNDPROC)MAKELONG(\
        GetProp(hwnd, PropOldProcLo),\
        GetProp(hwnd, PropOldProcHi)), hwnd, msg, wp, lp)
#endif

static LRESULT CALLBACK SubclassedStaticProc(HWND Static,
    UINT Msg, WPARAM WParam, LPARAM LParam)
{
/* Common dialog changed the text of stc1, notify our static */
    if ( Msg == WM_SETTEXT ) {
        PostPathChange(Static);
    } else if ( Msg == WM_LAST_WINDOW_MESSAGE ) {
        LRESULT l = CallOldProc(Static, Msg, WParam, LParam);
        RemoveProp(Static, PropHandler);
#if defined(_WIN32) || defined(WIN32)
        RemoveProp(Static, PropOldProc);
#else
        RemoveProp(Static, PropOldProcLo);
        RemoveProp(Static, PropOldProcHi);
#endif
        return l;
    }
    return CallOldProc(Static, Msg, WParam, LParam);
}

/* Common_OnInitDialog initializes the things. */
static void CommDlg_OnInitDialog(HWND Dlg)
{
    HWND DirStatic = GetDlgItem(Dlg, stc1), NewStatic;
    RECT ClientRect, StaticRect;
    HDC  hDC;
    HFONT hFont, hOldFont;
    TEXTMETRIC tm;
    GetWindowRect(DirStatic, &StaticRect);
    MapWindowPoints(HWND_DESKTOP, Dlg, (LPPOINT)&StaticRect, 4);
    if ( NULL == (NewStatic = CreateWindowEx(
            GetWindowLong(DirStatic, GWL_EXSTYLE),
            (LPSTR)"static", (LPSTR)"",
/* Should prevent word wrapping! */
            GetWindowLong(DirStatic, GWL_STYLE) | SS_LEFTNOWORDWRAP,
            StaticRect.left, StaticRect.top,
            StaticRect.right  - StaticRect.left,
            StaticRect.bottom - StaticRect.top,
            Dlg, (HMENU)IDC_NEW_STATIC,
            CurrentInstance(), NULL)) ) {
        WinTrace("FAILURE: creation of static");
    }
    hFont = (HFONT)SendMessage(DirStatic, WM_GETFONT, 0, 0);
    if ( hFont == 0 ) hFont = GetStockObject(SYSTEM_FONT);
    SendMessage(NewStatic, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(1,0));

    hDC = GetDC(Dlg);
    hOldFont = SelectObject(hDC, hFont);
    GetTextMetrics(hDC, &tm);
    SelectObject(hDC, hOldFont);
    ReleaseDC(Dlg, hDC);
    GetClientRect(Dlg, &ClientRect);

/* Move old static */
    SetWindowPos(DirStatic, NULL, 0, ClientRect.bottom,
        tm.tmMaxCharWidth * MAX_PATH,
        StaticRect.bottom - StaticRect.top,
        SWP_NOZORDER | SWP_HIDEWINDOW | SWP_NOACTIVATE
        | SWP_NOREDRAW);

/* Attach properties */
    SetProp(DirStatic, PropHandler, (HANDLE)Dlg);
#if defined(_WIN32) || defined(WIN32)
    SetProp(DirStatic, PropOldProc, (HANDLE)GetWindowLong(DirStatic, GWL_WNDPROC));
#else
    SetProp(DirStatic, PropOldProcLo, (HANDLE)LOWORD(GetWindowLong(DirStatic, GWL_WNDPROC)));
    SetProp(DirStatic, PropOldProcHi, (HANDLE)HIWORD(GetWindowLong(DirStatic, GWL_WNDPROC)));
#endif
/* Subclass static */
    SetWindowLong(DirStatic, GWL_WNDPROC, (LONG)SubclassedStaticProc);
/* We're ready to go, post a change of path */
    PostPathChange(DirStatic);
}

static void CommDlg_OnPathChange(HWND Dlg)
{
    HWND DirStatic = GetDlgItem(Dlg, stc1),
         OurStatic = GetDlgItem(Dlg, IDC_NEW_STATIC);
    HFONT DlgFont;
    char Buffer[MAX_PATH+1], * Last, * Walk,
         Result[MAX_PATH+1]; /* This one's too big. Need this.
                                Programmer may have a large
                                static in template */
    RECT OurRect;
    TEXTMETRIC Metrics;
    HDC DC;
    SIZE Size;
    int TextLen, LastPart, OldMapMode;
    int Min, Max, Mid, Bigger, Smaller;
    GetClientRect(OurStatic, &OurRect);
    DlgFont = (HFONT)SendMessage(Dlg, WM_GETFONT, 0, 0);
    if ( DlgFont == NULL ) DlgFont = GetStockObject(SYSTEM_FONT);
    DC = GetDC(Dlg);
    DlgFont = SelectObject(DC, DlgFont);
/* Programmer may use a dialog template based on own class */
    OldMapMode = SetMapMode(DC, MM_TEXT);
    GetTextMetrics(DC, &Metrics);
    TextLen = GetWindowText(DirStatic, Buffer, MAX_PATH);
    GetTextExtentPoint(DC, Buffer, TextLen, &Size);
/* Fits in static */
    if ( Size.cx <= OurRect.right ) {
        SetWindowText(OurStatic, Buffer);
        goto C_OPC;
    }
/* Must do our thing. Last points at the last directory part of
 * the selected path.                                                       */
    Last = strrchr(Buffer, '\\');
    if ( !Last ) {
        WinTrace("FAILURE: No last directory found");
        goto C_OPC;
    }
/* Walk walks the potentially valid characters to include in the
 * abbreviated path.                                                        */
    Walk = strchr(Buffer, '\\');
    if ( Walk == Last ) {
        SetWindowText(OurStatic, Buffer);
        goto C_OPC;
    }
/* Get widths of "fixed" strings, i.e.  the parts we always want to
 * see on screen                                                            */
    GetTextExtentPoint(DC, (LPCSTR)"...", 3, &Size);
    LastPart = Size.cx;
    GetTextExtentPoint(DC, Last, TextLen - (Last - Buffer), &Size);
    LastPart += Size.cx;

/* Min == Start character, Max == Last character */
    Smaller = Min = Walk + 1 - Buffer;
    Bigger  = Max = Last - Buffer;

/* If this is phoney, don't blame it on Newton. Stole this from one
 * of my text formatting routines and more or less verbatimly
 * inserted it in this code. I know it's faster than walking the
 * the string in a linear fashion.
 *
 * ANECDOTE: Alfons claims he "discovered" this way to format text
 * during a calculus lecture (when he was a plain student physics
 * and computers were just his hobby). If this algorithm isn't as
 * programmer optimized as it should be, blame it on Alfons'
 * mantra "aesthetics before coding". Physics == aesthetics.                */

/* HINT: Mid has the number of characters we're looking at.                 */

#define GRANULARITY         1
    while ( Min < Max ) {
        Mid = ((Max + Min) / 2);
        GetTextExtentPoint(DC, Buffer, Mid, &Size);
        if ( Size.cx + LastPart < OurRect.right ) {
/* May be bigger. We're strongly biased towards smaller values. Why?
 * Because we're using integer division and rounding.                       */
            Min = Mid + GRANULARITY;
            Smaller = Mid;
            Max = Bigger;
        } else {
/* May be smaller. */
            Max = Mid - GRANULARITY;
            Bigger = Mid;
            Min = Smaller;
        }
    }

/* Yummy! Got a cookie back! */
    lstrcpyn(Result, Buffer, Mid);
    strcat(Result, "...");
    strcat(Result, Last);
    SetWindowText(OurStatic, Result);

C_OPC:
    SetMapMode(DC, OldMapMode);
    SelectObject(DC, DlgFont);
    ReleaseDC(Dlg, DC);
}

/*-PUB----------------------------------------------------------------------*
    @func Pretranslates messages for a common file open dialog hook
    procedure. This function should be called before your hook function
    handles a message.

    @rdesc This function does not return a value.
 *--------------------------------------------------------------------------*/
void PreTranslateHookMessage(
    HWND Dlg,               /* @parm Window handle of common dialog         */
    UINT Msg,               /* @parm Current message                        */
    WPARAM WParam,          /* @parm Message's wParam                       */
    LPARAM LParam)          /* @parm Message's lParam                       */
{
    if ( Msg == WM_INITDIALOG )
        CommDlg_OnInitDialog(Dlg);
    else if ( Msg == WM_PATHCHANGE )
        CommDlg_OnPathChange(Dlg);
}

/*-PUB----------------------------------------------------------------------*
    @func Returns the currently selected path in the common dialog. If
    it returns a negative number, the Result buffer should be sizeof
    abs(result). Else it returns the length of the returned string.

    @rdec This function returns one of the following values:
    @flag 0  | Error.
    @flag >0 | Success, length of string returned in <p Result>.
    @flag <0 | Required size for <p Result>.
 *--------------------------------------------------------------------------*/
int GetCurrentPath(
    HWND Dlg,           /* @parm Window handle of common dialog             */
    LPSTR Result,       /* @parm Buffer which receives the selected path    */
    int ResultLen)      /* @parm Number of chars that fit in Result,
                            counting the 0 terminator                       */
{
    int DirLen = GetWindowTextLength(GetDlgItem(Dlg, stc1));
    if ( DirLen == 0 ) return 0;
    if ( DirLen > ResultLen - 1 ) return -(DirLen + 1);
    return GetWindowText(GetDlgItem(Dlg, stc1), Result, ResultLen);
}

/*-PUB----------------------------------------------------------------------*
    @func Returns the full path of the currently selected file. If there's
    no file selected (or if any error occurred) returns 0. A negative number
    is returned when the returned string does not fit in the buffer.
    @rdesc One of the following values is returned:
    @flag  0    | Error
    @flag  <0   | Required size of <p Result>
    @flag  >0   | Number of characters returned in <p Result>
 *--------------------------------------------------------------------------*/
int GetSelectedFilePath(
    HWND Dlg,                   /* @parm Window handle of common dialog     */
    LPSTR Result,               /* @parm Buffer which receives the selected
                                   files' full pathname                     */
    int ResultLen)              /* @parm The number of characters that fit in
                                    <p Buffer> including the zero byte      */
{
    int FileLen, DirLen, SelFile;
    LPSTR Walk;
/* Check length of selected file */
    SelFile = SendDlgItemMessage(Dlg, lst1, LB_GETCURSEL, 0, 0);
    if ( SelFile == LB_ERR ) return 0;
    DirLen = GetWindowTextLength(GetDlgItem(Dlg, stc1));
    FileLen = SendDlgItemMessage(Dlg, lst1, LB_GETTEXTLEN,
        (WPARAM)SelFile, 0);
    if ( DirLen == 0 || FileLen == 0 ) return 0;
    ResultLen--;
    if ( DirLen + FileLen + 1 > ResultLen )
        return -(DirLen + FileLen + 1);
/* Try to get the text */
    DirLen = GetWindowText(GetDlgItem(Dlg, stc1), Result, ResultLen);
    if ( DirLen == 0 ) return 0;
    Walk = Result;
    while ( *Walk ) Walk++;
    if ( *(Walk - 1) != '\\' ) *Walk++ = '\\', DirLen++;
/* Try to get the text */
    if ( DirLen + FileLen  > ResultLen ) return -(DirLen + FileLen + 1);
    FileLen = SendDlgItemMessage(Dlg, lst1, LB_GETTEXT, (WPARAM)SelFile,
        (LPARAM)(LPVOID)Walk);
    return FileLen + DirLen;
}

BOOL CDlgTool_GetOpenFileName(LPOPENFILENAME lpOpenFileName)
{
    return GetOpenFileName(lpOpenFileName);
}

#ifdef WIN32
HINSTANCE __CurrentInstance(void)
{
    return (HINSTANCE)GetModuleHandle(NULL);
}
#else
HINSTANCE __CurrentInstance(void)
{
    LPVOID Nothing;
    return (HINSTANCE)SELECTOROF((LPVOID)&Nothing);
}
#endif
