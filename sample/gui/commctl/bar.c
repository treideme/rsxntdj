/*
    BAR.C

    (c) Rainer Schnitker 1996,1997

    This example use a toolbar and tooltips (win95 style)

*/

#ifdef __GNUC__
#include <crtrsxnt.h>
#endif

#define  STRICT
#define  WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commctrl.h>
#include <windowsx.h>
#include "bar.h"

//
// missing in original commctl.h and windowsx.h
//
#ifndef FORWARD_SB_SETTEXT
#define FORWARD_SB_SETTEXT(hwnd, part, type, text, fn) \
    (void)(fn)((hwnd), SB_SETTEXT, (WPARAM)((part)|(type)),(LPARAM)(text))
#endif
#ifndef FORWARD_SB_SETPARTS
#define FORWARD_SB_SETPARTS(hwnd, npart, width, fn) \
    (void)(fn)((hwnd), SB_SETPARTS, (WPARAM)(npart),(LPARAM)(LPINT)(width))
#endif

//
// local vars
//
static char	    szAppName[16];
static char	    szTitle[80];
static HINSTANCE    hInst;
static HWND	    hWndToolbar;
static HWND	    hWndStatusbar;

//
// set parts and text of the status bar
//
static void InitStatusBar(HWND hwndParent)
{
    const char cSpaceInBetween = 8;
    int   ptArray[5];
    SIZE  size;
    RECT  rect;
    HDC   hDC;

    hDC = GetDC(hwndParent);
    GetClientRect(hwndParent, &rect);

    ptArray[4] = rect.right;

    if (GetTextExtentPoint(hDC, "00:00:00", 9, &size))
	ptArray[3] = ptArray[4] - (size.cx) - cSpaceInBetween;
    else
	ptArray[3] = 0;

    if (GetTextExtentPoint(hDC, "Time:", 6, &size))
	ptArray[2] = ptArray[3] - (size.cx) - cSpaceInBetween;
    else
	ptArray[2] = 0;

    if (GetTextExtentPoint(hDC, "654,321", 8, &size))
	ptArray[1] = ptArray[2] - (size.cx) - cSpaceInBetween;
    else
	ptArray[1] = 0;

    if (GetTextExtentPoint(hDC, "Cursor Pos:", 12, &size))
	ptArray[0] = ptArray[1] - (size.cx) - cSpaceInBetween;
    else
	ptArray[0] = 0;

    ReleaseDC(hwndParent, hDC);

    FORWARD_SB_SETPARTS(hWndStatusbar,
			sizeof(ptArray)/sizeof(ptArray[0]),
                        ptArray,
			SendMessage);

    FORWARD_SB_SETTEXT(hWndStatusbar, 0, 0, "Status Bar", SendMessage);
    FORWARD_SB_SETTEXT(hWndStatusbar, 1, 0, "Cursor:", SendMessage);
    FORWARD_SB_SETTEXT(hWndStatusbar, 3, 0, "Time:", SendMessage);
}

//
// Timer Event: set text on status bar
//
static void Main_OnTimer(HWND hwnd, UINT id)
{
    char	szBuf[12];
    SYSTEMTIME	sysTime;

    GetLocalTime(&sysTime);

    wsprintf(szBuf, "%02u:%02u:%02u",
	     sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

    FORWARD_SB_SETTEXT(hWndStatusbar, 4, 0, szBuf, SendMessage);
}

//
// Mouse Event: set text on status bar
//
static void Main_OnMouseMove(HWND hWnd, int x, int y, UINT keyFlags)
{
    char szBuf[20];

    wsprintf(szBuf, "%d,%d", x, y);
    FORWARD_SB_SETTEXT(hWndStatusbar, 2, 0, szBuf, SendMessage);
}

//
// Menu Event: set text on status bar
//
static void Main_OnMenuSelect(HWND hWnd, HMENU hMenu, int item,
                              HMENU hMenuPopup, UINT flags)
{
    static char szBuffer[128];
    static UINT idPopup[] =
    {
	IDS_FILEMENU,
	IDS_EDITMENU,
	IDS_HELPMENU,
    };
    int nStringID;

    szBuffer[0] = 0;				// First reset the buffer

    if (flags == 0xffff && hMenu == NULL)	// Menu has been closed
	nStringID = IDS_DESCRIPTION;

    else if (flags & MFT_SEPARATOR)		// Ignore separators
	nStringID = 0;

    else if (flags & MF_POPUP)			// Popup menu
    {
	if (flags & MF_SYSMENU) 		// System menu
	    nStringID = IDS_SYSMENU;

	else
	    // Get string ID for popup menu from idPopup array.
	    nStringID = ((item < sizeof(idPopup)/sizeof(idPopup[0])) ?
			    idPopup[item] : 0);
    }  // for MF_POPUP

    else					// Must be a command item
	nStringID = item;			// String ID == Command ID

    if (0 != nStringID)
	LoadString(hInst, nStringID, szBuffer, sizeof(szBuffer));

    FORWARD_SB_SETTEXT(hWndStatusbar, 0, 0, szBuffer, SendMessage);
}

//
// Notify Event: display tooltops
//
static LRESULT Main_OnNotify(HWND hWnd, int id, LPNMHDR lpNotification)
{
    static char   szBuffer[64];
    LPTOOLTIPTEXT lpToolTipText;

    lpToolTipText = (LPTOOLTIPTEXT) lpNotification;

    if (lpToolTipText->hdr.code == TTN_NEEDTEXT)
    {
	LoadString(hInst,
		   lpToolTipText->hdr.idFrom,
		   szBuffer,
		   sizeof(szBuffer));

	lpToolTipText->lpszText = szBuffer;
    }
    return 0;
}

//
// Control/Menu Commands: do something
//
static void Main_OnCommand(HWND hWnd, int id, HWND hWndCtl, UINT notify)
{
    switch (id)
    {
	case IDM_FILENEW:
	case IDM_FILEOPEN:
	case IDM_FILESAVE:
	case IDM_FILESAVEAS:
	case IDM_FILECLOSE:
	case IDM_FILEPRINT:
	case IDM_FILEPAGESU:
	case IDM_FILEPRINTSU:

	case IDM_EDITUNDO:
	case IDM_EDITCUT:
	case IDM_EDITCOPY:
	case IDM_EDITPASTE:
	case IDM_EDITCLEAR:
	    MessageBox(hWnd, "menu command", "test", MB_OK);
	    return;

	case IDM_EXIT:
	    DestroyWindow(hWnd);
	    return;

	case IDM_ABOUT:
            MessageBox(hWnd,
                "Minimal Toolbar/Statusbar Application\n\n"
                "Rainer Schnitker",
                "test", MB_OK|MB_ICONINFORMATION);
	    return;
    }
}

#define CTBE_IMAGES	    9
#define CTBE_IMAGEWIDTH     18
#define CTBE_IMAGEHEIGHT    17
#define CTBE_BUTTONWIDTH    0
#define CTBE_BUTTONHEIGHT   0

TBBUTTON tbButton[] =
{
    {0, IDM_FILENEW,    TBSTATE_ENABLED, TBSTYLE_BUTTON, {0,0}, 0, 0},
    {1, IDM_FILEOPEN,   TBSTATE_ENABLED, TBSTYLE_BUTTON, {0,0}, 0, 0},
    {2, IDM_FILESAVE,   TBSTATE_ENABLED, TBSTYLE_BUTTON, {0,0}, 0, 0},
    {6, IDM_FILEPRINT,  TBSTATE_ENABLED, TBSTYLE_BUTTON, {0,0}, 0, 0},
    {0, 0,              TBSTATE_ENABLED, TBSTYLE_SEP,    {0,0}, 0, 0},
    {3, IDM_EDITCUT,    TBSTATE_ENABLED, TBSTYLE_BUTTON, {0,0}, 0, 0},
    {4, IDM_EDITCOPY,   TBSTATE_ENABLED, TBSTYLE_BUTTON, {0,0}, 0, 0},
    {5, IDM_EDITPASTE,  TBSTATE_ENABLED, TBSTYLE_BUTTON, {0,0}, 0, 0},
    {0, 0,              TBSTATE_ENABLED, TBSTYLE_SEP,    {0,0}, 0, 0},
    {7, IDM_ABOUT,      TBSTATE_ENABLED, TBSTYLE_BUTTON, {0,0}, 0, 0},
};

//
// Create Event: init common controls
//
static BOOL Main_OnCreate(HWND hWnd, LPCREATESTRUCT lpCs)
{
    InitCommonControls();

    hWndToolbar = CreateToolbarEx(hWnd,
	WS_CHILD | WS_VISIBLE | TBSTYLE_TOOLTIPS,
	IDC_TOOLBAR,
	CTBE_IMAGES,
	hInst,
	IDB_BMP,
	tbButton,
	sizeof(tbButton)/sizeof(TBBUTTON),
	CTBE_BUTTONWIDTH,
	CTBE_BUTTONHEIGHT,
	CTBE_IMAGEWIDTH,
	CTBE_IMAGEHEIGHT,
	sizeof(TBBUTTON)
    );

    if (!hWndToolbar)
	return FALSE;

    hWndStatusbar = CreateStatusWindow(
	WS_CHILD | WS_VISIBLE | WS_BORDER,
        "Status Bar",
        hWnd,
	IDC_STATUSBAR
    );

    if (hWndStatusbar) {
        InitStatusBar(hWnd);
        SetTimer(hWnd, IDC_TIMER, 1000, NULL);
	return TRUE;
    }
    else
       return FALSE;
}

//
// Size Event: resize also statusbar and toolbar
//
static void Main_OnSize(HWND hWnd, UINT state, int cx, int cy)
{
    FORWARD_WM_SIZE(hWndStatusbar, state, cx, cy, SendMessage);
    FORWARD_WM_SIZE(hWndToolbar,   state, cx, cy, SendMessage);

    InitStatusBar(hWnd);
}

//
// Destroy Event: kill app
//
static void Main_OnDestroy(HWND hWnd)
{
    PostQuitMessage(0);
}

//
// Main Windows Proc
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	    return HANDLE_WM_CREATE(hWnd, wParam, lParam, Main_OnCreate);

	case WM_DESTROY:
	    return HANDLE_WM_DESTROY(hWnd, wParam, lParam, Main_OnDestroy);

	case WM_COMMAND :
	    return HANDLE_WM_COMMAND(hWnd, wParam, lParam, Main_OnCommand);

	case WM_NOTIFY:
	    return HANDLE_WM_NOTIFY(hWnd, wParam, lParam, Main_OnNotify);

	case WM_SIZE:
	    return HANDLE_WM_SIZE(hWnd, wParam, lParam, Main_OnSize);

	case WM_TIMER:
	    return HANDLE_WM_TIMER(hWnd, wParam, lParam, Main_OnTimer);

	case WM_MOUSEMOVE:
	    return HANDLE_WM_MOUSEMOVE(hWnd, wParam, lParam, Main_OnMouseMove);

	case WM_MENUSELECT:
	    return HANDLE_WM_MENUSELECT(hWnd, wParam, lParam, Main_OnMenuSelect);

    } /* switch message */

    return DefWindowProc (hWnd, message, wParam, lParam);
}

//
// register class
//
static BOOL InitApplication(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASSEX	    wc;
    HWND	    hWnd;

    LoadString(hInstance, IDS_APPNAME, szAppName, sizeof(szAppName));
    LoadString(hInstance, IDS_DESCRIPTION, szTitle, sizeof(szTitle));

    hInst = hInstance;

    wc.cbSize	     = sizeof(WNDCLASSEX);
    wc.style	     = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon	     = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
    wc.hCursor	     = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName  = szAppName;
    wc.lpszClassName = szAppName;
    wc.hIconSm	     = LoadImage(hInstance,MAKEINTRESOURCE(IDI_APPICON),
				     IMAGE_ICON, 16, 16, 0);

    if (!RegisterClassEx(&wc)) // bad for NT ?
	if (!RegisterClass((LPWNDCLASS)&wc.style))
		return FALSE;

    hWnd = CreateWindow(
	szAppName,
	szTitle,
	WS_OVERLAPPEDWINDOW,
	CW_USEDEFAULT, 0,
	CW_USEDEFAULT, 0,
	NULL,
	NULL,
	hInstance,
	NULL
    );

    if (!hWnd)
	return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
// Main entry
//
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    MSG msg;
    HANDLE hAccelTable;

    if (!InitApplication(hInstance, nCmdShow))
	return FALSE;

    hAccelTable = LoadAccelerators(hInstance, szAppName);

    while( GetMessage(&msg, NULL, 0, 0))
	if (!TranslateAccelerator (msg.hwnd, hAccelTable, &msg))
	{
	    TranslateMessage(&msg);
	    DispatchMessage(&msg);
	}
    return msg.wParam;
}
