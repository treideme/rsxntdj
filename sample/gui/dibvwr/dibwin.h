/* dibwin.h, module which implements the dibvwr control for displaying
 * window bitmaps.
 *
 * Written by Alfons Hoogervorst, 1995-1997, proteus@worldaccess.nl.        */

#ifndef __dibwin_h

/* @DOC */
/* @module dibwin.h | Some definitions for DibWindow control.               */

/*** Clasname of the DIB Viewer Window ***/
#define DIB_VWR_CLASSNAME		"AHII_DIB_VWR_WINDOW"

/*** Styles ***/

/* No palette actions. DIB window does not have a palette nor handles
	palette related messages. Use this style when the DIB window displays
	a bitmap with the system palette. This style should be set before
	you assign a bitmap to the DIB window. */
#define DWS_NOPALETTE		0x0001

/* No scrolling with scroll bars. With this style set the DIB indow does not
	support scrolling with scroll bars. Use this when you need to display
	some autoscrolling dib window. */
#define DWS_NOSCROLLBARS	0x0002

/* Fit to client. Specifies whether DIB should be stretched within the
   client area. Note that "fitting to client area" implies "no scroll bars" */
#define DWS_FITTOCLIENT     0x0004

/* No fast erase. Normally this style should be off. With this style
	set the DIB window will erase invalidated areas with the window's
	class brush, which produces a lot of flicker. If DWS_NOFASTERASE
	is on you should consider subclassing or superclassing the DIB window
	and optimize the erase backgrond logic. */
#define DWS_NOFASTERASE    0x8000


/*****************/

/*** Flags for Set/GetWindowDIBits ***/

/* Set a DIB handle to DIB window. You should discard the handle yourself,
	the DIB window always creates a copy */
#define SWD_HANDLE			(0x0001)

/* Create a copy of the passed bitmap data. You should discard the
	passed bitmap data yourself, because the DIB window creates a copy */
#define SWD_COPY				0x0002

/* Immediately redraws the DIB window after setting the new DIB data */
#define SWD_REDRAW			0x0020

/* Previous bitmap won't be discarded (deleted). Use this only with
	static bitmap data. */
#define SWD_DONTDELETEPREV  0x0040

/*** Flags for SetWindowDIBPalette ***/
#define SWDP_REDRAW			SWD_REDRAW
#define SWDP_DONTDELETE 	SWD_DONTDELETEPREV


/* Returns a handle to the bitmap data. This is not a HBITMAP, rather a
	handle compatible with the CF_DIB clipboard type. If you specify this
	flag, you'll always get a copy of the original data */
#define GWD_HANDLE			SWD_HANDLE

/* Returns a copy of the bitmap data. This flag has only meaning with
	pointers to DIB data */
#define GWD_COPY				SWD_COPY

/*****************/


#if !defined(RC_INVOKED) && !defined(APPSTUDIO_INVOKED)
/*** Access to management structures of the DIB window. Do not use
	  them, unless you know what you're doing. ***/
#pragma pack(1)
typedef struct {
	LPBITMAPINFO	lpDib;              /* DIB data. Alloced with HeapAlloc. */
	LPVOID			lpBits;             /* Offset to bits */
	int				nScanlineSize;		/* Size of a scan line */

	HPALETTE        hPalette;			/* Handle of palette of the DIB */

	ATOM			atomSharedDib;		/* Shared DIB handle */
	int				nSharedDibCnt;		/* How many times shared */
	LPVOID			lpvdSharedDib;

    /* Scroll data */
/* 0x0a11fab2 / 042197 - Added step max for non page scrolls */
	int				nXPos;
	int             nXMax;
	int             nXStepMax;
	int				nYPos;
	int             nYStepMax;
	int             nYMax;

#if WINVER < 0x0400
	BOOL            bInUpdate;
#endif
} DIBVWR;

typedef DIBVWR FAR* HDIBVWR;
#pragma pack()
#endif /* !RC_INVOKED && !APPSTUDIO_INVOKED */


/* The indexes of the window words */
#define EWB_LPDIB					(0)

/* Total nr. of window bytes. We have to include this for those of you
	compiling under Win16 */
#define EWB_DIB_WINDOW 		(sizeof(HDIBVWR))


#if !defined(RC_INVOKED) && !defined(APPSTUDIO_INVOKED)
/* Window data access. Do not use these macros. */
#define GetWindowData(hwnd, type, index) \
	(sizeof(type) == sizeof(WORD) ? \
		(type)GetWindowWord((hwnd), (index)) : \
		(type)GetWindowLong((hwnd), (index)))

# define SetWindowData(hwnd, type, index, data) \
	(sizeof(type) == sizeof(WORD) ? \
		(type)SetWindowWord((hwnd), (index), (WORD)(data)) : \
		(type)SetWindowLong((hwnd), (index), (LONG)(data)))

/* Access to the management structures. Do not use them. */
#define GetDIBData(hwnd) 			GetWindowData(hwnd, HDIBVWR, EWB_LPDIB)
#define SetDIBData(hwnd, data)	SetWindowData(hwnd, HDIBVWR, EWB_LPDIB, data)
#endif /* !RC_INVOKED && !APPSTUDIO_INVOKED */

/* Messages of DIB Window. Use the WindowSharedDIBxxx API. */
#define DWM_ALLOCSHAREDDIB			WM_USER + 0x0001
#define DWM_FREESHAREDDIB			WM_USER + 0x0002

#if !defined(RC_INVOKED) && !defined(APPSTUDIO_INVOKED)
#ifdef __cplusplus
extern "C" {
#endif
BOOL register_dib_window (HINSTANCE);
BOOL register_dib_window_ex(HINSTANCE, UINT);

BOOL SetWindowDIBits (HWND, LPVOID, UINT);
LPVOID GetWindowDIBits (HWND, UINT);

ATOM WindowSharedDIBAlloc(HWND);
BOOL WindowSharedDIBFree (HWND, ATOM);

BOOL SetWindowDIBPalette (HWND, HPALETTE, UINT);
HPALETTE GetWindowDIBPalette (HWND);

VOID SetBitmapAndPalette (HWND, LPBITMAPINFO, BOOL);

#ifdef __cplusplus
}
#endif
#endif /* !RC_INVOKED && !APPSTUDIO_INVOKED */

#endif /* !__dibwin_h */

