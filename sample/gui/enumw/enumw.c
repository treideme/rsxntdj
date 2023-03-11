/*
 *  ENUMW.C
 *
 *  enum fonts, windows and resources
 *
 *  written by:
 *
 *   Rainer Schnitker
 *   Fred Kiefer
 *
 */

#ifdef __GNUC__
#include <crtrsxnt.h>           /* for C runtime DLL compile switch */
#endif

#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <string.h>
#include "enumw.h"

/* As we don't use UNICODE, we have to define this here */
int WINAPI lstrlenW (LPCWSTR lpString);

#define PAINT_BORDER 25

#define IDC_LIST 500

/*
 * Local Data
 */

static OLDFONTENUMPROC lpfnEnumFonts;   /* Win 3.1x instance code */
static WNDENUMPROC lpfnEnumWindows;
static FONTENUMPROC lpfnEnumFontFam;

static char szAppname[] = "EnumW";      /* name of class and window */
static HINSTANCE hInstance;
static HWND hWindow;                    /* Main windows */
static HWND hListWnd;                   /* child window */


/* ----------------------------------------------------------------------------
 *  Enum Functions
 */

static BOOL CALLBACK
EnumLangsFunc (
     HANDLE hModule,
     LPCTSTR lpType,
     LPCTSTR lpName,
     WORD wLang,
     LONG lParam)
{
  HANDLE hResInfo;
  char *szBuffer;
  char szText[256];
  int cbString = 0;
  BOOL bDialog = FALSE;

  szBuffer = szText;

  if ((ULONG) lpType & 0xFFFF0000)
    {
      cbString = sprintf (szBuffer, "Type: %s", lpType);
    }
  else
    {
      USHORT uType = (USHORT) (ULONG) lpType;

      switch (uType)
        {
        case RT_ACCELERATOR:
          strcpy (szBuffer, "Type: Accelartor");
          break;
        case RT_BITMAP:
          strcpy (szBuffer, "Type: Bitmap");
          break;
        case RT_DIALOG:
          bDialog = TRUE;
          strcpy (szBuffer, "Type: Dialog");
          break;
        case RT_FONT:
          strcpy (szBuffer, "Type: Font");
          break;
        case RT_FONTDIR:
          strcpy (szBuffer, "Type: Fontdir");
          break;
        case RT_MENU:
          strcpy (szBuffer, "Type: Menu");
          break;
        case RT_RCDATA:
          strcpy (szBuffer, "Type: RCDATA");
          break;
        case RT_STRING:
          strcpy (szBuffer, "Type: Strings");
          break;
        case RT_MESSAGETABLE:
          strcpy (szBuffer, "Type: Messages");
          break;
        case RT_CURSOR:
          strcpy (szBuffer, "Type: Cursor");
          break;
        case RT_GROUP_CURSOR:
          strcpy (szBuffer, "Type: G Cursor");
          break;
        case RT_ICON:
          strcpy (szBuffer, "Type: Icon");
          break;
        case RT_GROUP_ICON:
          strcpy (szBuffer, "Type: G Icon");
          break;
        case RT_VERSION:
          {
            strcpy (szBuffer, "Type: Version");
            break;
          }
        default:
          cbString = sprintf (szBuffer, "Type: %u", uType);
        }
    }
  szBuffer = szText + strlen (szText);

  hResInfo = FindResourceEx (hModule, lpType, lpName, wLang);

  if (bDialog)
    {
      HGLOBAL hGlobal;
      LPVOID lpRes;
      LPDLGTEMPLATE lpdt;
      LPDLGITEMTEMPLATE lpdit;
      LPWORD lpw;
      LPWSTR lpwsz;
      char szConvert[256];
      int items;
      int i;

      hGlobal = LoadResource (hModule, hResInfo);
      lpRes = LockResource (hGlobal);
      if (lpRes != (LPVOID) (((ULONG) lpRes + 3) & ~3))
        MessageBox (hWindow, "Resource at wrong alignment", NULL, MB_OK);

      lpdt = (LPDLGTEMPLATE) lpRes;
      items = lpdt->cdit;
      lpw = (LPWORD) (lpdt + 1);

      /* Is there a menu of any kind? */
      if (*lpw == 0)
        /* no menu */
        lpw++;
      else if (*lpw == 0xFFFF)
        lpw += 2;
      else
        {
          lpwsz = (LPWSTR) lpw;
          /*WideCharToMultiByte(CP_OEMCP, 0, lpwsz, -1,
           * szConvert, 256, NULL, FALSE); */
          lpw = (LPWORD) (lpwsz + lstrlenW (lpwsz) + 1);
        }

      /* Is there a window definition of any kind? */
      if (*lpw == 0)
        /* standard dialog */
        lpw++;
      else if (*lpw == 0xFFFF)
        lpw += 2;
      else
        {
          lpwsz = (LPWSTR) lpw;
          /*WideCharToMultiByte(CP_OEMCP, 0, lpwsz, -1,
           * szConvert, 256, NULL, FALSE); */
          lpw = (LPWORD) (lpwsz + lstrlenW (lpwsz) + 1);
        }

      /* dialog title */
      lpwsz = (LPWSTR) lpw;
      WideCharToMultiByte (CP_OEMCP, 0, lpwsz, -1,
                           szConvert, 256, NULL, FALSE);
      lpw = (LPWORD) (lpwsz + lstrlenW (lpwsz) + 1);

      /* Is there a font definition? */
      if ((lpdt->style & DS_SETFONT) == DS_SETFONT)
        {
          lpw++;
          lpwsz = (LPWSTR) lpw;
          /*WideCharToMultiByte(CP_OEMCP, 0, lpwsz, -1,
           * szConvert, 256, NULL, FALSE); */
          lpw = (LPWORD) (lpwsz + lstrlenW (lpwsz) + 1);
        }

      cbString = sprintf (szBuffer, "\t Title = %s\tItems =%u (%u,%u,%u,%u)",
                    szConvert, items, lpdt->x, lpdt->y, lpdt->cx, lpdt->cy);
      SendMessage (hListWnd, LB_ADDSTRING, 0, (LPARAM) szText);

      /* Loop over every dialog item in the dialog */
      for (i = 0; i < items; i++)
        {
          /* reset buffer */
          szBuffer = szText;

          /* round up to the next 32-bit boundary */
          lpw = (LPWORD) (((ULONG) lpw + 3) & ~3);

          lpdit = (LPDLGITEMTEMPLATE) lpw;
          lpw = (LPWORD) (lpdit + 1);

          /* control class name */
          if (*lpw == 0xFFFF)
            lpw += 2;
          /* Flag out 0x8000 to get the byte value */
          else
            {
              lpwsz = (LPWSTR) lpw;
              /*WideCharToMultiByte(CP_OEMCP, 0, lpwsz, -1,
               * szConvert, 256, NULL, FALSE); */
              lpw = (LPWORD) (lpwsz + lstrlenW (lpwsz) + 1);
            }

          /* round up to the next 16-bit boundary */
          lpw = (LPWORD) (((ULONG) lpw + 1) & ~1);

          /* control title */
          if (*lpw == 0xFFFF)
            {
              szConvert[0] = 0;
              lpw += 2;
            }
          else
            {
              lpwsz = (LPWSTR) lpw;
              WideCharToMultiByte (CP_OEMCP, 0, lpwsz, -1,
                                   szConvert, 256, NULL, FALSE);
              lpw = (LPWORD) (lpwsz + lstrlenW (lpwsz) + 1);
            }

          /* Skip creation data if there is any */
          lpw++;

          cbString = sprintf (szBuffer, "\t ID = %u  %s (%u,%u,%u,%u)",
            lpdit->id, szConvert, lpdit->x, lpdit->y, lpdit->cx, lpdit->cy);
          SendMessage (hListWnd, LB_ADDSTRING, 0, (LPARAM) szText);
        }
    }
  else
    {
      if ((ULONG) lpName & 0xFFFF0000)
        {
          cbString = sprintf (szBuffer, "\tName: %s", lpName);
        }
      else
        {
          cbString = sprintf (szBuffer, "\tName: %u", (USHORT) (ULONG) lpName);
        }
      szBuffer = szText + strlen (szText);

      cbString = sprintf (szBuffer, "\tLanguage: %u", (USHORT) wLang);
      szBuffer = szText + strlen (szText);

      cbString = sprintf (szBuffer, "\t Size = %lu hResInfo = %lx",
                      SizeofResource (hModule, hResInfo), (ULONG) hResInfo);
      SendMessage (hListWnd, LB_ADDSTRING, 0, (LPARAM) szText);
    }


  return TRUE;
}

static BOOL CALLBACK EnumNamesFunc (HANDLE hModule, LPCTSTR lpType,
                                    LPTSTR lpName, LONG lParam)
{
  return EnumResourceLanguages (hModule, lpType, lpName,
                                (ENUMRESLANGPROC) EnumLangsFunc, lParam);
}

static BOOL CALLBACK EnumTypesFunc (HANDLE hModule, LPTSTR lpType, LONG lParam)
{
  return EnumResourceNames (hModule, lpType,
                            (ENUMRESNAMEPROC) EnumNamesFunc, lParam);
}

static void do_enumres (HWND hWnd)
{
  HMODULE hExe;

  SendMessage (hListWnd, LB_RESETCONTENT, 0, 0);
  SendMessage (hListWnd, WM_SETREDRAW, 0, 0);

  /* hExe = (HMODULE) NULL; */
  hExe = LoadLibrary ("winedit.exe");
  if (!EnumResourceTypes (hExe, (ENUMRESTYPEPROC) EnumTypesFunc, 0))
    MessageBox (hWnd, "EnumRes failed", NULL, MB_OK);

  InvalidateRect (hListWnd, NULL, TRUE);
  SendMessage (hListWnd, WM_SETREDRAW, 1, 0);
  UpdateWindow (hListWnd);
}


static int CALLBACK
EnumFontsProc (
    const LOGFONT * lpFont,
    const TEXTMETRIC * lpTM,
    int style,
    LPARAM str)
{
  if (lpTM->tmPitchAndFamily & TMPF_FIXED_PITCH)
    SendMessage (hListWnd, LB_ADDSTRING, 0, (LPARAM) lpFont->lfFaceName);
  return 1;

}

static int CALLBACK
EnumFontFamProc (
    const ENUMLOGFONT * lpFont,
    const NEWTEXTMETRIC * lpTM,
    int type,
    LPARAM str)
{
  if (type & TRUETYPE_FONTTYPE)
    SendMessage (hListWnd, LB_ADDSTRING, 0, (LPARAM) lpFont->elfFullName);

  return 1;
}

static void display_window (HWND hWnd, int level)
{
  static char text[256];
  static char class[256];
  RECT r;
  char *buf;
  int i;

  buf = text;

  for (i = 0; i < (int) level; i++)
    {
      *buf++ = ' ';
      *buf++ = ' ';
      *buf++ = ' ';
      *buf++ = ' ';
    }
  sprintf (buf, "%08lX    ", (LONG) hWnd);
  buf = text + strlen (text);

  if (GetClassName (hWnd, class, 256))
    {
      sprintf (buf, "[%s]    ", class);
      buf = text + strlen (text);
    }
  GetWindowRect (hWnd, &r);
  sprintf (buf, "(%ld,%ld,%ld,%ld)    ", r.left, r.top, r.right, r.bottom);
  buf = text + strlen (text);
  if (GetWindowText (hWnd, class, 256))
    {
      sprintf (buf, "<%s>", class);
      buf = text + strlen (text);
    }
  if (level == 0)
    {
      HINSTANCE hInst = (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE);

      if (GetModuleFileName (hInst, class, 256))
        sprintf (buf, "    %s", class);
    }

  /* we must convert 32bit flat pointer to 16bit far pointer */
  SendMessage (hListWnd, LB_ADDSTRING, 0, (LPARAM) text);
}

static HWND seen[1024] = {0};

static BOOL CALLBACK EnumWindowsProc (HWND hWnd, LPARAM level)
{
  HWND *ps;
  int i;
  static int num_wnd = 0;

  /* cheap check for duplicates */
  for (i = 0, ps = seen; i < num_wnd; i++, ps++)
    if (hWnd == *ps)
      return 1;
  if (num_wnd < 1024)
    seen[num_wnd++] = hWnd;

  display_window (hWnd, level);
  EnumChildWindows (hWnd, lpfnEnumWindows, level + 1);
  return 1;                     /* keep going */

}


/* ----------------------------------------------------------------------------
 *  do_functions for commands
 */

static void do_paint (HWND hWnd, char *fontname)
{
  static LOGFONT logFont =
  {
    0,
    0,
    0,
    0,
    400,
    FALSE,
    FALSE,
    FALSE,
    DEFAULT_CHARSET,
    OUT_DEFAULT_PRECIS,
    CLIP_DEFAULT_PRECIS,
    DEFAULT_QUALITY,
    DEFAULT_PITCH,
    ""
  };

  HFONT hFont;
  HDC hDC;
  RECT rect;

  /* erease old text */
  GetClientRect (hWnd, &rect);
  rect.bottom = PAINT_BORDER - 1;
  InvalidateRect (hWnd, &rect, TRUE);
  UpdateWindow (hWnd);

  /* fill font struct, max 32 chars */
  strncpy (logFont.lfFaceName, fontname, 32);
  logFont.lfFaceName[32] = 0;

  /* Show new text */
  hDC = GetDC (hWnd);

  if ((hFont = CreateFontIndirect (&logFont)) != NULL)
    {
      HFONT hOldFont = SelectObject (hDC, hFont);
      TextOut (hDC, 0, 0, logFont.lfFaceName, strlen(logFont.lfFaceName));
      SelectObject (hDC, hOldFont);
      DeleteObject (hFont);
    }
  else
    MessageBox (hWnd, "cannot create this font", NULL, MB_OK);

  ReleaseDC (hWnd, hDC);
}

static void do_enumfonts (HWND hWnd)
{
  HDC hDC;

  SendMessage (hListWnd, LB_RESETCONTENT, 0, 0);
  SendMessage (hListWnd, WM_SETREDRAW, 0, 0);

  hDC = GetDC (hWnd);
  if (!EnumFonts (hDC, NULL, lpfnEnumFonts, 0))
    MessageBox (hWnd, "EnumFonts failed", NULL, MB_OK);
  ReleaseDC (hWnd, hDC);

  InvalidateRect (hListWnd, NULL, TRUE);
  SendMessage (hListWnd, WM_SETREDRAW, 1, 0);
  UpdateWindow (hListWnd);
}

static void do_enumfontfam (HWND hWnd)
{
  HDC hDC;

  SendMessage (hListWnd, LB_RESETCONTENT, 0, 0);
  SendMessage (hListWnd, WM_SETREDRAW, 0, 0);

  hDC = GetDC (hWnd);
  if (!EnumFontFamilies (hDC, NULL, lpfnEnumFontFam, 0))
    MessageBox (hWnd, "EnumFontFam failed", NULL, MB_OK);
  ReleaseDC (hWnd, hDC);

  InvalidateRect (hListWnd, NULL, TRUE);
  SendMessage (hListWnd, WM_SETREDRAW, 1, 0);
  UpdateWindow (hListWnd);
}

static void do_enumwindows (HWND hWnd)
{
  SendMessage (hListWnd, LB_RESETCONTENT, 0, 0);
  SendMessage (hListWnd, WM_SETREDRAW, 0, 0);

  memset (seen, 0, sizeof (seen));
  if (!EnumWindows (lpfnEnumWindows, 0))
    MessageBox (hWnd, "EnumWindows failed", NULL, MB_OK);

  InvalidateRect (hListWnd, NULL, TRUE);
  SendMessage (hListWnd, WM_SETREDRAW, 1, 0);
  UpdateWindow (hListWnd);
}


/* ----------------------------------------------------------------------------
 *  Window Messages
 *  Functions
 */

static BOOL Enumw_OnCreate (HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
  HANDLE hFont;

  /* window is created, make instances (win 3.11 code) */

#ifdef _WIN32
  lpfnEnumFonts = (FARPROC) EnumFontsProc;
  lpfnEnumFontFam = (FARPROC) EnumFontFamProc;
  lpfnEnumWindows = (FARPROC) EnumWindowsProc;
#else
  lpfnEnumFonts = (OLDFONTENUMPROC)
    MakeProcInstance ((FARPROC) EnumFontsProc, hInstance);
  lpfnEnumFontFam = (FONTENUMPROC)
    MakeProcInstance ((FARPROC) EnumFontFamProc, hInstance);
  lpfnEnumWindows = (WNDENUMPROC)
    MakeProcInstance ((FARPROC) EnumWindowsProc, hInstance);
#endif

  hListWnd = CreateWindow (
                            "Listbox",
                            NULL,
                            (LBS_STANDARD & ~LBS_SORT) | LBS_HASSTRINGS |
                     LBS_NOREDRAW | LBS_USETABSTOPS | LBS_NOINTEGRALHEIGHT |
                            WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_CHILD,
                            0, 0, lpCreateStruct->cx, lpCreateStruct->cy,
                            hWnd,
                            (HMENU) IDC_LIST,
                            hInstance,
                            0);

  hFont = GetStockObject (SYSTEM_FIXED_FONT);
  SendMessage (hListWnd, WM_SETFONT, (WPARAM) hFont, TRUE);

  return (hListWnd != NULL);
}

static void Enumw_OnSize (HWND hWnd, UINT state, int cx, int cy)
{
  /* Top-level window is moved, move clild window */
  /* PAINT_BORDER = space for text out */

  MoveWindow (hListWnd, 0, PAINT_BORDER, cx, cy - PAINT_BORDER, TRUE);
}

static void Enumw_OnDestroy (HWND hWnd)
{
  /* Window is destroyed: free resources, send WM_QUIT */
  SendMessage (hListWnd, LB_RESETCONTENT, 0, 0);

#ifndef _WIN32
  FreeProcInstance ((FARPROC) lpfnEnumFonts);
  FreeProcInstance ((FARPROC) lpfnEnumFontFam);
  FreeProcInstance ((FARPROC) lpfnEnumWindows);
#endif

  PostQuitMessage (0);
}

static void Enumw_OnCommand (HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
  static int use_dblclk;

  switch (id)
    {

    case IDM_FONTS:
      do_enumfonts (hWnd);
      use_dblclk = 1;
      break;

    case IDM_FONTFAM:
      do_enumfontfam (hWnd);
      use_dblclk = 1;
      break;

    case IDM_WINDOWS:
      do_enumwindows (hWnd);
      use_dblclk = 0;
      break;

    case IDM_RESOURCES:
      do_enumres (hWnd);
      use_dblclk = 0;
      break;

    case IDM_ABOUT:
      MessageBox (hWnd,
                  "EnumW 1.31 Application\n"
                  "\n"
                  " Rainer Schnitker\n"
                  " Fred Kiefer",
                  szAppname, MB_OK | MB_ICONINFORMATION);
      break;

    case IDC_LIST:
      /* Check notification code */
      if (codeNotify == LBN_SELCHANGE && use_dblclk)
        {
          char fontname[128];

          WPARAM index = SendMessage (
                                       hListWnd,
                                       LB_GETCURSEL,
                                       0, 0);

          if (index != LB_ERR &&
              SendMessage (
                  hListWnd, LB_GETTEXT, index, (LPARAM) fontname) != LB_ERR)
            do_paint (hWnd, fontname);
        }
      break;
    }                           /* switch wparam */
}


/* ----------------------------------------------------------------------------
 *  Window Callback
 */

static LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
    {
    case WM_CREATE:
      return HANDLE_WM_CREATE (hWnd, wParam, lParam, Enumw_OnCreate);

    case WM_SIZE:
      return HANDLE_WM_SIZE (hWnd, wParam, lParam, Enumw_OnSize);

    case WM_DESTROY:
      return HANDLE_WM_DESTROY (hWnd, wParam, lParam, Enumw_OnDestroy);

    case WM_COMMAND:
      return HANDLE_WM_COMMAND (hWnd, wParam, lParam, Enumw_OnCommand);
    }

  return DefWindowProc (hWnd, message, wParam, lParam);
}


/* ----------------------------------------------------------------------------
 *  Application init functions
 */

static BOOL InitApplication (HINSTANCE hInstance)
{
  WNDCLASS wc;

  wc.style = 0;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon (hInstance, szAppname);
  wc.hCursor = LoadCursor (NULL, IDC_ARROW);
  wc.hbrBackground = GetStockObject (WHITE_BRUSH);
  wc.lpszMenuName = szAppname;
  wc.lpszClassName = szAppname;

  return RegisterClass (&wc);
}

static BOOL InitInstance (HINSTANCE hInstance, int nCmdShow)
{
  hWindow = CreateWindow (
                           szAppname,
                           "EnumW Application",
                           WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT,
                           CW_USEDEFAULT,
                           CW_USEDEFAULT,
                           CW_USEDEFAULT,
                           NULL, NULL,
                           hInstance,
                           NULL);

  if (!hWindow)
    return (FALSE);

  ShowWindow (hWindow, nCmdShow);
  UpdateWindow (hWindow);

  return TRUE;
}

int WINAPI WinMain (
                     HINSTANCE hInst,
                     HINSTANCE hPrevInst,
                     LPSTR lpszCmdParam,
                     int nCmdShow)
{
  MSG msg;

  hInstance = hInst;
  if (!InitApplication (hInstance))
    {
      MessageBox (NULL, "register class", NULL, MB_OK);
      return (FALSE);
    }
  if (!InitInstance (hInstance, nCmdShow))
    {
      MessageBox (NULL, "create window", NULL, MB_OK);
      return (FALSE);
    }

  while (GetMessage (&msg, NULL, 0, 0))
    {
      TranslateMessage (&msg);
      DispatchMessage (&msg);
    }
  return msg.wParam;
}
