/* dibvwr.c - Main program.
 *
 * Written by Alfons Hoogervorst, 1995-1997, proteus@worldaccess.nl.        */
#include "compiler.h"
#include <windows.h>
#include <commdlg.h>
#include "dibopen.h"
#include "windbg.h"
#include "winfuncs.h"

#ifndef MAX_PATH
#define MAX_PATH    (256)
#endif

#include "dibvwr.h"

/* DIB window control + functions */
#include "dibwin.h"

/* High level DIB functions */
#include "dibfunc.h"

/* BMP file functions */
#include "bmpfile.h"

/* About dialog */
#include "dbvabout.h"


/*** Classnames & property strings ***/
#define CLASSNAME    "Ahii_DibWindow"

/* Property for storing previous dimensions of window */
#define PROP_SIZE_X			"prop_Size_X"
#define PROP_SIZE_Y			"prop_Size_Y"

/* Propert storing flags for Edit menu */
#define PROP_EDIT_MENU		"prop_Edit_Menu"

/* Flags for Edit menu */
#define EDIT_COPY				(1)
#define EDIT_CUT				(2)
#define EDIT_PASTE			    (4)
#define EDIT_COPY_CUT		    (EDIT_COPY | EDIT_CUT)

/* Control/child id of DIB Viewer/Control */
#define ID_DIB_VIEWER		100

/*** Prototypes ***/
#ifdef __cplusplus
extern "C" {
#endif
static BOOL register_vwr_window (void);
static LRESULT CALLBACK vwrwndproc (HWND, UINT, WPARAM, LPARAM);
static LRESULT dibwnd_on_create (HWND);
static LRESULT dibwnd_on_command (HWND, HWND, WORD, WORD);
static LRESULT dibwnd_on_menu_command (HWND, WORD);
static VOID dibwnd_on_size (HWND, WORD, int, int);
static VOID validate_edit_menu (HWND, HMENU);
static VOID init_app (VOID);
static VOID menu_fileopen (HWND, HWND);
static VOID menu_filesave (HWND, HWND);
#ifdef __cplusplus
}
#endif

/*** Some statics ***/
static HINSTANCE    _hInst;
static HWND         _hwndMain;

/* Macro */
#define hzalloc(size) \
	HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (size))

/* Global string resource constants */
#define FILTER_MAX_SIZE		(50)
#define NAME_MAX_SIZE		(20)
static LPSTR 		_lpszFileOpenFilter;
static LPSTR        _lpszApplicationName;


int PASCAL WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	MSG 		message;

	_hInst = hInstance;
	hPrevInstance = hPrevInstance;
	lpszCmdLine = lpszCmdLine;

	/* First time initialization */
	if ( !register_dib_window(_hInst) || !register_vwr_window() ) {
	    WINASSERTTEXT(TRUE, "Class error");
		return -1;
    }

	/* Load strings */
	init_app();

    /* Create main window */
	_hwndMain = CreateWindowEx(0, CLASSNAME, _lpszApplicationName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		HWND_DESKTOP,
		0,
		_hInst,
		NULL);

	if ( !_hwndMain ) {
        WINASSERTTEXT(TRUE, "Main window failed");
        return -1;
    }

	/* Windows passes a CmdShow parameter to the program. */
	ShowWindow(_hwndMain, nCmdShow);
	UpdateWindow(_hwndMain);

	/* Run Message Loop */
	while (GetMessage(&message, 0, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.wParam;
}

static BOOL register_vwr_window(void)
{
	WNDCLASS wndclass;
	wndclass.style         = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc   = (WNDPROC)vwrwndproc;
	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hInstance     = _hInst;
	wndclass.hIcon         = LoadIcon(_hInst, MAKEINTRESOURCE(100));
	wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = NULL;
	wndclass.lpszMenuName  = MAKEINTRESOURCE(IDM_MAINMENU);
	wndclass.lpszClassName = CLASSNAME;
	return RegisterClass(&wndclass);
}

/*--------------------------------------------------------------------------*
    vwrwndproc, shows how you should route the relevant messages to the
    dibwin control.
 *--------------------------------------------------------------------------*/
static LRESULT CALLBACK vwrwndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL        fCallDefault = TRUE;
	LRESULT     lResult = 0;		// 0 means handled

	switch (uMsg) {

		/* Pass these messages to DIB control */
		case WM_PALETTECHANGED:
		case WM_QUERYNEWPALETTE:
			SendMessage(GetDlgItem(hWnd, ID_DIB_VIEWER), uMsg, wParam, lParam);
			break;

        /* All clipboard related stuff are routed to the DIB control */
		case WM_CUT:
		case WM_COPY:
		case WM_PASTE:
		case WM_CLEAR:
			lResult = SendMessage(GetDlgItem(hWnd, ID_DIB_VIEWER), uMsg,
				wParam, lParam);
			fCallDefault = FALSE;
			break;

	    /* Because DIB control "claims" the entire client area of the
         * main window, we don't need to erase the background: return
         * a non-zero value (we handled erasing)                            */
		case WM_ERASEBKGND:
			return 1L;

        /* If the user selected the Edit menu, we check if any of the
         * menu items (Copy, Cut, Paste) are valid                          */
		case WM_INITMENUPOPUP:
			/* Not a system menu & popup menu 1 */
			if ( !HIWORD(lParam) && LOWORD(lParam) == 1 ) {
				validate_edit_menu(hWnd, (HMENU)wParam);
			}
			break;

        /* Handling of all menu related stuff */
		case WM_COMMAND:
			return dibwnd_on_command(hWnd, (HWND)lParam,
				LOWORD(wParam), HIWORD(wParam));

        /* If main window resizes we need to resize the DIB control too. */
		case WM_SIZE:
			lResult = DefWindowProc(hWnd, uMsg, wParam, lParam);
			dibwnd_on_size(hWnd, (WORD)wParam, LOWORD(lParam),	HIWORD(lParam));
			fCallDefault = FALSE;
			break;

		case WM_CREATE:
			return dibwnd_on_create(hWnd);

		case WM_DESTROY:
		    RemoveProp(hWnd, PROP_SIZE_X);
		    RemoveProp(hWnd, PROP_SIZE_Y);
			RemoveProp(hWnd, PROP_EDIT_MENU);
			PostQuitMessage(0); /* This is the main window */
			fCallDefault = FALSE;
			break;
	}

	if ( fCallDefault ) lResult = DefWindowProc(hWnd, uMsg, wParam, lParam);
	return lResult;
}

static LRESULT dibwnd_on_create(HWND hwndDib)
{
	/* We want a DIB_VWR with all default styles on, so we don't
	 * specify any of the DWS_xxx styles                                    */
	HWND	hwndChild = CreateWindowEx(0, DIB_VWR_CLASSNAME,
	            DIB_VWR_CLASSNAME, WS_CHILD | WS_VISIBLE,
				0, 0, 0, 0, hwndDib, (HMENU)ID_DIB_VIEWER, _hInst, NULL);
	if ( hwndChild == NULL )
	    return -1L;
	else {
		/*** Set menu status OK ***/
		SetProp(hwndDib, PROP_EDIT_MENU, (HANDLE)0xFFFF);
		validate_edit_menu(hwndDib, GetSubMenu(GetMenu(hwndDib), 1));
	}
	return 0L;
}

/******************/

static LRESULT dibwnd_on_command(HWND hwndDib, HWND hwndChild,
	WORD wId, WORD wNotification)
{
	if ( hwndChild == 0 && wNotification == 0 )
		return dibwnd_on_menu_command(hwndDib, wId);
	return DefWindowProc(hwndDib, WM_COMMAND, MAKEWPARAM(wId, wNotification),
		(LPARAM)hwndChild);
}

LRESULT dibwnd_on_menu_command(HWND hwndDib, WORD wMenuCmd)
{
	switch ( wMenuCmd ) {

		case CM_FILENEW:
			/* Forward a clear message to self */
			SendMessage(hwndDib, WM_CLEAR, 0, 0);
			break;

		case CM_FILEOPEN:
			menu_fileopen(hwndDib, GetDlgItem(hwndDib, ID_DIB_VIEWER));
			break;

		case CM_FILESAVE:
		case CM_FILESAVEAS:
		    menu_filesave(hwndDib, GetDlgItem(hwndDib, ID_DIB_VIEWER));
			break;

		case CM_FILEEXIT:
			PostMessage(hwndDib, WM_CLOSE, 0, 0);
			break;

		case CM_EDITPASTE:
			SendMessage(hwndDib, WM_PASTE, 0, 0);
			break;

		case CM_EDITCOPY:
			SendMessage(hwndDib, WM_COPY, 0, 0);
			break;

		case CM_EDITCUT:
			SendMessage(hwndDib, WM_CUT, 0, 0);
			break;

		case CM_HELPABOUT:
			about_dialog(hwndDib);
			break;
	}
	return 0;
}

/*****************/

/*--------------------------------------------------------------------------*
    Resize DIB window control
 *--------------------------------------------------------------------------*/
static VOID dibwnd_on_size(HWND hwndDib, WORD wType, int nNewX, int nNewY)
{
	int 	nSizeX = (int)GetProp(hwndDib, PROP_SIZE_X),
			nSizeY = (int)GetProp(hwndDib, PROP_SIZE_Y);

	if ( (wType != SIZE_MINIMIZED) && (nSizeX != nNewX || nSizeY != nNewY) ) {

		/*** Change size of child window ***/
		if ( nNewX != nSizeX || nNewY != nSizeY ) {
			SetWindowPos(GetDlgItem(hwndDib, ID_DIB_VIEWER), 0, 0, 0,
				nNewX, nNewY, SWP_NOMOVE | SWP_NOZORDER |
					(nNewX == nSizeX && nNewY == nSizeY ? SWP_NOSIZE : 0));

			/* Store new dimensions */
			SetProp(hwndDib, PROP_SIZE_X, (HANDLE)nNewX);
			SetProp(hwndDib, PROP_SIZE_Y, (HANDLE)nNewY);
		}
	}
}

/*****************/

/*--------------------------------------------------------------------------*
    validate_edit_menu, validates the edit menu items. The current menu
    status is stored in a window property.
 *--------------------------------------------------------------------------*/
static VOID validate_edit_menu(HWND hwndDib, HMENU hmenuEdit)
{
	int 	nPrevState = (int)GetProp(hwndDib, PROP_EDIT_MENU), nNewState;

    /* Precalculate new state */
	nNewState = ( GetWindowDIBits(GetDlgItem(hwndDib,
		ID_DIB_VIEWER), 0) != NULL ? EDIT_COPY_CUT : 0 ) |
		( IsClipboardFormatAvailable(CF_DIB) ? EDIT_PASTE : 0 );

	if ( nNewState != nPrevState ) {

		/* EDIT_COPY_ CUT state changed? */
		if ( (nPrevState & EDIT_COPY_CUT) ^ (nNewState & EDIT_COPY_CUT) ) {
			EnableMenuItem(hmenuEdit, CM_EDITCOPY,
				MF_BYCOMMAND | (nNewState & EDIT_COPY_CUT ? MF_ENABLED : MF_GRAYED));
			EnableMenuItem(hmenuEdit, CM_EDITCUT,
				MF_BYCOMMAND | (nNewState & EDIT_COPY_CUT ? MF_ENABLED : MF_GRAYED));
		}

		/* EDIT_PASTE state changed? */
		if ( (nPrevState & EDIT_PASTE) ^ (nNewState & EDIT_PASTE) )
			EnableMenuItem(hmenuEdit, CM_EDITPASTE,
				MF_BYCOMMAND | (nNewState & EDIT_PASTE ? MF_ENABLED : MF_GRAYED));
		SetProp(hwndDib, PROP_EDIT_MENU, (HANDLE)nNewState);
	}
}

/*****************/

static VOID replace_pipe_symbols(char* str)
{
	while ( *str ) {
	    if ( *str == '|' )
	        *str = 0;
        str++;
    }
}

static VOID init_app(VOID)
{
	_lpszFileOpenFilter = hzalloc(FILTER_MAX_SIZE);
	if ( LoadString(_hInst, IDS_FILEOPENFILTER,
			_lpszFileOpenFilter, FILTER_MAX_SIZE) )
		replace_pipe_symbols(_lpszFileOpenFilter);
	_lpszApplicationName = hzalloc(NAME_MAX_SIZE);
	if ( LoadString(_hInst, IDS_APPLICATIONNAME,
			_lpszApplicationName, NAME_MAX_SIZE) )
		replace_pipe_symbols(_lpszApplicationName);
}

int percent_count(LPCSTR lpszText)
{
	int	nCount = 0;
	for ( ; *lpszText; lpszText++ )
		if ( *lpszText == '%' )
			if ( *(lpszText + 1) == '%' ) lpszText += 1;
			else if ( IsCharAlpha(*(lpszText + 1)) ) nCount++;
	return nCount;
}

int message_str(HWND hParent, int nStrID, LPCSTR lpszCaption, UINT uMBStyle, ...)
{
	char  szStrText[100];
	char  szResult[300];
	szStrText[0] = szResult[0] = 0;
	if ( !LoadString(GetModuleHandle(NULL), nStrID, szStrText,
		sizeof(szStrText)) ) return -1;
	if ( szStrText[0] && percent_count(szStrText) ) {
		LPSTR lpArgs = ((LPSTR) &uMBStyle) + sizeof uMBStyle;
		wvsprintf(szResult, szStrText, lpArgs);
	} else lstrcpy(szResult, szStrText);
	return MessageBox(hParent, szResult, lpszCaption, uMBStyle);
}

/****************/

static VOID menu_fileopen(HWND hWndVwr, HWND hWndDib)
{
    BOOL            bPressedOK;
	LPBITMAPINFO    lpbmi;
	char            buf[MAX_PATH];
	static BOOL     bExplorer;

    /* Twiggle between different dialog box styles */
    bPressedOK = get_open_dib_file(hWndVwr, _lpszFileOpenFilter,
        buf, sizeof buf, &lpbmi, (bExplorer ^= 1));

    /* Pressed OK, not a valid DIB. */
    if ( bPressedOK && lpbmi == NULL ) {
    	message_str(hWndDib, IDS_ERR_LOADFILE,
    		_lpszApplicationName, MB_OK | MB_ICONINFORMATION, buf);
    	WINASSERTTEXT(TRUE, "BMP file load");
    	return;
    }

    /* I don't want to be bothered which palette to use, let the DIB Viewer
     * handle the details.                                                  */
    if ( bPressedOK && lpbmi ) SetBitmapAndPalette(hWndDib, lpbmi, TRUE);
}

static VOID menu_filesave(HWND hWndVwr, HWND hWndDibCtrl)
{
    LPBITMAPINFO    lpbmi = GetWindowDIBits(hWndDibCtrl, 0);

    if ( lpbmi ) {
        OPENFILENAME    ofn;
        char            buf[MAX_PATH];

        /* Initialize */
        MemSet(&ofn, 0, sizeof ofn);
        MemSet(buf, 0, sizeof buf);

        ofn.lStructSize = sizeof ofn;
        ofn.hwndOwner = hWndVwr;
        ofn.hInstance = (HINSTANCE)GetModuleHandle(NULL);
        if ( _lpszFileOpenFilter ) ofn.lpstrFilter = _lpszFileOpenFilter;
        ofn.lpstrFile = buf;
        ofn.nMaxFile = sizeof buf;
        ofn.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_EXPLORER;
        ofn.lpstrDefExt = "bmp";

        if ( GetSaveFileName(&ofn) && ERROR_SUCCESS != write_bmp_file_win32_ptr(buf, lpbmi) ) {
            message_str(hWndVwr, IDS_ERR_WRITEFILE,
                _lpszApplicationName, MB_OK | MB_ICONINFORMATION, buf);
            WINASSERTTEXT(TRUE, "BMP file write");
            return;
        }
    } else WINASSERTTEXT(TRUE, "No DIB avail.");
}

/*** End of File ***/