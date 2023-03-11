/* dbvabout.c - DibVwr About Dialog with an added surprise
 *
 * Written by Alfons Hoogervorst, 1995-1997, proteus@worldaccess.nl.        */

/* This module directly accesses the HDIBVWR data managed by the
 * DibWindow. At the time of writing the dibwin.c interface functions
 * we're not completed entirely. <g> See the do_scroll window for
 * examples of directly accessing the HDIBVWR data of a DIB window.        */

/*
 * @DOC
 * @module dbvabout.c |
 * This module is only interesting because it directly accesses the
 * data stored in the DibWindow. This data is manipulated to perform
 * the scrolling effect in the about dialog.
 * @index dvabout.c | func
 */

#include "compiler.h"
#include <windows.h>
#include "dbvabout.h"
#include "dibwin.h"
#include "dibfunc.h"
#include "windbg.h"
#include "winfuncs.h"

#define ID_TIMER			(667)
#define TIME_OUT			(75)

/*** Under Win32 HMODULE == HINSTANCE ***/
#define get_current_hinstance()	\
	((HINSTANCE)GetModuleHandle(NULL))

#define IsScrolling(hDlg) \
    GetWindowLong((hDlg), DWL_USER)
#define SetScrolling(hDlg) \
    SetWindowLong((hDlg), DWL_USER, 1)

#define PROP_SCROLL_HWND    "prop_Scroll_Hwnd"
#define SetScrollWindow(hDlg, hWnd) \
    SetProp(hDlg, PROP_SCROLL_HWND, (HANDLE)(hWnd))
#define GetScrollWindow(hDlg) (HWND)GetProp(hDlg, PROP_SCROLL_HWND)

#ifdef __cplusplus
extern "C" {
#endif
BOOL CALLBACK dbv_about_dlgproc(HWND, UINT, WPARAM, LPARAM);
static BOOL dbv_about_oninitdialog (HWND);
static BOOL dbv_about_onshowwindow (HWND, BOOL);
static BOOL dbv_about_ontimer (HWND);
static BOOL dbv_about_oncommand (HWND, UINT, UINT, HWND);
static VOID do_scroll (HWND, HDIBVWR);
#ifdef __cplusplus
}
#endif

/*****************/

static int _nMovX;
static int _nMovY;
static int _nWidth;
static int _nHeight;


/*** about_dialog ***
	Just a wrapper.
*********************/
VOID about_dialog(HWND hWndParent)
{
	DialogBox(get_current_hinstance(), MAKEINTRESOURCE(100), hWndParent,
		dbv_about_dlgproc);
}

/*****************/

BOOL CALLBACK dbv_about_dlgproc(HWND hWndDlg, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	switch ( uMsg ) {

		/*** Pass these messages to DIB_VIEWER control ***/
		case WM_PALETTECHANGED:
		case WM_QUERYNEWPALETTE:
			{
				HWND	hWndDib = GetDlgItem(hWndDlg, 100);
				if ( hWndDib )	SendMessage(hWndDib, uMsg, wParam, lParam);
			}
			return TRUE;

		case WM_TIMER:
			return dbv_about_ontimer(hWndDlg);

		case WM_SHOWWINDOW:
			return dbv_about_onshowwindow(hWndDlg, (BOOL)wParam);

		case WM_COMMAND:
			return dbv_about_oncommand(hWndDlg, (UINT)LOWORD(wParam),
				(UINT)HIWORD(wParam), (HWND)lParam);

		case WM_INITDIALOG:
			return dbv_about_oninitdialog(hWndDlg);

	}
	return FALSE;
}

/*** dbv_about_oninitdialog ***
	Initialize dialog. A little bit tricky. Just assume this function
	moves some controls around. Take a look at the About Dialog's
	resource template.
*******************************/
static BOOL dbv_about_oninitdialog(HWND hWndDlg)
{
	RECT			rcWindow, rcScroller;
	LPBITMAPINFO	lpbmiRes, lpbmiWnd;
	HGLOBAL			hRes;
	HWND            hWndDibCtrl;

	GetWindowRect(hWndDlg, &rcWindow);

	/* Control with item nr. 999 is a place holder for our scroller */
	GetWindowRect(GetDlgItem(hWndDlg, 999), &rcScroller);

	/* We got size. Check if our bitmap is available. */
	lpbmiRes = (LPBITMAPINFO)LockResource(hRes =
		LoadResource(get_current_hinstance(), FindResource(get_current_hinstance(),
		MAKEINTRESOURCE(999), RT_BITMAP)));

    WINASSERTTEXT(lpbmiRes == NULL, "No #999");

	/* Okay, try to create bitmap & scroller */
	if ( lpbmiRes ) {
		if ( NULL != (lpbmiWnd = copy_dib_ptr(lpbmiRes)) &&
			  NULL != (hWndDibCtrl = CreateWindowEx(0, DIB_VWR_CLASSNAME,
			        "DIB Scroller",
					WS_CHILD | WS_VISIBLE | DWS_NOSCROLLBARS,
					0, 0, 0, 0,
					hWndDlg, (HMENU)(int)100,
					get_current_hinstance(),
					NULL)) ) {

            /* Do some asserts */
            WINASSERTTEXT(GetParent(hWndDibCtrl) != hWndDlg ||
                hWndDibCtrl != GetDlgItem(hWndDlg, 100), "resource error");

			/* Now we need to swap OK button and scroller positions */
			MapWindowPoints(HWND_DESKTOP, hWndDlg, (LPPOINT)&rcScroller,
				sizeof(RECT) / sizeof(POINT));
			GetWindowRect(GetDlgItem(hWndDlg, IDOK), &rcWindow);
			MapWindowPoints(HWND_DESKTOP, hWndDlg, (LPPOINT)&rcWindow,
				sizeof(RECT) / sizeof(POINT));

			/* Move frame & resize frame */
			SetWindowPos(GetDlgItem(hWndDlg, 999), 0,
				rcScroller.left, rcWindow.top,
				rcScroller.right - rcScroller.left,
				rcScroller.bottom - rcScroller.top + /* height of button */
					rcWindow.bottom - rcWindow.top,
				SWP_NOREDRAW | SWP_NOZORDER);

			/* Move OK button */
			SetWindowPos(GetDlgItem(hWndDlg, IDOK), 0,
				rcWindow.left, rcScroller.bottom, 0, 0,
				SWP_NOREDRAW | SWP_NOZORDER | SWP_NOSIZE);

			/* Adjust rectangle: actual rectangle of frame in dialog */
			GetWindowRect(GetDlgItem(hWndDlg, 999), &rcScroller);
			MapWindowPoints(HWND_DESKTOP, hWndDlg, (LPPOINT)&rcScroller,
				sizeof(RECT) / sizeof(POINT));

			/* Set rectangle for scroller. Scroller should fit in frame */
			#define m_f		(3)
			InflateRect(&rcScroller, m_f * -GetSystemMetrics(SM_CXBORDER),
				m_f * -GetSystemMetrics(SM_CYBORDER));
			#undef m_f

			/* Move & resize scroller */
			SetWindowPos(hWndDibCtrl, 0,
				rcScroller.left, rcScroller.top,
				rcScroller.right - rcScroller.left,
				rcScroller.bottom - rcScroller.top,
				SWP_NOREDRAW | SWP_NOZORDER);

			/* Set window DIB bits */
			SetBitmapAndPalette(hWndDibCtrl, lpbmiWnd, FALSE);
			SetScrollWindow(hWndDlg, hWndDibCtrl);

			/* Set scroll variables */
			_nWidth  = lpbmiWnd->bmiHeader.biWidth - (rcScroller.right - rcScroller.left);
			_nHeight = lpbmiWnd->bmiHeader.biHeight - (rcScroller.bottom - rcScroller.top);
			_nMovX = _nMovY = -1;

			/* Initialize Snippets rng */
			SLongRand(GetTickCount());

			return TRUE;
		}

		/* If here, error: free resources */
		if ( lpbmiWnd ) dib_ptr_free(lpbmiWnd);
		GlobalUnlock(hRes);
	}

	if ( hRes ) FreeResource(hRes);

	/* We failed! Let's put the scroller place holder out of sight of user. */
	SetWindowPos(hWndDlg, 0, 0, 0, rcWindow.right - rcWindow.left,
		rcScroller.top - rcWindow.top, SWP_NOZORDER | SWP_NOREDRAW | SWP_NOMOVE);

	return TRUE;
}

/*** dbv_about_onshowwindow ***
	Set a timer if this window becomes visible.
*******************************/
static BOOL dbv_about_onshowwindow(HWND hWndDlg, BOOL bShow)
{
	/* We're using the user data long as a init. flag */
	if ( !IsScrolling(hWndDlg) && bShow ) {
		SetScrolling(hWndDlg);

		/* Setup a timer */
		if ( GetScrollWindow(hWndDlg) != NULL )
		    if ( !SetTimer(hWndDlg, ID_TIMER, TIME_OUT, NULL) )
		        WINASSERTTEXT(TRUE, "Timer failure");
	}
	return FALSE;
}

/*** dbv_about_on_timer ***
	Again, a wrapper.
***************************/
static BOOL dbv_about_ontimer(HWND hWndDlg)
{
	HWND	hWndDib = GetScrollWindow(hWndDlg);
	do_scroll(hWndDib, GetDIBData(hWndDib));
	return TRUE;
}

/*** dbv_about_oncommand ***
	Handler for WM_COMMAND messages. This one responds to IDOK/IDCANCEL
	only.
****************************/
static BOOL dbv_about_oncommand(HWND hWndDlg, UINT uItemId,
	UINT uNotification, HWND hWndControl)
{
	/* Unreferenced parameters */
	uNotification = uNotification;
	hWndControl = hWndControl;

	if ( uItemId == IDOK || uItemId == IDCANCEL ) {
		KillTimer(hWndDlg, ID_TIMER);
		RemoveProp(hWndDlg, PROP_SCROLL_HWND);
		EndDialog(hWndDlg, uItemId);
		return TRUE;
	}
	return FALSE;
}

/*****************/

static VOID do_scroll(HWND hWndDib, HDIBVWR hdvData)
{
	#define min_step_x		(2)
	#define min_step_y		(2)

	#define max_step_x		(4 * GetSystemMetrics(SM_CXBORDER))
	#define max_step_y		(4 * GetSystemMetrics(SM_CYBORDER))

	#define lboundx			(0)
	#define lboundy			(0)

	#define hboundx      	(_nWidth - 1)
	#define hboundy      	(_nHeight - 1)

	if ( hdvData == NULL ) return;
	else {
		int	nX = hdvData->nXPos, nY = hdvData->nYPos;
#ifdef __SCROLL
		HDC		hdcDib;
		HBITMAP  hbmpDib;
#endif

		nX += _nMovX; nY += _nMovY;

		/* Check if we hit bounds */
		if ( nX < lboundx ) {
			_nMovX = (int)LongRand() % max_step_x + min_step_x;
			nX = lboundx + _nMovX;
		}

		if ( nY < lboundy ) {
			_nMovY = (int)LongRand() % max_step_y + min_step_y;
			nY = lboundy + _nMovY;
		}

		if ( nX > hboundx ) {
			_nMovX = -1 * ((int)LongRand() % max_step_x + min_step_x);
			nX = hboundx + _nMovX;
		}

		if ( nY > hboundy ) {
			_nMovY = -1 * ((int)LongRand() % max_step_y + min_step_y);
			nY = hboundy + _nMovY;
		}

#ifdef __SCROLL
		nDX = nX - hdvData->nXPos;
		nDY = nY - hdvData->nYPos;
#endif
		/* Directly set the origin in DIB window */
		hdvData->nXPos = nX;
		hdvData->nYPos = nY;

#ifndef __SCROLL
		/* Full redraw might be faster */
		InvalidateRect(hWndDib, NULL, FALSE);
		UpdateWindow(hWndDib);
#else
		GetClientRect(hWndDib, &rcClient);
		rcScroll = rcClient;
		OffsetRect(&rcClient, -nDX, -nDY);

		hrgnResult = CreateRectRgn(1, 1, 1, 1);
		hrgnClient = CreateRectRgnIndirect(&rcClient);
		hrgnScroll = CreateRectRgnIndirect(&rcScroll);

		CombineRgn(hrgnResult, hrgnClient, hrgnScroll, RGN_DIFF);
		DeleteObject(hrgnClient);
		DeleteObject(hrgnScroll);
		ScrollWindowEx(hWndDib, -nDX, -nDY, NULL, NULL, NULL, NULL,
			SW_INVALIDATE);
		DeleteObject(hrgnResult);
#endif
	}
}

/* End of File */
