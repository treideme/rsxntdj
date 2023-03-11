/* dibwin.c, module which implements the dibvwr control for displaying
 * window bitmaps.
 *
 * Written by Alfons Hoogervorst, 1995-1997, proteus@worldaccess.nl.        */

/* @DOC
 * @module This file implements the DibWindow Control for displaying bitmaps
 * in a window. Before you use the DibWindow you should register it with
 * one of the register functions. Here some notes:
 *
 *	-	The top-level window containing the dib window should forward
 *		all palette related messages to the dib window
 *
 *	-	If necessary, pass all clipboard related messages to the dib
 *		window.
 *
 *	Future extensions:
 *
 *	-   Handling of the WM_STYLECHANGED message. Currently this message
 *      is only supported by Windows 95 and Windows NT 3.51 with the
 *      W95 extensions.
 *
 *  Known shortcomings:
 *
 * -    Bitmap widths, DWORDs, are converted to ints. You can't load
 *      bitmaps larger than (MAX_INT, MAX_INT).
 *
 * -    HDIBVWR data should be synchronized!
 *
 * -    There's still that tiny scrolling problem. Am too lazy to clean
 *      it up.
 *
 * @index dibwin.c | struct enum func type
 */
#include "compiler.h"
#include <windows.h>
#include "dibwin.h"
#include "dibfunc.h"
#include "winfuncs.h"
#include "windbg.h"

#define WM_SIZEREDRAW			(WM_USER + 0x110)

#define IsPaletteWindow(hWnd) \
	((GetWindowLong((hWnd), GWL_STYLE) & DWS_NOPALETTE) != DWS_NOPALETTE)

#define ShouldHaveScrollBars(hWnd) \
	((GetWindowLong((hWnd), GWL_STYLE) & DWS_NOSCROLLBARS) != DWS_NOSCROLLBARS)

#define ShouldEraseFast(hWnd) \
	((GetWindowLong((hWnd), GWL_STYLE) & DWS_NOFASTERASE) != DWS_NOFASTERASE)

#define ShouldFitToClient(hWnd) \
    ((GetWindowLong((hWnd), GWL_STYLE) & DWS_FITTOCLIENT) == DWS_FITTOCLIENT)


#ifdef __cplusplus
extern "C" {
#endif
static LPBITMAPINFO get_dib_ptr (HWND);
static BOOL set_dib_ptr (HWND, LPBITMAPINFO, BOOL, BOOL);
LRESULT APIENTRY dib_window_proc (HWND, UINT, WPARAM, LPARAM);
static LRESULT dib_window_on_hscroll (HWND, int, unsigned int);
static LRESULT dib_window_on_vscroll (HWND, int, unsigned int);
static LRESULT dib_window_on_sizeredraw (HWND, int, int);
static LRESULT dib_window_on_clear (HWND);
static LRESULT dib_window_on_copy (HWND);
static LRESULT dib_window_on_paste (HWND);
static LRESULT dib_window_on_paint (HWND);
static VOID paint_window (HWND, HDC, LPRECT, HDIBVWR);
static VOID erase_background(HWND, HDC, LPRECT, HDIBVWR);
static LRESULT dib_window_on_allocshareddib (HWND, HDIBVWR);
static LRESULT dib_window_on_freeshareddib (HWND, HDIBVWR);
static HBRUSH get_window_brush (HWND, LPBOOL);
#ifdef __cplusplus
}
#endif

/*-PUB----------------------------------------------------------------------*
    @func register_dib_window register the DibWindow control for use in
    applications. Call this function or <f register_dib_window_ex> before
    you use the DibWindow.
    @rdesc Returns TRUE if succesful, FALSE if an error occurred.

    arguments
        hInstance - Instance of module that wants to register the
            window class
 *--------------------------------------------------------------------------*/
BOOL register_dib_window(
    HINSTANCE hInstance
/* @parm Instance of module that wants to use the DibWindow.                */
)
{
	return register_dib_window_ex(hInstance, 0);
}

/*-PUB----------------------------------------------------------------------*
    @func This is an extended version of <f register_dib_window> and allows
    you to use additional class flags, presumably CS_ALIGNCLIENT.
    @rdesc Returns TRUE if succesful, FALSE if an error occurred.
	    uExtraFlags - Extra window class flags
 *--------------------------------------------------------------------------*/
BOOL register_dib_window_ex(
    HINSTANCE hInstance,
/* @parm instance of module registering the window class.                   */
    UINT uExtraFlags
/* @parm Extra window class flags.                                          */
)
{
	WNDCLASS	wndClass;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | uExtraFlags;
	wndClass.lpfnWndProc = dib_window_proc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = EWB_DIB_WINDOW;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, "DIB_VWR_ICON");
	if ( wndClass.hIcon == 0 )
		wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_CROSS);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = DIB_VWR_CLASSNAME;
	return (BOOL)RegisterClass(&wndClass);
}

/*****************/

static LPBITMAPINFO get_dib_ptr(HWND hwndDib)
{
	HDIBVWR	hdvData = GetDIBData(hwndDib);
	return hdvData != NULL ? hdvData->lpDib : NULL;
}

/*--------------------------------------------------------------------------*
    set_dib_ptr, replaces the DIB data. It does not invalidate the client
    rect. This functions has grown very hard. Most of the functionality
    can be shifted into a Windows 4.0 WM_CHANGESTYLE message handler.
 *--------------------------------------------------------------------------*/
static BOOL set_dib_ptr(HWND hwndDib, LPBITMAPINFO lpNewDib,
	BOOL bDeletePrev, BOOL bCreateCopy)
{
	HDIBVWR			hdvData = GetDIBData(hwndDib);
	LPBITMAPINFO	lpOldDib;
	HPALETTE		hOldPalette;

	if ( hdvData == NULL ) return FALSE;

	/* Store away important data */
	lpOldDib = hdvData->lpDib;
	hOldPalette = hdvData->hPalette;

	/* Try to destroy any shared regions */
	if ( hdvData->atomSharedDib ) {
		hdvData->nSharedDibCnt = 1; 			/* Set reference count to 1 */
		dib_window_on_freeshareddib(hwndDib, hdvData);
	}

	/* Clear all */
	MemSet(hdvData, 0, sizeof(DIBVWR));

	if ( lpNewDib != NULL ) {
		hdvData->lpDib = bCreateCopy ? copy_dib_ptr(lpNewDib) : lpNewDib;
		if ( hdvData->lpDib == NULL ) return FALSE;
		else {
			RECT	rcClient;

			hdvData->lpBits = find_dib_bits(hdvData->lpDib);
			hdvData->nScanlineSize = get_scanline_size(hdvData->lpDib);

			if ( IsPaletteWindow(hwndDib) )
				hdvData->hPalette = create_dib_palette(hdvData->lpDib);

			if ( ShouldHaveScrollBars(hwndDib) ) {
				GetClientRect(hwndDib, &rcClient); /* Get new client rectangle */
				dib_window_on_sizeredraw(hwndDib, rcClient.right, rcClient.bottom);
			}
		}
	} else /* No dib? Set size to zero */
		if ( ShouldHaveScrollBars(hwndDib) )
			if ( GetWindowLong(hwndDib, GWL_STYLE) &
					(WS_VSCROLL | WS_HSCROLL) ) {
				SetScrollRange(hwndDib, SB_HORZ, 0, 0, FALSE);
				SetScrollPos(hwndDib, SB_HORZ, 0, TRUE);
				SetScrollRange(hwndDib, SB_VERT, 0, 0, FALSE);
				SetScrollPos(hwndDib, SB_VERT, 0, TRUE);
			}

	if ( bDeletePrev ) {
		if ( lpOldDib != NULL ) dib_ptr_free(lpOldDib);
		if ( hOldPalette  && hOldPalette != GetStockObject(DEFAULT_PALETTE) )
			DeleteObject(hOldPalette);
	}
	return TRUE;
}

/*--------------------------------------------------------------------------*
    One time initialization / deinitialization.
 *--------------------------------------------------------------------------*/
static HDIBVWR init_dib_vwr(HWND hwndDib)
{
	HDIBVWR	hdvData = HeapAlloc(GetProcessHeap(),
	            HEAP_ZERO_MEMORY, sizeof(DIBVWR));
	if ( hdvData == NULL ) return NULL;
	(VOID)SetDIBData(hwndDib, hdvData);
	if ( !set_dib_ptr(hwndDib, NULL, FALSE, FALSE) ) {
		HeapFree(GetProcessHeap(), 0, hdvData);
		return NULL;
	}
	return hdvData;
}

static VOID done_dib_vwr(HWND hwndDib)
{
	HDIBVWR	hdvData = GetDIBData(hwndDib);

	if ( hdvData != NULL ) {
		set_dib_ptr(hwndDib, NULL, TRUE, FALSE);
		HeapFree(GetProcessHeap(), 0, hdvData);
	}
}

/*****************/

LRESULT APIENTRY dib_window_proc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {

		/* WM_ERASEBKGND - Takes care of proper handling of erase messages */
		case WM_ERASEBKGND:
			return ShouldEraseFast(hWnd) ? 1 :
				DefWindowProc(hWnd, uMsg, wParam, lParam);

		case WM_QUERYNEWPALETTE:
			{
				HPALETTE    hpal = (GetDIBData(hWnd))->hPalette;
				if ( hpal != NULL ) {
					HDC	hdc = GetDC(hWnd);
					SelectPalette(hdc, hpal, FALSE);
					if ( RealizePalette(hdc) )
						InvalidateRect(hWnd, NULL, FALSE);
					ReleaseDC(hWnd, hdc);
				}
			}
			return 0L;

		case WM_PALETTECHANGED:
			if ( (HWND)wParam != hWnd ) {
				HPALETTE    hpal = (GetDIBData(hWnd))->hPalette;
				if ( hpal != NULL ) {
					HDC	hdc = GetDC(hWnd);
					SelectPalette(hdc, hpal, FALSE);
					if ( RealizePalette(hdc) )
						UpdateColors(hdc);
					ReleaseDC(hWnd, hdc);
				}
			}
			return 0L;

		case WM_CUT:
			(VOID)dib_window_on_copy(hWnd);
			/*** Fall through ***/

		case WM_CLEAR:
			return dib_window_on_clear(hWnd);

		case WM_COPY:
			return dib_window_on_copy(hWnd);

		case WM_PASTE:
			return dib_window_on_paste(hWnd);

		case WM_PAINT:
			return dib_window_on_paint(hWnd);

		case WM_CREATE:
			return init_dib_vwr(hWnd) != NULL ? 0 : -1;

		case WM_DESTROY:
			done_dib_vwr(hWnd);
			return 0;

		case WM_HSCROLL:
			return ShouldHaveScrollBars(hWnd) ?
				dib_window_on_hscroll(hWnd, (int)LOWORD(wParam),
					(short int)HIWORD(wParam)) :
				0;

		case WM_VSCROLL:
			return ShouldHaveScrollBars(hWnd) ?
				dib_window_on_vscroll(hWnd, (int)LOWORD(wParam),
					(short int)HIWORD(wParam)) : 0;

		/* The following two messages map to the same handler. */
		case WM_SIZEREDRAW:
		case WM_SIZE:
			return ShouldHaveScrollBars(hWnd) ?
				dib_window_on_sizeredraw(hWnd, (int)LOWORD(lParam),
					(int)HIWORD(lParam)) :
				DefWindowProc(hWnd, uMsg, wParam, lParam);

		case DWM_ALLOCSHAREDDIB:
			return dib_window_on_allocshareddib(hWnd, GetDIBData(hWnd));

		case DWM_FREESHAREDDIB:
			return dib_window_on_freeshareddib(hWnd, GetDIBData(hWnd));

		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

#define SCROLL_LINE_X       2 * GetSystemMetrics(SM_CXBORDER)
#define SCROLL_LINE_Y       2 * GetSystemMetrics(SM_CYBORDER)

/* 0x0a11fab2 / 042197 - Added some simple helper functions to keep source
 * code a little bit more cleaner. Merely intended to help porting to
 * the Win 4.0 scroll info things.                                          */

/* 0x0a11fab2 / 042197 - Calculates the horizontal page scroll unit */
static int CalcHorzPage(HWND hWnd)
{
    RECT Client;
    GetClientRect(hWnd, &Client);
    return Client.right - Client.left;
}

/* 0x0a11fab2 / 042197 - Calculates the vertical page scroll unit */
static int CalcVertPage(HWND hWnd)
{
    RECT Client;
    GetClientRect(hWnd, &Client);
    return Client.bottom - Client.top;
}

static int CalcHorzMax(HWND hWnd, int DibWidth)
{
    return DibWidth - 1;
}

static int CalcVertMax(HWND hWnd, int DibHeight)
{
    return DibHeight - 1;
}

static int CalcHorzStepMax(HWND hWnd, int DibWidth)
{
    return DibWidth - CalcHorzPage(hWnd);
}

static int CalcVertStepMax(HWND hWnd, int DibHeight)
{
    return DibHeight - CalcVertPage(hWnd);
}

/* 0x0a11fab2 / 042197 - Updated to incorporate CalcHorzPage() */
static LRESULT dib_window_on_hscroll(HWND hWnd, int nScrollCode, unsigned int nPos)
{
	HDIBVWR	hdvData = GetDIBData(hWnd);
	int		nXNew;
	int     PageWidth;

	if ( hdvData->lpDib == NULL ) return 0L;

	/* Width of client */
    PageWidth = CalcHorzPage(hWnd);

	switch ( nScrollCode ) {

/* On page ups/page downs we dec/inc with width of client */
		case SB_PAGELEFT:
			nXNew = hdvData->nXPos - PageWidth;
			if ( nXNew < 0 ) nXNew = 0;
			break;

		case SB_PAGERIGHT:
			nXNew = hdvData->nXPos + PageWidth;
			if ( nXNew > hdvData->nXStepMax )
			    nXNew = hdvData->nXStepMax;
            WINVTRACE("SB_PAGERIGHT - max: %d, new: %d, old: %d; bmpw: %d, clntw: %d",
                hdvData->nXMax, nXNew, hdvData->nXPos,
                (int)hdvData->lpDib->bmiHeader.biWidth,
                PageWidth);
			break;

/* On line ups/line downs we dec/inc with a value determined by
 * a system metric constant.                                                */
		case SB_LINELEFT:
			nXNew = hdvData->nXPos - SCROLL_LINE_X;
			if ( nXNew < 0 ) nXNew = 0;
			break;

		case SB_LINERIGHT:
			nXNew = hdvData->nXPos + SCROLL_LINE_X;
			if ( nXNew > hdvData->nXStepMax )
			    nXNew = hdvData->nXStepMax;
			break;

		case SB_THUMBPOSITION:
			nXNew = nPos;
			break;

		case SB_THUMBTRACK:
			nXNew = nPos;
			break;

        case SB_BOTTOM:
            nXNew = hdvData->nXStepMax;
            break;

        case SB_TOP:
            nXNew = 0;
            break;

		default:
		    nXNew = hdvData->nXPos;
		    return 0L;
	}

/* Don't scroll if the same                                                 */
	if ( nXNew != hdvData->nXPos ) {
		int	nXShift = nXNew - hdvData->nXPos;
		hdvData->nXPos = nXNew;
		SetScrollPos(hWnd, SB_HORZ, nXNew, TRUE);
        ScrollWindow(hWnd, -nXShift, 0, NULL, NULL);
		UpdateWindow(hWnd);
	}
	return 0L;
}

/* 0x0a11fab2 / 042197 - Updated to incorporate CalcVertPage()              */
static LRESULT dib_window_on_vscroll(HWND hWnd, int nScrollCode,
	unsigned int nPos)
{
	HDIBVWR	hdvData = GetDIBData(hWnd);
	int		nYNew;
	int     PageHeight;

	if ( hdvData->lpDib == NULL ) return 0L;
    PageHeight = CalcVertPage(hWnd);

	switch ( nScrollCode ) {

		case SB_PAGEUP:
			nYNew = hdvData->nYPos - PageHeight;
			if ( nYNew < 0 ) nYNew = 0;
			break;

		case SB_PAGEDOWN:
			nYNew = hdvData->nYPos + PageHeight;
			if ( nYNew > hdvData->nYStepMax ) nYNew = hdvData->nYStepMax;
			break;

		case SB_LINEUP:
			nYNew = hdvData->nYPos - SCROLL_LINE_Y;
			if ( nYNew < 0 ) nYNew = 0;
			break;

		case SB_LINEDOWN:
			nYNew = hdvData->nYPos + SCROLL_LINE_Y;
			if ( nYNew > hdvData->nYStepMax )
			    nYNew = hdvData->nYPos;
            WINVTRACE("SB_LINEDOWN - New: %d, Old: %d, StepMax: %d, Max: %d",
                nYNew, hdvData->nYPos, hdvData->nYStepMax, hdvData->nYMax);
			break;

		case SB_THUMBPOSITION:
			nYNew = nPos;
			break;

		case SB_THUMBTRACK:
			nYNew = nPos;
			break;

        case SB_TOP:
            nYNew = 0;
            break;

        case SB_BOTTOM:
            nYNew = hdvData->nYStepMax;
            break;

		default:
			nYNew = hdvData->nYPos;
			break;
	}
/* Don't scroll if the same */
	if ( nYNew != hdvData->nYPos ) {
		int	nYShift = nYNew - hdvData->nYPos;
		hdvData->nYPos = nYNew;
		SetScrollPos(hWnd, SB_VERT, nYNew, TRUE);
		ScrollWindow(hWnd, 0, -nYShift, NULL, NULL);
		UpdateWindow(hWnd);
	}
	return 0L;
}

/* 0x0a11fab2 - This one's entirely updated. xxx_sizeredraw is responsible
 * for updating internal scrolling related variables.                       */
static LRESULT dib_window_on_sizeredraw(HWND hWnd, int nClientWidth,
	int nClientHeight)
{
	HDIBVWR	    hdvData = GetDIBData(hWnd);
    SCROLLINFO  sinfo;
    int         nDibHeight, nDibWidth;
    BOOL        ResizeUpdate;

	if ( hdvData->lpDib == NULL ) return 0L;

	ResizeUpdate = FALSE;

	/* Prevent recurring call of this function when changing the scroll bar
	 * info (range)                                                         */

    /* FIXME??? DWORD to int */
    nDibWidth = (int)hdvData->lpDib->bmiHeader.biWidth;
    nDibHeight = (int)hdvData->lpDib->bmiHeader.biHeight;

    /* Maximum scroll value. */
    hdvData->nXMax = max(CalcHorzMax(hWnd, nDibWidth),  0);
    hdvData->nYMax = max(CalcVertMax(hWnd, nDibHeight), 0);

    hdvData->nXStepMax = max(CalcHorzStepMax(hWnd, nDibWidth), 0);
    hdvData->nYStepMax = max(CalcVertStepMax(hWnd, nDibHeight), 0);

    /* DIB fits either vertically / horizontally?
     * FIXME: Currently always updates the window, even if previous
     * height or width was already zero                                     */
    if ( nClientWidth >= nDibWidth ) {
        hdvData->nXPos = 0;
        ResizeUpdate = TRUE;
    }
    if ( nClientHeight >= nDibHeight ) {
        hdvData->nYPos = 0;
        ResizeUpdate = TRUE;
    }

    sinfo.cbSize = sizeof sinfo;
    sinfo.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    sinfo.nPos = hdvData->nYPos;
    sinfo.nMin = 0;
    sinfo.nMax = hdvData->nYMax;
    sinfo.nPage = CalcVertPage(hWnd);
    SetScrollInfo(hWnd, SB_VERT, &sinfo, TRUE);

    sinfo.cbSize = sizeof sinfo;
    sinfo.fMask = SIF_RANGE | SIF_PAGE /*| SIF_POS*/;
    sinfo.nPos = hdvData->nXPos;
    sinfo.nMin = 0;
    sinfo.nMax = hdvData->nXMax;
    sinfo.nPage = CalcHorzPage(hWnd);
    SetScrollInfo(hWnd, SB_HORZ, &sinfo, TRUE);

    if ( ResizeUpdate ) {
        InvalidateRect(hWnd, NULL, TRUE);
        UpdateWindow(hWnd);
    }

	return 0L;
}

static LRESULT dib_window_on_clear(HWND hDibWnd)
{
	set_dib_ptr(hDibWnd, NULL, TRUE, FALSE);
	InvalidateRect(hDibWnd, NULL, TRUE);
	return 0L;
}

static LRESULT dib_window_on_copy(HWND hDibWnd)
{
	HDIBVWR			hdvData;
	HGLOBAL			hdibCopy;

	hdvData = GetDIBData(hDibWnd);
	if ( hdvData != NULL && hdvData->lpDib != NULL ) {
		hdibCopy = copy_dib_handle(hdvData->lpDib);
		/* Set copy of bitmap to clipboard */
		if ( hdibCopy && OpenClipboard(hDibWnd) ) {
			EmptyClipboard();
			if ( SetClipboardData(CF_DIB, hdibCopy) == NULL ) /* Failed */
				GlobalFree(hdibCopy);
			CloseClipboard();
		}
	}
	return 0L;
}

static LRESULT dib_window_on_paste(HWND hDibWnd)
{
	/* Indenting madness. Decreed by Jerry Coffin. */
	if ( IsClipboardFormatAvailable(CF_DIB) )
		if ( OpenClipboard(hDibWnd) ) {
			HGLOBAL	hdibClipboard = (HGLOBAL)GetClipboardData(CF_DIB);
			if ( hdibClipboard != NULL ) {
				LPBITMAPINFO	lpbmi = (LPBITMAPINFO)GlobalLock(hdibClipboard);
				if ( lpbmi != NULL )
					if ( set_dib_ptr(hDibWnd, lpbmi, TRUE, TRUE) ) {
						InvalidateRect(hDibWnd, NULL, FALSE);
						UpdateWindow(hDibWnd);
					}
				GlobalUnlock(hdibClipboard);
			}
			CloseClipboard();
		}
	return 0L;
}

static LRESULT dib_window_on_paint(HWND hWnd)
{
	PAINTSTRUCT		ps;
	HDIBVWR			hdvData = GetDIBData(hWnd);
	BOOL            bFastErase = ShouldEraseFast(hWnd),
	                bHasDib = hdvData != NULL ? hdvData->lpDib != NULL : FALSE;

	BeginPaint(hWnd, &ps);
	if ( bFastErase )
	    erase_background(hWnd, ps.hdc, &ps.rcPaint, hdvData);
	if ( bHasDib ) {
    	/* If there's a palette, use it. hdvData is a pointer to
    	 *	data allocated by the dib window.                               */
    	if ( hdvData->hPalette != NULL ) {
    		SelectPalette(ps.hdc, hdvData->hPalette, FALSE);
    		UnrealizeObject(hdvData->hPalette);
    		RealizePalette(ps.hdc);
    	}
        /* Fit to client? If so, set the correct client width */
        if ( ShouldFitToClient(hWnd) ) {
            RECT    rcClient;
            GetClientRect(hWnd, &rcClient);
            /* Unoptimized when fit to client */
            StretchDIBits(ps.hdc, rcClient.left, rcClient.top,
                rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
                0, 0,
                hdvData->lpDib->bmiHeader.biWidth, hdvData->lpDib->bmiHeader.biHeight,
                hdvData->lpBits,
                hdvData->lpDib,
                DIB_RGB_COLORS,
                SRCCOPY);
        } else paint_window(hWnd, ps.hdc, &ps.rcPaint, hdvData);
    } else /* Nothing to draw */;
	EndPaint(hWnd, &ps);
	return 0L;
}

static VOID erase_background(HWND hWnd, HDC hdcPaint, LPRECT lprcPaint,
	HDIBVWR hdvData)
{
	HBRUSH      hbrBack;
	BOOL		bDeleteBrush;
	HRGN		hrgnDib = 0, hrgnPaint = 0, hrgnCombine;

	hbrBack = get_window_brush(hWnd, &bDeleteBrush);
	hrgnCombine = CreateRectRgnIndirect(lprcPaint);

	/* If there's a dib, we don't want to erase it. Remember: any invalidated
	 * part of the DIB area will be restored by a call to StretchDIBits.
	 * We're optimizing the paint logic of our window, it updates/redraws
	 * in a visually more appealing way (i.e. flicker free).                */
	if ( hdvData->lpDib != NULL ) {
		/* Client region occupied by dib */
		hrgnDib = CreateRectRgn(
			0,
			0,
			max(0, (int)hdvData->lpDib->bmiHeader.biWidth - hdvData->nXPos),
			max(0, (int)hdvData->lpDib->bmiHeader.biHeight - hdvData->nYPos)
		);
		/* Update region */
		hrgnPaint = CreateRectRgnIndirect(lprcPaint);
		/* Subtract hrgnDib from hrgnPaint */
		CombineRgn(hrgnCombine, hrgnPaint, hrgnDib, RGN_DIFF);
	}
	/* Erase background */
	FillRgn(hdcPaint, hrgnCombine, hbrBack);
	/* Remove objects */
	if ( hrgnDib ) DeleteObject(hrgnDib);
	if ( hrgnPaint ) DeleteObject(hrgnPaint);
	if ( hrgnCombine ) DeleteObject(hrgnCombine);
	if ( bDeleteBrush ) DeleteObject(hbrBack);
}

static VOID paint_window(HWND hWnd, HDC hdcPaint, LPRECT lprcPaint,
	HDIBVWR hdvData)
{
	LPBITMAPINFO    lpbmi = hdvData->lpDib;
	int			    height, lines, columns;

	/* Quiet compiler */
	hWnd = hWnd;

	/* Calc. DIB y coordinate */
	height = max(lpbmi->bmiHeader.biHeight - hdvData->nYPos -
		lprcPaint->bottom, 0);

	/* Calculate number of pixel lines to blit */
	lines = lprcPaint->bottom > lpbmi->bmiHeader.biHeight ?
		lpbmi->bmiHeader.biHeight - lprcPaint->top :
		lprcPaint->bottom - lprcPaint->top;

	/* Calculate number of pixel columns to blit */
	columns = lprcPaint->right > lpbmi->bmiHeader.biWidth ?
		lpbmi->bmiHeader.biWidth - lprcPaint->left :
		lprcPaint->right - lprcPaint->left;

	/* Blit dib */
	StretchDIBits(hdcPaint,
		lprcPaint->left, lprcPaint->top,
		columns, lines,
		lprcPaint->left + hdvData->nXPos,
		height,
		columns, lines,
		hdvData->lpBits,
		lpbmi,
		DIB_RGB_COLORS,
		SRCCOPY);
}

/* dib_window_on_allocshareddib - Responsible for a shared DIB allocation
 * action. This part should be synchronized!                                */
static LRESULT dib_window_on_allocshareddib(HWND hWnd, HDIBVWR hdvData)
{
	hWnd = hWnd;

	if ( hdvData == NULL ) return 0;

	if ( !hdvData->atomSharedDib ) {
		char	buf[10];
		if ( 0 == (hdvData->atomSharedDib = create_shared_dib_atom(
				hdvData->lpDib, CreateUniqueName(buf, sizeof buf),
				&(hdvData->lpvdSharedDib))) )
			return 0;
	}

	hdvData->nSharedDibCnt++;
	return (LRESULT)hdvData->atomSharedDib;
}

static LRESULT dib_window_on_freeshareddib(HWND hWnd, HDIBVWR hdvData)
{
	hWnd = hWnd;
	if ( !hdvData || !hdvData->atomSharedDib ) return FALSE;

	if ( !--hdvData->nSharedDibCnt ) {
		destroy_shared_dib_atom(hdvData->atomSharedDib,	hdvData->lpvdSharedDib);
		hdvData->atomSharedDib = 0;
	}
	return TRUE;
}

/*****************/

static HBRUSH get_window_brush(HWND hWnd, LPBOOL bDelete)
{
	HBRUSH	hBrush = (HBRUSH)GetClassLong(hWnd, GCL_HBRBACKGROUND);
	/* Valid brush? */
	if ( GetObject(hBrush, sizeof(LOGBRUSH), NULL) != sizeof(LOGBRUSH) ) {
		LOGBRUSH		lbBrush;
		COLORREF		crColor;
		SetLastError(0);
		crColor = GetSysColor((int)hBrush - 1);
		lbBrush.lbColor = GetLastError() ? GetSysColor(COLOR_WINDOW) : crColor;
		lbBrush.lbStyle = BS_SOLID;
		hBrush = CreateBrushIndirect(&lbBrush);
		*bDelete = TRUE;
	} else
		*bDelete = FALSE;
	return hBrush;
}

/*** Next two functions are a la Windows API definitions ***/

/*-PUB----------------------------------------------------------------------*
    @func SetWindowDIBits sets bits with optional settings. If you specify
    SW_DONTDELETEPREV the original palette and DIB of the DibWindow will
    not be destroyed!
    @rdesc Returns FALSE if an error occurred or TRUE if succesful
 *--------------------------------------------------------------------------*/
BOOL SetWindowDIBits(
    HWND hWndDib,       /* @parm Handle of dib window.                      */
    LPVOID lpdib,
/* @parm New DIB, the value it holds depends on the flags specified in
    the <p uFlags> param.                                                   */
    UINT uFlags
/* @parm Flags for this function. The following values are allowed to be ORed in:
   @flag SWD_HANDLE | The <p lpDib> parameter contains a DIB handle. If not
    specified the function will assume you that the <p lpDib> parameter
    holds a DIB pointer.
   @flag SWD_COPY   | The DibWindow creates a copy of the lpDib bitmap and
    use that copy in its displays. If not used the DibWindow will be the
    owner of the DIB, and will be automatically deleted when the DibWindow
    is destroyed.
   @flag SWD_REDRAW | Forces the DibWindow to redraw.
   @flag SWD_DONTDELETEPREV | DibWindow will not delete previous bitmap data.
    Before you use this flag you should get the old bitmap data with
    <f GetWindowDIBits>.
*/
)
{
	LPBITMAPINFO	lpbmi = uFlags & SWD_HANDLE ?
		copy_handle_dib((HGLOBAL)lpdib, FALSE) : (LPBITMAPINFO)lpdib;

	if ( !lpbmi ) return FALSE;

	if ( !set_dib_ptr(hWndDib, lpbmi, !(uFlags & SWD_DONTDELETEPREV),
				uFlags & SWD_COPY) )
		return FALSE;

	if ( uFlags & SWD_REDRAW ) {
		InvalidateRect(hWndDib, NULL, TRUE);
		UpdateWindow(hWndDib);
	}
	return TRUE;
}

/*-PUB----------------------------------------------------------------------*
    @func GetWindowDIBits gets data from the DibWindow.
    @rdesc Returns a DIB handle or pointer to a DIB. See the <p uFlags>
    parameter how you should interprete the return value.
 *--------------------------------------------------------------------------*/
LPVOID GetWindowDIBits(
    HWND hWndDib,       /* @parm DibWindow to get information from.         */
    UINT uFlags
/* @parm Flags for this function. The flags control how the return value
    should be interpreted. Any of the following may be used (ORed):
   @flag GWD_HANDLE | The return value is a handle. If not specified it
    returns a DIB pointer.
   @flag GWD_COPY   | Requests a copy of the bitmap in the DibWindow. You are
    responsible for cleaning up the returned copy. If you requested a
    GWD_HANDLE, use GlobalFree; else use dib_ptr_free.
*/
)
{
	LPBITMAPINFO	lpbmi = get_dib_ptr(hWndDib);

	if ( !lpbmi ) return NULL;

	lpbmi = uFlags & SWD_HANDLE ? (LPBITMAPINFO)copy_dib_handle(lpbmi) :
		uFlags & SWD_COPY ? copy_dib_ptr(lpbmi) : lpbmi;

	return lpbmi;
}

/*****************/

/*-PUB----------------------------------------------------------------------*
    @func WindowSharedDIBAlloc creates a copy of the current DibWindows'
     bitmap in shared memory. The atom can be used to access the shared bitmap
     in other processes.
    @rdesc Returns an ATOM which can used in IPC. This atom "points" to a
     DIB allocated in shared memory. You can access and copy the DIB's data
     by using the "shared" functions in dibfunc.c. You should call
     WindowSharedDIBFree to free the returned ATOM.
 *--------------------------------------------------------------------------*/
ATOM WindowSharedDIBAlloc(
    HWND hWndDib    /* @parm DibWindow handle.                              */
)
{
	return (ATOM)SendMessage(hWndDib, DWM_ALLOCSHAREDDIB, 0, 0);
}

/*-PUB-----------------------------------------------------------------------*
    @func Frees a atom previously allocated with WindowSharedDIBAlloc.
    @rdesc Returns TRUE if succesful, or FALSE if some error occurred.
 *---------------------------------------------------------------------------*/
BOOL WindowSharedDIBFree(
    HWND hWndDib,   /* @parm Handle of DibWindow.                           */
    ATOM hAtom
/* @parm Atom previously allocated with WindowSharedDibAlloc.               */
)
{
	return (BOOL)SendMessage(hWndDib, DWM_FREESHAREDDIB, 0, 0);
}

/*--------------------------------------------------------------------------*
    @func SetWindowDIBPalette sets a DibWindows' palette.
    @rdesc Returns TRUE if succesful, else it returns FALSE.
 *--------------------------------------------------------------------------*/
BOOL SetWindowDIBPalette(
    HWND hWndDib,
/* @parm DibWindow handle.                                                  */
    HPALETTE hPalette,
/* @parm Palette handle.                                                    */
    UINT uOptions
/* @parm Options for setting the palette, any combination of these flags
    ORed in:
   @flag SWDP_REDRAW | Forces redraw of window.
   @flag SWDP_DELETE | Don't delete previous selected palette.
*/
)
{
	HDIBVWR	hdvData = GetDIBData(hWndDib);
	if ( !hdvData ) return FALSE;
	if ( !(uOptions & SWDP_DONTDELETE) &&
		  hdvData->hPalette &&
		  hdvData->hPalette != GetStockObject(DEFAULT_PALETTE) )
		DeleteObject(hdvData->hPalette);
	hdvData->hPalette = hPalette;
	if ( uOptions & SWDP_REDRAW ) {
		InvalidateRect(hWndDib, NULL, TRUE);
		UpdateWindow(hWndDib);
	}
	return TRUE;
}

/*
 @func This function returns the current palette used by the DibWindow.
 @rdesc The handle of palette used by the DibWindow.
*/
HPALETTE GetWindowDIBPalette (
    HWND hWndDib    /* @parm Handle of DibWindow.                           */
)
{
	HDIBVWR	hdvData = GetDIBData(hWndDib);
	return hdvData ? hdvData->hPalette : NULL;
}

/*
    @func This function sets the bitmap and the palette for the DibWindow.
    @rdesc No return value.
*/
VOID SetBitmapAndPalette(
    HWND hWndDibCtrl,       /* @parm DibWindow handle.                      */
    LPBITMAPINFO lpbmi,     /* @parm Pointer to DIB.                        */
    BOOL bRedraw            /* @parm Forces window to redraw.               */
)
{
    HPALETTE    hPalette;
    /* 24 and 32 bpp DIBs don't have palettes. 2, 4, 8 DIBs have. If the current
       DIB is 24 or 32 bpp, we'll need to fix the palette ourselves. Remember:
       the DIB Viewer Control already creates a palette if the DIB has
       2, 4, 8 bpp, but not for other types. */
    hPalette = dib_num_colors(lpbmi) <= 256 ? NULL :
        create_resource_palette(BITMAP_256COLORS);

    /* Palette and DIBits are set with default flags (0) */
    SetWindowDIBits(hWndDibCtrl, lpbmi, 0);
    if ( hPalette ) SetWindowDIBPalette(hWndDibCtrl, hPalette, 0);

    /* Redraw on request */
    if ( bRedraw ) {
        InvalidateRect(hWndDibCtrl, NULL, TRUE);
        UpdateWindow(hWndDibCtrl);
    }
}

/*** End Of File ***/