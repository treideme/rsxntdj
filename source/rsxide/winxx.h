#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>
#include <shellapi.h>
#include <commdlg.h>
#include <commctrl.h>
#include <ddeml.h>
#include <windowsx.h>   /* after shellapi !! */

//
// missing in windowsx.h
//
#ifndef FORWARD_SB_SETTEXT
#define FORWARD_SB_SETTEXT(hwnd, part, type, text, fn) \
    (void)(fn)((hwnd), SB_SETTEXT, (WPARAM)((part)|(type)),(LPARAM)(text))
#endif
#ifndef FORWARD_SB_SETPARTS
#define FORWARD_SB_SETPARTS(hwnd, npart, width, fn) \
    (void)(fn)((hwnd), SB_SETPARTS, (WPARAM)(npart),(LPARAM)(LPINT)(width))
#endif

/* WM_USER messages (wparam) */
#define WMUSER_COMPILER_STOP 1

#define HANDLE_WM_USER(hwnd, wParam, lParam, fn) \
    ((fn)((hwnd), (int) (wParam)), 0L)
#define PostUserMessage(hwnd, code) PostMessage(hwnd, WM_USER, (code), 0L)
