/* dibopen.c - A common dialog for opening and previewing DIB files.
 *
 * Written by Alfons Hoogervorst, 1995-1997, proteus@worldaccess.nl.        */

/* @DOC
 * @module dibopen.c | dibopen.c implements a common dialog for loading
 *  and previewing bitmap files. This file requires the dibopen.rc
 *  resource script.
 * @index dibopen.c  | func struct                                          */

/*
    Change log:

	Nov, 1995
	    The dib open dialog has a preview capability. The preview box is just
	    a dib viewer control managed by a hooked get open file name common
	    dialog.

    Dec, 1995
        Added old-style common dialog support.
	    If you get "stc1/lst1 undefined" errors while compiling, check the
	    identifiers in Windows header <dlgs.h>.

    April, 1997
        Modified get_sel_file_path(). See several articles on this topic
        in comp.os.ms-windows.programmer.misc,
        "reading filename within OpenFile dlg". Look for the special
        comment markers iCDLGTOOL! for necessary additions.
        Also made this Win 4.0 only (using the xxxScrollInfo API).
*/

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include "compiler.h"
#include <string.h>
#include <windows.h>
#include <commdlg.h>
#include <dlgs.h>

#include "winfuncs.h"
#include "windbg.h"

/* Functions for reading bmp file */
#include "bmpfile.h"

/* Interface functions for DIB Window/Control */
#include "dibwin.h"

/* Functions for manipulating and querying DIBs */
#include "dibfunc.h"

/* Resource identifiers of DIB OPEN dialog */
#include "dibopen.rh"

/* Include file for this module */
#include "dibopen.h"

#define CDLGTOOL
#ifdef CDLGTOOL
/* iCDLGTOOL! Additional tools for common dialogs, based on the
 * articles published in comp.os.ms-windows.programmer.misc.                */
#include "cdlgtool.h"
#endif

/* Inactivate unuseable defines */
#ifndef __GNUC__
#	if(WINVER < 0x0400)
#		define WM_NOTIFY           WM_NULL
#		define OFN_EXPLORER        0
#		define WS_EX_STATICEDGE    0
#	endif
#endif

/* Maximum number of chars of a full file name */
#ifndef MAX_PATH
#   define MAX_PATH    256
#endif

/* Properties */
#define PROP_PREVIEW_HEIGHT "propMaxHeight"
#define PROP_PREVIEW_WIDTH  "propMaxWidth"
#define PROP_PREVIEW_MODE   "propPreviewMode"
#define PROP_LAST_SELECTED_DIR  "propLastSelectedDir"
#define PROP_LAST_SELECTED_FILE "propLastSelectedFile"

/* added by Johan Venter for headers (jventer@writeme.com) */
#ifndef SNDMSG
#ifdef __cplusplus
#define SNDMSG ::SendMessage
#else
#define SNDMSG SendMessage
#endif
#endif // ifndef SNDMSG

/*
    @struct GODF | Information to pass to open dib dialog. Currently DIBOPEN.C
    doesn't do much with this structure. Merely intended for future extension.
*/
typedef struct {
    LPBITMAPINFO    lpbmi;              /* @field Pointer to the DIB of the
                                            selected bitmap file.           */
    LPSTR           lpstrFile;          /* @field Selected file's name.     */
    int             nFileType;          /* @field Selected file type.       */
    BOOL            bPreview;           /* @field Preview mode.             */
    BOOL            bExplorerDialog;    /* @field Explored dialog.          */
} GODF, FAR* LPGODF;

/*** Linked list that stores the controls texts for the old style common
     dialogs ***/
typedef struct tagCONTROLS FAR* PCONTROLS;
typedef struct tagCONTROLS {
    LPSTR     pControlText;
    PCONTROLS pControlNext;
} CONTROLS;

/* We use the dialog user long for storing a pointer to GODF data */
#define PutDlgPtr(hDlg, ptr) \
    SetWindowLong((hDlg), DWL_USER, (LONG)(ptr))
#define GetDlgPtr(hDlg) \
    (LPGODF)GetWindowLong((hDlg), DWL_USER)

/* Preview mode macros */
#define InPreviewMode(hDlg) \
    (GetProp((hDlg), PROP_PREVIEW_MODE) != 0)
#define SetPreviewMode(hDlg, mode) \
    SetProp((hDlg), PROP_PREVIEW_MODE, (HANDLE)(mode))

/* Dialog type macros */
#define IsExplorerDialog(hDlg) \
    (GetDlgPtr(hDlg))->bExplorerDialog

#define GetSelFilePath(hDlg, buf, bufsize) \
    (IsExplorerDialog((hDlg)) ? \
    CommDlg_OpenSave_GetFilePath(GetParent((hDlg)), (buf), (bufsize)) : \
    get_sel_file_path((hDlg), (buf), (bufsize)))


/*** Prototypes ***
    Not necessary in modern compilers.
*******************/
#ifdef __cplusplus
extern "C" {
#endif
static BOOL CALLBACK hookproc_open_dib (HWND, UINT, WPARAM, LPARAM);
static BOOL hookproc_on_initdialog (HWND, LPARAM);
static BOOL hookproc_on_command(HWND, WORD, WORD, HWND);
static BOOL hookproc_on_selchange (HWND);
static BOOL hookproc_on_fileok (HWND);

static BOOL command_previewcheck (HWND);
static LPBITMAPINFO verify_bmp_file (LPCSTR);
static VOID set_new_stats (HWND, LONG, LONG, LONG, LONG);
static VOID update_statistics (HWND, LPBITMAPINFO);
static VOID twiggle_preview_controls (HWND, BOOL);
static VOID update_preview_window (HWND, LPBITMAPINFO);
static VOID resize_preview_window (HWND, LONG, LONG);

static int get_sel_file_path (HWND, LPSTR, int);
static void build_control_chain (PCONTROLS*, HWND);
static void dispose_control_chain (PCONTROLS);
static void set_control_chain_text (PCONTROLS, HWND);
static void get_local_OFN_texts (void);
#ifdef __cplusplus
}
#endif


/*** _pFirstText ***
    This one time allocated static is the head of a linked list of all
    window texts in the File Open Common dialog of the current
    Windows locale.
********************/
static PCONTROLS   _pFirstText;
#ifndef CDLGTOOL
static UINT        WM_LBSELCHANGE;
#endif

/*-PUB----------------------------------------------------------------------*
    @func _get_open_dib_file, opens a DIB file using the open file common
    dialog. This dialog has a preview window and additionally displays
    statistics. This function works with the explorer too. Is actually the
    engine for get_open_dib_file. _get_open_dib_file (and get_open_dib_file)
    only support Windows DIBs. If you want to use it for another file format
    make this function call some function when the preview window detects
    an error.
    @rdesc Returns TRUE if successful, or FALSE if some error occurred.
 *--------------------------------------------------------------------------*/
BOOL _get_open_dib_file(
    HWND hWndParent,            /* @parm Parent for the dialog.             */
    LPCSTR lpszFileOpenFilter,
/* @parm Filter with file types and extensions. May be NULL. A filter
    typically looks like this:
    "Windows bitmaps\0*.bmp;*.dib\0"
    "Windows bitmaps\0*.dib\0GIF files\0*.gif\0"
*/
    int* lpnFileType,
/* @parm Pointer to an int receiving the selected file's type.              */
    LPSTR lpszBufName,
/* @parm Pointer to the buffer receiving the name of the selected DIB file. */
    int nSize,
/* @parm Numbers of characters that fit in <p lpszBufName>. Should include
 * the 0 byte.                                                              */
    LPBITMAPINFO* lpbmi,
/* @parm Pointer to DIB pointer. Receives the address of the newly created
 * DIB. This DIB should be freed with <f dib_ptr_free>.                     */
    BOOL bExplorerDialog
/* @parm If TRUE, this function shows the explorer dialog.                  */
)
{
    OPENFILENAME    ofn;
    GODF            godf;
    BOOL            bResult;

    if ( lpbmi == NULL ) return FALSE;
#ifndef CDLGTOOL
    if ( !WM_LBSELCHANGE )
        WM_LBSELCHANGE = RegisterWindowMessage(LBSELCHSTRING);
#endif

    *lpbmi = NULL;

    /* Compile time check */
    bExplorerDialog =
#if(WINVER >= 0x0400)
    bExplorerDialog             /* Accept OFN_EXPLORER */
#else
    FALSE                       /* Always invalid */
#endif
    ;

    /* Run-time check; force FALSE if run under Windows smaller than 3.51 */
    if ( GetWindowsVersionNumber() <= 0x00035000 ) bExplorerDialog = FALSE;

    /* Do we have to get the control texts? */
    if ( !bExplorerDialog && !_pFirstText ) get_local_OFN_texts();

    /* The latter half of the allocation will be used by GetOpenFileName */
    if ( NULL == (godf.lpstrFile = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
            2 * MAX_PATH)) ) return FALSE;
    godf.nFileType = 0;
    godf.lpbmi = NULL;
    godf.bExplorerDialog = bExplorerDialog;

    /* Twiggle code here if you want to control preview mode */
    godf.bPreview = FALSE;

    MemSet(&ofn, 0, sizeof ofn);

    /* Initialize structure */
    ofn.lStructSize     = sizeof ofn;
    ofn.hwndOwner       = hWndParent;
    ofn.hInstance       = GetModuleHandle(NULL);
    if ( lpszFileOpenFilter )
        ofn.lpstrFilter = lpszFileOpenFilter;
    ofn.lpstrFile       = &godf.lpstrFile[MAX_PATH];
    ofn.nMaxFile        = MAX_PATH;
    ofn.Flags           = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST |
                          OFN_ENABLETEMPLATE | OFN_ENABLEHOOK;

    /* This will do for All. */
    if ( bExplorerDialog ) ofn.Flags |= OFN_EXPLORER;

    /* Currently my open file dialog does nothing with the godf structure. */
    ofn.lCustData       = (LONG)&godf;

    /* Set the hook function for the common dialog */
    ofn.lpfnHook        = (LPOFNHOOKPROC)hookproc_open_dib;

    /* Select the template */
    ofn.lpTemplateName  = bExplorerDialog ? MAKEINTRESOURCE(IDD_DIBOPEN) :
        MAKEINTRESOURCE(IDD_DIBOPENT);

    /* Launch hooked dialog */
    if ( FALSE != (bResult = (GetOpenFileName(&ofn))) ) {

        /* Verify if this is a valid bitmap file. */
        godf.lpbmi = verify_bmp_file(ofn.lpstrFile);
        godf.nFileType = ofn.nFilterIndex;

        /* Set return values */
        if ( godf.lpbmi ) {
            if ( lpnFileType ) *lpnFileType = godf.nFileType;
            if ( lpszBufName ) lstrcpyn(lpszBufName, ofn.lpstrFile, nSize);
            *lpbmi = godf.lpbmi;
        }
    }

    /* Clean up */
    HeapFree(GetProcessHeap(), 0, godf.lpstrFile);
    return bResult;
}

/*-PUB----------------------------------------------------------------------*
    @func get_open_dib_file is the simpler version of its engine
    <f get_open_dib_file>. For more information refer to that function.
    @rdesc Returns TRUE if successful or FALSE if error occurred.
 *--------------------------------------------------------------------------*/
BOOL get_open_dib_file(
    HWND hWndParent,        /* @parm Parent for dialog.                     */
    LPCSTR lpszFilter,      /* @parm Filter for dialog.                     */
    LPSTR lpszFileName,     /* @parm Buffer returning selected file's name. */
    int nSize,              /* @parm Number of characters that fitn in <p lpszFileName> */
    LPBITMAPINFO* lpbmi,    /* @parm Pointer receiving pointer to DIB.      */
    BOOL bExplorer          /* @parm TRUE: uses explorer dialog.            */
)
{
    /* All. Last parameter will twiggle to FALSE if compiled under Windows
       version < 4.0 */
    return _get_open_dib_file(hWndParent, lpszFilter, NULL, lpszFileName, nSize,
        lpbmi, bExplorer);
}

/*--------------------------------------------------------------------------*
    Dialog procedure for DIB preview dialog. Remember: this hook dialog is
    a child of the actual common dialog.
 *--------------------------------------------------------------------------*/
static BOOL CALLBACK hookproc_open_dib(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#ifdef CDLGTOOL
/* iCDLGTOOL! Let CDLGTOOL.C do its things first.                           */
    PreTranslateHookMessage(hDlg, uMsg, wParam, lParam);
#else
    if ( uMsg == WM_LBSELCHANGE ) {
        if ( wParam == lst2 && HIWORD(lParam) == CD_LBSELCHANGE ) {
            SetProp(hDlg, PROP_LAST_SELECTED_DIR, (HANDLE)LOWORD(lParam));
        } else if ( wParam == lst1 && HIWORD(lParam == CD_LBSELCHANGE ) ) {
            SetProp(hDlg, PROP_LAST_SELECTED_FILE, (HANDLE)LOWORD(lParam));
        }
        return 0;
    }
#endif
    switch ( uMsg ) {

        case WM_NOTIFY:
#if(WINVER < 0x0400)
            return FALSE;
#else
            if ( ((LPOFNOTIFY)lParam)->hdr.code == CDN_SELCHANGE && InPreviewMode(hDlg) )
                return hookproc_on_selchange(hDlg);
            else if ( ((LPOFNOTIFY)lParam)->hdr.code == CDN_FILEOK )
                return hookproc_on_fileok(hDlg);
            else return FALSE;
#endif

        case WM_COMMAND:
            return hookproc_on_command(hDlg, LOWORD(wParam), HIWORD(wParam),
                (HWND)lParam);

		/*** Pass these messages to DIB Window control ***/
		case WM_PALETTECHANGED:
		case WM_QUERYNEWPALETTE:
			SendMessage(GetDlgItem(hDlg, IDC_PREVIEW), uMsg, wParam, lParam);
			break;

        case WM_INITDIALOG:
            return hookproc_on_initdialog(hDlg, lParam);

        case WM_DESTROY:
            /* Remove all properties */
            WINVTRACE("%s, %d, WM_DESTROY seen", __FILE__, __LINE__);
            RemoveProp(hDlg, PROP_PREVIEW_WIDTH);
            RemoveProp(hDlg, PROP_PREVIEW_HEIGHT);
            RemoveProp(hDlg, PROP_PREVIEW_MODE);
#ifndef CDLGTOOL
            RemoveProp(hDlg, PROP_LAST_SELECTED_DIR);
            RemoveProp(hDlg, PROP_LAST_SELECTED_FILE);
#endif
            return FALSE;

        default:
            return FALSE;
    }

    return TRUE;
}

/*--------------------------------------------------------------------------*
    Initialize dialog
 *--------------------------------------------------------------------------*/
static BOOL hookproc_on_initdialog(HWND hDlg, LPARAM lParam)
{
    RECT    rcWindow;
    HWND    hDibCtrl;

    /* Save data. lParam is a pointer to the original OPENFILENAME struct   */
    PutDlgPtr(hDlg, ((LPOPENFILENAME)lParam)->lCustData);

    /* If we requested an old-style common dialog, let's set the texts of
     *  the controls.                                                       */
    if ( !IsExplorerDialog(hDlg) ) set_control_chain_text(_pFirstText, hDlg);

    /* Set preview mode (default is off) */
    twiggle_preview_controls(hDlg, (GetDlgPtr(hDlg))->bPreview);
    update_statistics(hDlg, NULL);

    /* Get original dimensions of preview window. */
    GetWindowRect(hDibCtrl = GetDlgItem(hDlg, IDC_PREVIEW), &rcWindow);

    /* Calculate position for creation of DIB Window/control */
    MapWindowPoints(HWND_DESKTOP, hDlg, (LPPOINT)&rcWindow, sizeof(RECT) / sizeof(POINT));

    /* Store the original width and height of the preview window. Both are
     * the maximum allowed values. The height will be used to resize
     * the preview window (to match the aspect ratio of the original
     * bitmap)                                                              */
    SetProp(hDlg, PROP_PREVIEW_WIDTH, (HANDLE)(rcWindow.right - rcWindow.left));
    SetProp(hDlg, PROP_PREVIEW_HEIGHT, (HANDLE)(rcWindow.bottom - rcWindow.top));

    /* Destroy place holding static window */
    DestroyWindow(hDibCtrl);

    /* Try to create a dib window control. Notice useage of the special
     * DWS_XXX styles. WS_EX_STATICEDGE gives us a 3D-border.               */
    hDibCtrl = CreateWindowEx(WS_EX_STATICEDGE, DIB_VWR_CLASSNAME, DIB_VWR_CLASSNAME,
        WS_BORDER | WS_CHILD | WS_VISIBLE | DWS_FITTOCLIENT | DWS_NOSCROLLBARS,
        rcWindow.left, rcWindow.top,
        rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top,
        hDlg, (HMENU)IDC_PREVIEW, (HINSTANCE)GetModuleHandle(NULL), NULL);

    /* Failed to create! Send a cancel message to parent. */
    if ( !hDibCtrl ) {
        WINTRACE("Preview creation failed");
        return PostMessage(GetParent(hDlg), WM_COMMAND,
            MAKEWPARAM(IDCANCEL, BN_CLICKED),
            (LPARAM)GetDlgItem(GetParent(hDlg), IDCANCEL));
    }

    return TRUE;
}

/*--------------------------------------------------------------------------*
    If we're in preview mode, we need to take care of redrawing the
    currently selected bitmap.
 *--------------------------------------------------------------------------*/
static BOOL hookproc_on_selchange(HWND hDlg)
{
    char    buf[MAX_PATH];
    LPGODF  lpgodf = GetDlgPtr(hDlg);

    buf[0] = 0;
    if ( GetSelFilePath(hDlg, buf, MAX_PATH) > 0 ) {
        HWND            hWndPreview = GetDlgItem(hDlg, IDC_PREVIEW);
        LPBITMAPINFO    lpbmi;

        if ( *((*lpgodf).lpstrFile) && lstrcmpi(buf, lpgodf->lpstrFile) == 0 ) {

            /* Get the original pointer (param 0) */
            lpbmi = GetWindowDIBits(hWndPreview, 0);

            /* We already had this file. */
            if ( !IsWindowVisible(hWndPreview) )
                ShowWindow(hWndPreview, SW_SHOW);

            /* Update window */
            update_statistics(hDlg, lpbmi);
            UpdateWindow(hWndPreview);
        } else {
            lpbmi = verify_bmp_file(buf);
            if ( lpbmi ) {
                /* Update preview window */
                update_statistics(hDlg, lpbmi);
                update_preview_window(hWndPreview, lpbmi);
                lstrcpyn(lpgodf->lpstrFile, buf, MAX_PATH);
            } else WINTRACE("Invalid bitmap");
        }
    }
    return TRUE;
}

/*--------------------------------------------------------------------------*
    Called when user pressed the OK button. Is a place holder for future
    extensions.
 *--------------------------------------------------------------------------*/
static BOOL hookproc_on_fileok(HWND hDlg)
{
    /* Place holder */
    hDlg = hDlg;
    return TRUE;
}

static BOOL hookproc_on_command(HWND hDlg, WORD wId, WORD wNotification,
    HWND hWndCtrl)
{
    switch ( wId ) {

        /* All. */
        case IDC_PREVIEWCHECK:
            return command_previewcheck(hDlg);

        /* Ver < 4.0 */
        case IDOK:
            if ( !IsExplorerDialog(hDlg) )
                hookproc_on_fileok(hDlg);
            break;

        /* Ver < 4.0 */
       // case LST1:
       //     if ( wNotification == LBN_SELCHANGE && InPreviewMode(hDlg) )
       //        hookproc_on_selchange(hDlg);
       //     break;
    }
    return FALSE;
}

static BOOL command_previewcheck(HWND hDlg)
{
    BOOL    bPreview = (InPreviewMode(hDlg) ^ 1);

    /* Flip preview mode */
    twiggle_preview_controls(hDlg, bPreview);

    /* Perhaps there's a file selected in the listbox, we want to update! */
    if ( bPreview )
        hookproc_on_selchange(hDlg);
    else {
        update_statistics(hDlg, NULL); /* Fill with zeroes */
    }
    return TRUE;
}

/*--------------------------------------------------------------------------*
    verify_bmp_file, checks if a selected file is a valid bitmap. Put
    here the code to detect file formats.
 *--------------------------------------------------------------------------*/
static LPBITMAPINFO verify_bmp_file(LPCSTR lpszFile)
{
    LPBITMAPINFO    lpbmi = read_bmp_file_win32_ptr(lpszFile);
    HBITMAP         hBitmap = (lpbmi != NULL ? ptr_to_hbitmap(lpbmi, NULL) : NULL);

    /* Create bitmap to verify valid bitmap */
    if ( hBitmap ) DeleteObject(hBitmap);
    return lpbmi;
}

static VOID set_new_stats(HWND hDlg, LONG lWidth, LONG lHeight,
    LONG lImageSize, LONG lColors)
{
    SetDlgItemInt(hDlg, IDC_EDITWIDTH, lWidth, FALSE);
    SetDlgItemInt(hDlg, IDC_EDITHEIGHT, lHeight, FALSE);
    SetDlgItemLong(hDlg, IDC_EDITSIZE, lImageSize, FALSE);
    SetDlgItemLong(hDlg, IDC_EDITCOLORS, lColors, FALSE);
}

static VOID update_statistics(HWND hDlg, LPBITMAPINFO lpbmi)
{
    if ( lpbmi != NULL ) {
        LPBITMAPINFOHEADER lpbmih = (LPBITMAPINFOHEADER)lpbmi;
        set_new_stats(hDlg, lpbmih->biWidth, lpbmih->biHeight,
            (LONG)dib_size(lpbmi), dib_num_colors(lpbmi));
    } else set_new_stats(hDlg, 0, 0, 0, 0);
}

static VOID twiggle_preview_controls(HWND hDlg, BOOL bEnable)
{
    int nId = IDC_EDITWIDTH;

    /* Hide or show the preview control? */
    if ( !bEnable ) {
        ShowWindow(GetDlgItem(hDlg, IDC_PREVIEW), SW_HIDE);
    }

    /* Disable all other info controls */
    for ( ; nId <= IDC_EDITCOLORS; nId++ )
        EnableWindow(GetDlgItem(hDlg, nId), bEnable);

    SetPreviewMode(hDlg, bEnable);
}

static VOID update_preview_window(HWND hWndDibCtrl, LPBITMAPINFO lpbmi)
{
    /* This control might be hidden already. But that doesn't matter. */
    ShowWindow(hWndDibCtrl, SW_HIDE);

    /* Resize window to match aspect ratio of original DIB file */
    resize_preview_window(hWndDibCtrl, lpbmi->bmiHeader.biWidth, lpbmi->bmiHeader.biHeight);

    /* Set palette and bitmap */
    SetBitmapAndPalette(hWndDibCtrl, lpbmi, FALSE);

    /* Update visually */
    ShowWindow(hWndDibCtrl, SW_SHOW);
    UpdateWindow(hWndDibCtrl);
}

static VOID resize_preview_window(HWND hWndDibCtrl, LONG lWidth, LONG lHeight)
{
    LONG    lMaxWidth = (LONG)GetProp(GetParent(hWndDibCtrl), PROP_PREVIEW_WIDTH),
            lMaxHeight = (LONG)GetProp(GetParent(hWndDibCtrl), PROP_PREVIEW_HEIGHT),
            lNewWidth, lNewHeight;

    if ( lWidth <= lMaxWidth && lHeight <= lMaxHeight ) {
        lNewWidth = lWidth;
        lNewHeight = lHeight;
    } else {
        lNewHeight = lMaxHeight;
        lNewWidth = min((lWidth * lMaxHeight) / lHeight, lMaxWidth);
    }

    /* Resize */
    SetWindowPos(hWndDibCtrl, 0, 0, 0, lNewWidth, lNewHeight,
        SWP_NOZORDER | SWP_NOMOVE | SWP_NOREDRAW | SWP_NOACTIVATE);
}

/*****************/

/*--------------------------------------------------------------------------*
    Several functions to get the support for old-style file open dialogs
    straight.
 *--------------------------------------------------------------------------*/

/* 0x0a11fab2 / 042197 - Here lies the original get_sel_file_path. May it
 * rest in peace and may it remain as a wrapper of the CDLGTOOL functions   */
int get_sel_file_path(HWND hDlg, LPSTR lpszBuf, int nBufSize)
{
/* iCDLGTOOL! */
#ifdef CDLGTOOL
    return GetSelectedFilePath(hDlg, lpszBuf, nBufSize);
#else
    LPSTR Walk;
    int LastSelected = (int)GetProp(hDlg, PROP_LAST_SELECTED_DIR);
    int Len, Current;
    if ( LastSelected == 0 ) {
        WINTRACE("Selected zero");
    }
    for ( Walk = lpszBuf, Current = 0; Current <= LastSelected; Current++ ) {
        Len = (int)SendDlgItemMessage(hDlg, lst2, LB_GETTEXT,
            (WPARAM)Current, (LPARAM)(LPSTR)Walk);
        if ( Len == -1 ) {
            WINTRACE("Error retrieving dir");
            return 0;
        }
        if ( Len > 0 && Walk[Len - 1] != '\\' )
            Walk[Len] = '\\', Len++;
        Walk += Len;
    }
    LastSelected = (int)GetProp(hDlg, PROP_LAST_SELECTED_FILE);
    if ( !LastSelected ) {
        WINTRACE("Error retrieving file name");
        return 0;
    } else {
        Len = (int)SendDlgItemMessage(hDlg, lst1, LB_GETTEXT,
            (WPARAM)LastSelected, (LPARAM)(LPSTR)Walk);
        if ( Len < 1 ) {
            WINTRACE("Error retrieving file name");
            return 0;
        }
        Walk += Len;
    }
    return Walk - lpszBuf;
#endif
}

/*--------------------------------------------------------------------------*
    build_control_chain, builds a chain of dialog controls. The owner of
    the control pointer is responsible for house cleaning. DIBVWR will
    never clean up this memory.
 *--------------------------------------------------------------------------*/
static void build_control_chain(PCONTROLS* pHeader, HWND hWnd)
{
    HWND        hChild = GetWindow(hWnd, GW_CHILD);
    PCONTROLS   pWalk;
    int         nLen;
    char        buf[256];

    pWalk = *pHeader = NULL;
    if ( !hChild ) return;
    while ( hChild ) {
        PCONTROLS   pChild = (PCONTROLS)HeapAlloc(GetProcessHeap(),
            HEAP_ZERO_MEMORY, sizeof(CONTROLS));

        if ( pChild != NULL ) {
            pChild->pControlText = NULL;
            pChild->pControlNext = NULL;

            nLen = GetWindowText(hChild, buf, sizeof buf);

            /* Allocate memory for string */
            if ( nLen ) {
                pChild->pControlText = (LPSTR)HeapAlloc(GetProcessHeap(),
                    HEAP_ZERO_MEMORY, nLen + 1);
                if ( pChild->pControlText != NULL )
                    lstrcpy(pChild->pControlText, buf);
            }

            /* Add to list */
            if ( pWalk != NULL ) (*pWalk).pControlNext = pChild;
            else *pHeader = pChild;
            pWalk = pChild;
        }

        /* Next child */
        hChild = GetWindow(hChild, GW_HWNDNEXT);
    }
}

/*--------------------------------------------------------------------------*
    Not used.
 *--------------------------------------------------------------------------*/
static void dispose_control_chain(PCONTROLS pHeader)
{
    while ( pHeader ) {
        PCONTROLS   pOld = pHeader;
        if ( pHeader->pControlText != NULL )
            HeapFree(GetProcessHeap(), 0, pHeader->pControlText);
        pHeader = pHeader->pControlNext;
        HeapFree(GetProcessHeap(), 0, pOld);
    }
}

static void set_control_chain_text(PCONTROLS pHeader, HWND hWnd)
{
    HWND    hChild = GetWindow(hWnd, GW_CHILD);
/* Walk the controls and set the original texts                             */
    while ( pHeader && hChild ) {
        if ( pHeader->pControlText != NULL )
            SetWindowText(hChild,(LPSTR)pHeader->pControlText);
        pHeader = pHeader->pControlNext;
        hChild = GetWindow(hChild, GW_HWNDNEXT);
    }
}

UINT CALLBACK retrieve_OFN_texts(HWND hDlg, UINT uMsg, WPARAM wp, LPARAM lp)
{
    switch ( uMsg ) {
        case WM_INITDIALOG:
            build_control_chain(&_pFirstText, hDlg);
            SendMessage(hDlg, WM_COMMAND, IDABORT, 0L);
            return TRUE;
    }
    return FALSE;
}

/*--------------------------------------------------------------------------*
    get_local_OFN_texts, retrieves the texts of child controls in the
    system's OpenFileDialog.
 *--------------------------------------------------------------------------*/
static void get_local_OFN_texts(void)
{
    OPENFILENAME    ofn;

    MemSet(&ofn, 0, sizeof ofn);
    ofn.lStructSize = sizeof ofn;
    ofn.Flags |= OFN_ENABLEHOOK | OFN_HIDEREADONLY;
    ofn.lpfnHook = retrieve_OFN_texts;

    /* Get text of local common dialog */
    GetOpenFileName(&ofn);
}
/* End Of File */
