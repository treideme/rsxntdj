/* rsxide.c - main rsxide file

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
#include "idmenu.h"
#include "idedlg.h"
#include "editdde.h"
#include "treeview.h"

#ifdef NONAMELESSUNION
#define U1(name)  u.##name
#define U2(name)  u2.##name
#define U3(name)  u3.##name
#else
#define U1(name)  name
#define U2(name)  name
#define U3(name)  name
#endif

/* --------- forward declaration --------------------------- */
static void button_target_menu_update (BOOL);
static void button_project_menu_update (BOOL);

/* --------- structures ------------------------------------ */

/* structure build from inifile */
struct obj_desc
  {
    char key[16];
    char src_ext[16];
    char dst_ext[16];
    char *command;
    char byeditor;
    char rsxntopt;
  };

#define SAVE_MAGIC_V1 "RSX-IDE"
#define SAVE_MAGIC "RSXIDE2"

struct save_project
  {
    char magic[8];
    int nTargets;
    int nSizeOfTarget;
  };

struct save_target
  {
    char szTargetName[260];
    union target_flags flags;
    int type;
    int nfiles;
    RECT rect;
  };

#define SAVE_SIZE_MAGIC "VALIDSZ"
struct save_size
  {
    char magic[8];  
    RECT rect;
    RECT comprect;
  };

struct runopt
  {
    char opt_make[260];
    char opt_run[260];
    char opt_debug[260];
  };

typedef unsigned char FILENAME[260];

/* --------- Global variables ------------------------------------ */

struct target_desc target_desc[5] =
{
  {"(gui/cui)", "exe"},
  {"(dll)", "dll"},
  {"(library)", "a"},
  {"(dual rsx)", "exe"},
  {"(dual emx)", "exe"}
};

HINSTANCE hInstance;

/* --------- local variables ------------------------------------- */

static char szAppClass[] = "RSXIDE";
static char szCompileClass[] = "RSXCOMPILE";
static char szTargetClass[] = "RSXTARGET";

static char szTmpMakefile[] = "MAKEFILE.TXT";
static char szDepMakefile[] = "MAKEFILE.DEP";
static char szAppTitle[] = "RSX-IDE";
static char szCompileTitle[] = "Compile Window";

static HWND hWndIde;            /* ide window */
static HWND hWndMdiClient;      /* client handle */
static HWND hWndCompileFrame;   /* compile window */
static HWND hWndCompileListBox; /* compile listbox */

static FILENAME LastFiles[4];
static char szProjectNext[MAX_PATH];
static char szProjectName[MAX_PATH];
static char szProjectDir[MAX_PATH];
static int win32s;
static int winv3x;
static BOOL need_save;
static BOOL makefile_used = FALSE;

static struct obj_desc *obj_desc;
static int nObjects;

static struct runopt runopt;

static void SetFileSaveStatus (BOOL value);
static BOOL target_touchall (void);

static char ** pszMacros;
static int  iMacros;

/* -------------------------------------------------------------------- */

static int iCharWidth;
static int iListboxMax;

int CompileListBox_AddString(char *s)
{
  int len = strlen(s) * iCharWidth;
  if (len > iListboxMax)
  {
    iListboxMax = len;
    ListBox_SetHorizontalExtent(hWndCompileListBox, iListboxMax);
  }
  return ListBox_SetCurSel(hWndCompileListBox, ListBox_AddString(hWndCompileListBox, s));
}

static void read_ini (HWND hWnd)
{
  const char * Commands = "Commands";
  const char * Editor = "Editor";
  const char * MACROS = "Macros";
  char name[] = "File1";
  
  char ini[_MAX_PATH], *ext;
  const int iBuflen = 4096;
  char *buf, *section;
  int i, len;
  HMENU hMenu;

  GetModuleFileName (hInstance, ini, 260);
  ext = strrchr (ini, '.');
  strcpy (ext + 1, "ini");

  GetPrivateProfileString (Editor, "Editor", "#", dde_editor, 260, ini);
  GetPrivateProfileString (Editor, "Service", "#", dde_service, 260, ini);
  GetPrivateProfileString (Editor, "Topic", "#", dde_topic, 260, ini);
  GetPrivateProfileString (Editor, "FileOpen", "#", dde_fileopen, 260, ini);
  GetPrivateProfileString (Editor, "Goto", "#", dde_goto, 260, ini);
  GetPrivateProfileString (Editor, "MarkLine", "#", dde_markline, 260, ini);

  for (i = 0; i < 4; ++i)
    {
      name[4] = '1' + i;
      GetPrivateProfileString ("LastOpen", name, "#", LastFiles[i], 260, ini);
      if (LastFiles[i][0] == '#')
        LastFiles[i][0] = '\0';
    }

  hMenu = GetSubMenu (GetMenu (hWnd), 0);
  AppendMenu (hMenu, MF_SEPARATOR, 0, NULL);

  for (i = 0; i < 4; ++i)
    {
      char file[_MAX_PATH];
      if (LastFiles[i][0])
        {
          file[0] = '&';
          file[1] = '1' + i;
          file[2] = ' ';
          file[3] = 0;
          strcat (file, LastFiles[i]);
          AppendMenu (hMenu, MF_ENABLED, IDM_FILE_FILE1 + i, file);
        }
    }

  // read in all sections in [Commands]
  buf = malloc (iBuflen);
  len = GetPrivateProfileString (Commands, NULL, "#", buf, iBuflen, ini);

  nObjects = 0;
  obj_desc = (struct obj_desc *) malloc (1);
  len = 0;
  section = buf;
  for (;;)
    {
      char pszTmp[200];

      if ((len = strlen (section)) == 0)
        break;
      obj_desc = realloc (obj_desc, ++nObjects * sizeof (struct obj_desc));

      strcpy (obj_desc[nObjects - 1].key, section);
      GetPrivateProfileString (Commands, section, "#", pszTmp, sizeof (pszTmp), ini);
      obj_desc[nObjects - 1].command = strdup (pszTmp);
      obj_desc[nObjects - 1].byeditor = GetPrivateProfileInt (section, "Edit", 0, ini);
      obj_desc[nObjects - 1].rsxntopt = GetPrivateProfileInt (section, "RsxntOptions", 0, ini);
      GetPrivateProfileString (section, "Obj", "#", obj_desc[nObjects - 1].dst_ext, sizeof (obj_desc[nObjects - 1].dst_ext), ini);
      GetPrivateProfileString (section, "Ext", "#", pszTmp, sizeof (pszTmp), ini);
      if (pszTmp[0] != '#')
        {
          char *p = strtok (pszTmp, " ");
          strcpy (obj_desc[nObjects - 1].src_ext, p);
          while ((p = strtok (NULL, " ")) != NULL)
            {
              obj_desc = realloc (obj_desc, ++nObjects * sizeof (struct obj_desc));
              memcpy (&obj_desc[nObjects - 1], &obj_desc[nObjects - 2], sizeof (struct obj_desc));
              strcpy (obj_desc[nObjects - 1].src_ext, p);
            }
        }
      section += len + 1;
    }

  GetPrivateProfileString (MACROS, NULL, "#", buf, iBuflen, ini);
  iMacros = 0;
  pszMacros = (char **) malloc (1);
  len = 0;
  section = buf;
  for (;;)
    {
      char pszTmp[200];
      int l;
      if ((len = strlen (section)) == 0)
        break;
      strcpy (pszTmp, section);
      strcat (pszTmp, "=");
      l = strlen (pszTmp);
      GetPrivateProfileString (MACROS, section, "#", pszTmp+l, sizeof(pszTmp) -l, ini);
      pszMacros = realloc (pszMacros, ++iMacros * sizeof (char *));
      pszMacros[iMacros-1] = strdup (pszTmp);
      section += len + 1;
    }
     
  free (buf);
}

static void write_ini (void)
{
  static char Editor[] = "Editor";
  static char name[] = "File1";
  char ini[260], *ext;
  int i;

  GetModuleFileName (hInstance, ini, 260);
  ext = strrchr (ini, '.');
  strcpy (ext + 1, "ini");

  WritePrivateProfileString (Editor, "Editor", dde_editor, ini);
  WritePrivateProfileString (Editor, "Service", dde_service, ini);
  WritePrivateProfileString (Editor, "Topic", dde_topic, ini);
  WritePrivateProfileString (Editor, "FileOpen", dde_fileopen, ini);
  WritePrivateProfileString (Editor, "Goto", dde_goto, ini);
  WritePrivateProfileString (Editor, "MarkLine", dde_markline, ini);

  for (i = 0; i < 4; ++i)
    {
      name[4] = '1' + i;
      WritePrivateProfileString ("LastOpen", name, LastFiles[i], ini);
    }
}

static int MessageBoxError (char *text)
{
  return MessageBox (hWndIde, text, NULL, MB_OK | MB_ICONINFORMATION);
}

static BOOL CommDlg (HWND hWnd, char *name, char *title, int mode)
{
  static char szDirName[MAX_PATH];
  OPENFILENAME ofn;
  BOOL bRet;
  char *s;

  if (!*szDirName)
    GetCurrentDirectory (sizeof (szDirName), szDirName);

  ofn.lStructSize = sizeof (ofn);
  ofn.hwndOwner = hWnd;
  ofn.hInstance = hInstance;
  ofn.lpstrFilter = "Ide Project (*.irs)\0*.irs\0All files (*.*)\0*.*\0";
  ofn.lpstrCustomFilter = NULL;
  ofn.nMaxCustFilter = 0;
  ofn.nFilterIndex = 1;
  ofn.lpstrFile = name;
  ofn.nMaxFile = MAX_PATH;
  ofn.lpstrFileTitle = NULL;
  ofn.nMaxFileTitle = 0;
  ofn.lpstrInitialDir = szDirName;
  ofn.lpstrTitle = title;

  if (mode == 0)                       /* New */
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
  else if (mode == 1)                  /* Open */
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
  else if (mode == 2)                  /* Save */
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;

  ofn.lpstrDefExt = NULL;

  if (mode == 2)
    bRet = GetSaveFileName (&ofn);
  else
    bRet = GetOpenFileName (&ofn);

  if (bRet)
    {
      int len;

      len = strlen (name);
      if (stricmp (name + len - 4, ".irs"))
        strcat (name, ".irs");

      strcpy (szDirName, name);
      s = szDirName + len;
      while (s > szDirName && *--s != '\\')
        ;
      *s = '\0';
    }

  return bRet;
}

typedef BOOL (*FSERVICE) (HWND);

BOOL CALLBACK EnumChildProc (HWND hWnd, LONG lParam)
{
  FSERVICE fnService;
  char class[sizeof (szTargetClass) + 1];

  if (!GetClassName (hWnd, class, sizeof (szTargetClass) + 1))
    return 1;

  if (strcmp (class, szTargetClass))
    return 1;

  fnService = (FSERVICE) lParam;

  return (*fnService) (hWnd);
}

static BOOL EnumMdiWindows (FSERVICE fnService)
{
  return EnumChildWindows (hWndMdiClient, EnumChildProc, (LPARAM) fnService);
}

static void target_menu_update (BOOL enable)
{
  HMENU hMenu = GetMenu (hWndIde);
  UINT flag = (enable) ? MF_ENABLED : MF_GRAYED;

  EnableMenuItem (hMenu, IDM_ACTION_MAKEALL, flag);
  EnableMenuItem (hMenu, IDM_TARGET_MAKE, flag);
  EnableMenuItem (hMenu, IDM_TARGET_RUN, flag);
  EnableMenuItem (hMenu, IDM_TARGET_DEBUG, flag);
  EnableMenuItem (hMenu, IDM_TARGET_REMOVE, flag);
  EnableMenuItem (hMenu, IDM_TARGET_RENAME, flag);
  EnableMenuItem (hMenu, IDM_TARGET_REMAKE, flag);
  EnableMenuItem (hMenu, IDM_TARGET_DEPS, flag);
  EnableMenuItem (hMenu, IDM_OPTION_MAKE, flag);
  EnableMenuItem (hMenu, IDM_OPTION_RUN, flag);
  EnableMenuItem (hMenu, IDM_OPTION_DEBUG, flag);
  EnableMenuItem (hMenu, IDM_OPTION_TARGET, flag);

  button_target_menu_update (enable);
}

static BOOL run_batch (char *basecmd,...)
{
  char command[512];
  va_list arg_ptr;
  char *next_arg;

  strcpy (command, basecmd);

  va_start (arg_ptr, basecmd);
  for (;;)
    {
      next_arg = va_arg (arg_ptr, char *);
      if (!next_arg)
        break;
      strcat (command, " ");
      strcat (command, next_arg);
    }
  va_end (arg_ptr);

  SendMessage (hWndMdiClient, WM_MDIACTIVATE, (WPARAM) hWndCompileFrame, 0);
  SetWindowText (hWndCompileFrame, command);

  ListBox_ResetContent (hWndCompileListBox);

  if (win32s)
    return run_cmd_win32s (command, hWndCompileListBox, hWndIde, szProjectDir);
  else
    return run_cmd_win32 (command, hWndCompileListBox, hWndIde, szProjectDir);
}

static int run_process (LPSTR lpszCmdLine)
{
  STARTUPINFO si;
  PROCESS_INFORMATION pinfo;
  int ret;
  
  memset (&si, 0, sizeof (STARTUPINFO));
  si.cb = sizeof (STARTUPINFO);

  ret = CreateProcess (NULL, lpszCmdLine, NULL, NULL,
                          FALSE, 0, NULL, szProjectDir, &si, &pinfo);

  CloseHandle (pinfo.hProcess);
  CloseHandle (pinfo.hThread);
  return ret;
}

static int run_process_detached (LPSTR lpszCmdLine)
{
  STARTUPINFO si;
  PROCESS_INFORMATION pinfo;
  int ret;
  
  memset (&si, 0, sizeof (STARTUPINFO));
  si.cb = sizeof (STARTUPINFO);

  ret = CreateProcess (NULL, lpszCmdLine, NULL, NULL,
                          FALSE, DETACHED_PROCESS, NULL, szProjectDir, &si, &pinfo);

  if (ret == TRUE)
  {
    WaitForSingleObject (pinfo.hProcess, INFINITE);
    CloseHandle (pinfo.hProcess);
    CloseHandle (pinfo.hThread);
  }
  return ret;
}

static int test_cmd_process (LPSTR lpszExe)
{
  FILE *f;
  IMAGE_DOS_HEADER idh;
  DWORD pesig;
  IMAGE_FILE_HEADER ifh;
  IMAGE_OPTIONAL_HEADER ioh;
  
  f = fopen (lpszExe, "rb");
  if (!f)
    return -1;
  fread (&idh, sizeof(idh), 1, f);
  if (idh.e_magic == IMAGE_DOS_SIGNATURE)
  {
    fseek (f, idh.e_lfanew, 0);
    fread (&pesig, sizeof(pesig), 1, f);
    if (pesig == IMAGE_NT_SIGNATURE)
    {
      fread (&ifh, sizeof(ifh), 1, f);
      if (ifh.SizeOfOptionalHeader == sizeof(ioh))
      {
        fread (&ioh, sizeof(ioh), 1, f);
        fclose (f);
        return (ioh.Subsystem == IMAGE_SUBSYSTEM_WINDOWS_CUI) ? 0 : -1;
      }
    }
  }
  fclose (f);
  return -1;
}

// treeview part

static int iImageIndex[NUM_BITMAPS];
enum { idxOpen = 0, idxClose, idxDoc};

static HTREEITEM FindRootItem (HWND hTreeWnd, char *pszExt)
{
  TV_ITEM tvi;
  TV_INSERTSTRUCT tvins;
  char buf[80];

  // find root
  HTREEITEM hti = TreeView_GetChild (hTreeWnd, NULL);

  if (hti != NULL)
    do
      {
        tvi.hItem = hti;
        tvi.mask = TVIF_PARAM | TVIF_TEXT;
        tvi.pszText = buf;
        tvi.cchTextMax = sizeof (buf);
        if (TreeView_GetItem (hTreeWnd, &tvi) == FALSE)
          break;
        if (tvi.lParam && strcmp (pszExt, (char *) tvi.lParam) == 0)
          return hti;
        hti = TreeView_GetNextSibling (hTreeWnd, hti);
      }
    while (hti != NULL);

  // not found insert root
  strcpy (buf, pszExt);
  strupr (buf);
  strcat (buf, "-Files");
  tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_STATE;
  tvi.state = TVIS_EXPANDED | TVIS_BOLD;
  tvi.stateMask = TVIS_EXPANDED | TVIS_BOLD;
  tvi.pszText = buf;
  tvi.cchTextMax = lstrlen (buf);
  tvi.iImage = iImageIndex[idxOpen];
  tvi.iSelectedImage = iImageIndex[idxOpen];
  tvi.lParam = (LPARAM) pszExt;

  tvins.U1(item) = tvi;
  tvins.hInsertAfter = TVI_SORT;
  tvins.hParent = TVI_ROOT;

  return TreeView_InsertItem (hTreeWnd, &tvins);
}

static HTREEITEM AddItemToTree (HWND hTreeWnd, LPSTR lpszItem, char *pszExt)
{
  TV_ITEM tvi;
  TV_INSERTSTRUCT tvins;

  tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_STATE;
  tvi.state = TVIS_EXPANDED | TVIS_BOLD;
  tvi.stateMask = TVIS_EXPANDED;
  tvi.pszText = lpszItem;
  tvi.cchTextMax = lstrlen (lpszItem);
  tvi.iImage = iImageIndex[idxDoc];
  tvi.iSelectedImage = iImageIndex[idxDoc];
  tvi.lParam = 0L;

  tvins.U1(item) = tvi;
  tvins.hInsertAfter = TVI_SORT;
  tvins.hParent = FindRootItem (hTreeWnd, pszExt);

  return TreeView_InsertItem (hTreeWnd, &tvins);
}

static void DeleteTreeItem (HWND hTreeWnd, HTREEITEM hItemSelected)
{
  TV_ITEM tvi;
  char buf[260];

  tvi.hItem = hItemSelected;
  tvi.mask = TVIF_PARAM | TVIF_TEXT;
  tvi.pszText = buf;
  tvi.cchTextMax = sizeof (buf);

  if (TreeView_GetItem (hTreeWnd, &tvi) == FALSE)
    return;

  if (tvi.lParam == 0)
    {
      tvi.hItem = TreeView_GetParent (hTreeWnd, hItemSelected);
      tvi.mask = TVIF_CHILDREN;
      TreeView_DeleteItem (hTreeWnd, hItemSelected);
      if (TreeView_GetItem (hTreeWnd, &tvi) == FALSE)
        return;
      if (tvi.cChildren == 0)
        TreeView_DeleteItem (hTreeWnd, tvi.hItem);
    }
}

static BOOL InitTreeViewImageLists (HWND hTreeWnd)
{
  HIMAGELIST himl;              // handle of image list 

  HBITMAP hbmp;                 // handle of bitmap 

  // Create the image list. 
  if ((himl = ImageList_Create (CX_BITMAP, CY_BITMAP,
                                FALSE, NUM_BITMAPS, 0)) == NULL)
    return FALSE;

  // Add the open file, closed file, and document bitmaps. 
  hbmp = LoadBitmap (hInstance, MAKEINTRESOURCE (IDB_OPEN_FILE));
  iImageIndex[idxOpen] = ImageList_Add (himl, hbmp, (HBITMAP) NULL);
  DeleteObject (hbmp);

  hbmp = LoadBitmap (hInstance, MAKEINTRESOURCE (IDB_CLOSED_FILE));
  iImageIndex[idxClose] = ImageList_Add (himl, hbmp, (HBITMAP) NULL);
  DeleteObject (hbmp);

  hbmp = LoadBitmap (hInstance, MAKEINTRESOURCE (IDB_DOCUMENT));
  iImageIndex[idxDoc] = ImageList_Add (himl, hbmp, (HBITMAP) NULL);
  DeleteObject (hbmp);

  // Fail if not all of the images were added. 
  if (ImageList_GetImageCount (himl) < 3)
    return FALSE;

  // Associate the image list with the tree-view control. 
  TreeView_SetImageList (hTreeWnd, himl, TVSIL_NORMAL);

  return TRUE;
}

// targets

static BOOL target_create_window (struct target *target, int x, int y, int cx, int cy)
{
  MDICREATESTRUCT mcs;
  RECT Rect;
  char title[MAX_PATH];

  strcpy (title, target -> szTargetName);
  strcat (title, "  ");
  strcat (title, target_desc[target -> type].title);

  mcs.szTitle = title;
  mcs.szClass = szTargetClass;
  mcs.hOwner = hInstance;
  mcs.x = x;
  mcs.y = y;
  mcs.cx = cx;
  mcs.cy = cy;
  mcs.style = 0;

  target -> hWndTarget = FORWARD_WM_MDICREATE (hWndMdiClient, &mcs, SendMessage);
  if (!target -> hWndTarget)
    {
      MessageBoxError ("Can't create MDI Window");
      free (target);
      return FALSE;
    }
  SetWindowLong (target -> hWndTarget, 0, (LONG) target);       /* save pointer */

  ShowWindow (target -> hWndTarget, SW_SHOW);

  GetClientRect (target -> hWndTarget, &Rect);

  target -> hWndTargetTreeView = CreateWindowEx (
                                                  0, WC_TREEVIEW,
                                                  "TreeView",
                                                  TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT |
                                                  WS_VISIBLE | WS_VSCROLL | WS_CHILD,
                                             0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top,
                                                  target -> hWndTarget,
                                                  (HMENU) IDC_LIST /* idc_window++ */ ,
                                                  hInstance,
                                                  NULL);

  InitTreeViewImageLists (target -> hWndTargetTreeView);

  return TRUE;
}

static BOOL target_create_new (void)
{
  struct target *target;
  char *name;
  int retval;

  target = (struct target *) malloc (sizeof (struct target)); 
  if (!target)
    {
      MessageBoxError ("Create Target: Out of memory");
      free (target);
      return FALSE;
    }
  memset (target, 0, sizeof (struct target));
  target->flags.s.string_options = STRING_OPTIONS;

  name = szProjectName + strlen (szProjectName);
  while (name > szProjectName && *name != '\\')
    --name;
  strcpy (target -> szTargetName, name + 1);

  name = target -> szTargetName + strlen (target -> szTargetName);
  while (name > target -> szTargetName && *name != '.')
    --name;
  strcpy (name, ".exe");

  retval = DialogBoxParam (hInstance, "TARGET", hWndIde, DialogTarget,
                           (LPARAM) target);

  if (retval == -1 || retval == FALSE)
    {                                  /* Error or Cancel */
      free (target);
      return FALSE;
    }

  target_create_window (target, CW_USEDEFAULT, CW_USEDEFAULT,
                        CW_USEDEFAULT, CW_USEDEFAULT);

  return TRUE;
}

static struct target *target_getdata (void)
{
  static HWND hWndLast;         /* last target window */
  HWND hWndActive;
  struct target *target;

  hWndActive = FORWARD_WM_MDIGETACTIVE (hWndMdiClient, SendMessage);

  if (hWndActive == hWndCompileFrame)
    {
      if (hWndLast && IsWindow (hWndLast))
        hWndActive = hWndLast;
      else
        {
          FORWARD_WM_MDINEXT (hWndMdiClient, hWndActive, TRUE, SendMessage);
          hWndActive = FORWARD_WM_MDIGETACTIVE (hWndMdiClient, SendMessage);
        }
    }

  target = (struct target *) GetWindowLong (hWndActive, 0);

  if (hWndActive != target -> hWndTarget)
    MessageBoxError ("Cannot find target window");

  hWndLast = hWndActive;
  return target;
}

static BOOL target_rename ()
{
  struct target *target = target_getdata ();

  if (!target)
    return FALSE;

  if (DialogBoxParam (hInstance, "TARGET", hWndIde, DialogTarget, (LPARAM) target) != TRUE)
    return FALSE;
  else
    {
      char title[260];
      strcpy (title, target -> szTargetName);
      strcat (title, "  ");
      strcat (title, target_desc[target -> type].title);
      SetWindowText (target -> hWndTarget, title);
      return TRUE;
    }
}

static void build_command (char *src, char *dst, char *desc, char *command)
{
  char *d, *c;

  d = desc;
  c = command;

  while (*d != 0)
    {
      if (*d == '%')
        {
          ++d;
          if (*d == 'f')
            {
              strcpy (c, src);
              c += strlen (src);
            }
          else if (*d == 't')
            {
              strcpy (c, dst);
              c += strlen (dst);
            }
          else
            MessageBoxError (desc);
          ++d;
        }
      else
        *c++ = *d++;
    }
  *c = 0;
}

static void write_tokens (char *str, char *prefix, FILE * stream)
{
  char pszTmp[200];
  char *p;

  strcpy (pszTmp, str);
  p = strtok (pszTmp, ";, ");
  while (p != NULL)
    {
      fputs (" ", stream);
      fputs (prefix, stream);
      fputs (p, stream);
      fputs (" ", stream);
      p = strtok (NULL, ";, ");
    }
}

static void write_cc_options (struct target *target, FILE * stream)
{
  if (target -> flags.s.gcc_pipe)
    fputs ("-pipe ", stream);
  if (target -> flags.s.cpp_nostdinc)
    fputs ("-nostdinc ", stream);
  if (target -> flags.s.cpp_include)
    write_tokens (target -> flags.s.cpp_include, "-I", stream);
  if (target -> flags.s.cpp_macros)
    write_tokens (target -> flags.s.cpp_macros, "-D", stream);
  if (target -> flags.s.cpp_umacros)
    write_tokens (target -> flags.s.cpp_umacros, "-U", stream);
  if (target -> flags.s.cpp_incfile)
    write_tokens (target -> flags.s.cpp_incfile, "-include ", stream);
  if (target -> flags.s.cpp_incmac)
    write_tokens (target -> flags.s.cpp_incmac, "-imacros ", stream);
  if (target -> flags.s.cpp_other)
    {
      fputs ("-Wp,", stream);
      fputs (target -> flags.s.cpp_other, stream);
      fputs (" ", stream);
    }

  fputs ((target -> flags.s.cc1_opt == opt_l1) ? "-O1 " :
         (target -> flags.s.cc1_opt == opt_l2) ? "-O2 " :
         (target -> flags.s.cc1_opt == opt_l3) ? "-O3 " : "", stream);
  fputs ((target -> flags.s.cc1_warnings == warn_none) ? "-w " :
         (target -> flags.s.cc1_warnings == warn_extra) ? "-Wall -W " : "-Wall ", stream);
  fputs ((target -> flags.s.cc1_style == style_ansi) ? "-ansi " :
         (target -> flags.s.cc1_style == style_traditional) ? "-traditional " : "", stream);
  if (target -> flags.s.cc1_486)
    fputs ("-m486 ", stream);
  if (target -> flags.s.cc1_ebp)
    fputs ("-fomit-frame-pointer ", stream);
  if (target -> flags.s.cc1_pedantic)
    fputs ("-pedantic ", stream);
  if (target -> flags.s.cc1_error)
    fputs ("-Werror ", stream);
  if (target -> flags.s.cc1_sigchar)
    fputs ("-fsigned-char ", stream);
  if (target -> flags.s.cc1_unsigbit)
    fputs ("-funsigned-bitfields ", stream);
  if (target -> flags.s.cc1_writestr)
    fputs ("-fwritable-strings ", stream);
  if (target -> flags.s.cc1_other)
    fputs (target -> flags.s.cc1_other, stream);
}

static void makefile_include_deps(FILE * stream)
{
  FILE * stream_dep = fopen (szDepMakefile, "rt");

  if (stream_dep)
  {
    int c;
    while ((c = fgetc(stream_dep)) != EOF)
      fputc(c, stream);
    fclose (stream_dep);
  }
}

static void target_write_makefile (struct target *target, FILE * stream, int iNumTarget)
{
  int i, e;
  char *s, *ext, *resfile = NULL, *deffile = NULL;
  char cc_macro[16];
  char cflags_macro[20];

  sprintf (cc_macro, "CC_TARGET_%02d", iNumTarget);
  sprintf (cflags_macro, "CFLAGS_TARGET_%02d", iNumTarget);

  fputs (cc_macro, stream);
  fputs ("=", stream);

  if (target -> type == type_win32 || target -> type == type_dll)
    {
      fputs ("$(WIN32_FLAG) ", stream);
      if (target -> type == type_dll)
        fputs ("$(DLL_FLAG) ", stream);

      if (target -> flags.s.gcc_runtime == rt_crtdll)
        fputs ("$(CRT_FLAG) ", stream);
      else if (target -> flags.s.gcc_runtime == rt_norte)
        fputs ("$(NRT_FLAG) ", stream);
      else if (target -> flags.s.gcc_runtime == rt_sys)
      {
        fputs ("$(SYS_FLAG) ", stream);
        if (target -> type == type_dll)
          fputs ("$(SO_FLAG) ", stream);
      }
    }
  else if (target -> type == type_rsx)
    fputs ("$(RSX32_FLAG) ", stream);
  else if (target -> type == type_lib)
    fputs ("$(WIN32_FLAG) ", stream);

  if (target -> flags.s.gcc_multithread)
    fputs ("$(MT_FLAG) ", stream);
  if (target -> flags.s.gcc_debug)
    fputs ("-g ", stream);
  if (target -> flags.s.gcc_print)
    fputs ("-v ", stream);
  if (target -> flags.s.gcc_other)
    fputs (target -> flags.s.gcc_other, stream);
  fputs ("\n", stream);
  fputs (cflags_macro, stream);
  fputs ("=", stream);
  write_cc_options (target, stream);
  fputs ("\n\n", stream);

  if (target -> type == type_dll)      // call makelib for import lib

    {
      char libname[_MAX_PATH];
      strcpy (libname, target -> szTargetName);
      strcpy (strrchr (libname, '.'), ".a");

      fputs (libname, stream);
      fputs (": ", stream);
      fputs (target -> szTargetName, stream);
      fputs ("\n\t$(IMP) ", stream);
      fputs (target -> szTargetName, stream);
      fputs (" -o ", stream);
      fputs (libname, stream);
      fputs ("\n\n", stream);
    }

  /* target: .exe .dll .a */
  fputs (target -> szTargetName, stream);
  fputs (":", stream);
  for (i = 0; i < target -> nfiles; i++)
    {
      fputs (" ", stream);
      fputs (target -> objectfiles[i], stream);
    }
  fputs ("\n\t", stream);

  /* command for target */
  if (target -> type == type_lib)
    {
      fputs ("$(AR) -r ", stream);
    }
  else
    {
      fputs ("$(LD) $(", stream);
      fputs (cc_macro, stream);
      fputs (") ", stream);
      if (!target -> flags.s.gcc_debug)
        fputs ("-s ", stream);
      if (target -> flags.s.ld_nostdo)
        fputs ("-nostartfiles ", stream);
      if (target -> flags.s.ld_nostdlib)
        fputs ("-nodefaultlibs ", stream);
      if (target -> flags.s.ld_ldir)
        write_tokens (target -> flags.s.ld_ldir, "-L", stream);
      if (target -> flags.s.ld_other)
        {
          fputs ("-Wl,", stream);
          fputs (target -> flags.s.gcc_other, stream);
          fputs (" ", stream);
        }
      fputs (" -o ", stream);
    }
  fputs (target -> szTargetName, stream);

  for (i = 0; i < target -> nfiles; i++)
    {
      s = target -> objectfiles[i];

      if ((ext = strrchr (s, '.')) == NULL)
        break;
      else
        ++ext;

      if (stricmp (ext, "O") == 0)
        {
          fputs (" ", stream);
          fputs (s, stream);
        }
      else if (stricmp (ext, "DEF") == 0)
        deffile = s;
      else if (stricmp (ext, "RES") == 0)
        resfile = s;

    }

  // libraries at end
  for (i = 0; i < target -> nfiles; i++)
    {
      s = target -> objectfiles[i];

      if ((ext = strrchr (s, '.')) == NULL)
        break;
      else
        ++ext;

      if (stricmp (ext, "A") == 0)
        {
          fputs (" ", stream);
          fputs (s, stream);
        }
    }

  if (deffile && (target -> type == type_win32 || target -> type == type_dll))
    {
      fputs (" ", stream);
      fputs (deffile, stream);
    }

  if (target -> flags.s.ld_libs && target -> flags.s.ld_libs[0])
    write_tokens (target -> flags.s.ld_libs, "-l", stream);

  if (resfile && (target -> type == type_win32 || target -> type == type_dll))
    {
      char command[512];
      for (e = 0; e < nObjects; ++e)
        if (stricmp (obj_desc[e].src_ext, "RES") == 0)
          {
            build_command (resfile, target -> szTargetName, obj_desc[e].command, command);
            fputs ("\n\t", stream);
            fputs (command, stream);
            break;
          }
    }
  if (target -> flags.s.second_link_cmd)
  {
    fputs ("\n\t", stream);
    fputs (target -> flags.s.second_link_cmd, stream);
  }

  fputs ("\n\n", stream);

  for (i = 0; i < target -> nfiles; i++)
    {

      s = target -> sourcefiles[i];

      if ((ext = strrchr (s, '.')) == NULL)
        break;
      else
        ++ext;

      for (e = 0; e < nObjects; ++e)
        if (stricmp (obj_desc[e].src_ext, ext) == 0)
          break;
      if (e >= nObjects)               /* should not true */
        continue;

      if (obj_desc[e].dst_ext[0] != '#'         /* no init entry */
          && strcmp (obj_desc[e].dst_ext, obj_desc[e].src_ext) != 0)
        {
          char command[512];

          build_command (s, target -> objectfiles[i],
                         obj_desc[e].command, command);

          fputs (target -> objectfiles[i], stream);
          fputs (": ", stream);
          fputs (s, stream);
          fputs ("\n\t", stream);
          fputs (command, stream);
          if (obj_desc[e].rsxntopt)
            fprintf (stream, " $(%s) ", cc_macro);
          if (strnicmp (obj_desc[e].command, "$(CC)", 3) == 0)
            fprintf (stream, " $(%s)", cflags_macro);
          fputs ("\n\n", stream);
        }
    }
}

static void fputs_makefileheader (FILE * stream)
{
  int i;
  fputs ("#\n# This makefile is created by rsxide (release 10/99)\n#\n", stream);
  fputs ("\n.SUFFIXES: .exe .res .a .o .c .cpp .cc .cxx .m .rc .p .f .F .r .y .l .s .S .def .h\n\n", stream);
  for (i = 0; i < iMacros; ++i)
    fprintf (stream, "%s\n", pszMacros[i]);
  fputs ("\n\n", stream);
}

static BOOL target_make (void)
{
  struct target *target = target_getdata ();
  FILE *stream;
      
  if (!target)
    return FALSE;

  stream = fopen (szTmpMakefile, "wt");
  if (!stream)
    {
      MessageBoxError ("Cannot creat makefile");
      return FALSE;
    }
  fputs_makefileheader (stream);
  fputs ("all: ", stream);
  fputs (target -> szTargetName, stream);
  fputs ("\n\n", stream);
  target_write_makefile (target, stream, 1);
  makefile_include_deps(stream);
  fclose (stream);

  return run_batch ("make.exe -f", szTmpMakefile, runopt.opt_make, NULL);
}

static BOOL service_makeall_targetnames (HWND hWnd)
{
  struct target *target = (struct target *) GetWindowLong (hWnd, 0);
  FILE *stream;

  if (!target)
    return 1;

  stream = fopen (szTmpMakefile, "at");
  if (!stream)
    {
      MessageBoxError ("cannot open makefile");
      return FALSE;
    }
  fputs (" ", stream);
  fputs (target -> szTargetName, stream);
  fclose (stream);

  return TRUE;
}

static int iTarget;

static BOOL service_makeall_targetcmds (HWND hWnd)
{
  struct target *target = (struct target *) GetWindowLong (hWnd, 0);
  FILE *stream;

  if (!target)
    return 1;

  stream = fopen (szTmpMakefile, "at");
  if (!stream)
    {
      MessageBoxError ("cannot open makefile");
      return FALSE;
    }
  target_write_makefile (target, stream, iTarget++);
  fclose (stream);

  return TRUE;
}

static BOOL target_makeall (void)
{
  FILE *stream;

  /* zero makefile */
  stream = fopen (szTmpMakefile, "wt");
  if (!stream)
    {
      MessageBoxError ("Cannot creat makefile");
      return FALSE;
    }
  fputs_makefileheader (stream);
  fputs ("all:", stream);
  fclose (stream);

  /* generate all: list */
  EnumMdiWindows (service_makeall_targetnames);

  stream = fopen (szTmpMakefile, "at");
  fputs ("\n\n", stream);
  fclose (stream);

  /* generate makefile */
  iTarget = 1;
  EnumMdiWindows (service_makeall_targetcmds);

  stream = fopen (szTmpMakefile, "at");
  makefile_include_deps(stream);
  fclose (stream);
  
  return run_batch ("make.exe -f", szTmpMakefile, runopt.opt_make, "all", NULL);
}

static void build_tokens (char *str, char *prefix, char * buffer)
{
  char pszTmp[200];
  char *p;

  strcpy (pszTmp, str);
  p = strtok (pszTmp, ";, ");
  while (p != NULL)
    {
      buffer = strcpy (buffer, prefix);
      buffer += strlen (prefix);
      buffer = strcpy (buffer, p);
      buffer += strlen (p);
      * buffer = ' ';
      ++buffer;
      p = strtok (NULL, ";, ");
    }
  * buffer = '\0';
}

static BOOL service_deps (HWND hWnd)
{
  struct target *target = (struct target *) GetWindowLong (hWnd, 0);
  FILE * stream, * stream_copy;
  int i;
  const char * tmpfile = "tmp.dep";
  char buf[260];

  if (!target)
    return FALSE;

  if (target -> nfiles == 0)
  {
    MessageBoxError ("no source files");
    return FALSE;
  }

  stream = fopen (szDepMakefile, "at");
  if (!stream)
    return FALSE;

  if (target -> flags.s.cpp_include)
    build_tokens (target -> flags.s.cpp_include, "-I", buf);
  else
    buf[0] = 0;
    
  for (i = 0; i < target -> nfiles; i++)
    {
      int e, c;
      char *s;
      char cmd[260];
      
      s = strrchr (target -> sourcefiles[i], '.') + 1;      
      for (e = 0; e < nObjects; ++e)
        if (stricmp (obj_desc[e].src_ext, s) == 0)
          break;
      if (e >= nObjects)
        continue;
      if (stricmp (obj_desc[e].dst_ext, "o") != 0)
        continue;

      strcpy (cmd, "cpp ");
      strcat (cmd, buf);
      strcat (cmd, target -> sourcefiles[i]);
      strcat (cmd, " -M -MD ");
      strcat (cmd, tmpfile);
      
      CompileListBox_AddString(cmd);
      run_process_detached (cmd);
      
      stream_copy = fopen (tmpfile, "rt");
      if (stream_copy)
      {
        char file[260];
        char * base;
        fscanf(stream_copy, "%s", file);
        base = strrchr (file, '/');
        fputs(base ? base + 1 : file, stream);
        while ((c = fgetc(stream_copy)) != EOF)
          fputc(c, stream);
      }
      fclose (stream_copy);
    }
  fclose (stream);
  unlink (tmpfile);
  return TRUE;
}

static void target_deps (void)
{
  FILE * stream = fopen (szDepMakefile, "wt");
  fputs ("#\n# This dependencies file is created by rsxide\n#\n", stream);
  fclose (stream);
  ListBox_ResetContent (hWndCompileListBox);
  ListBox_SetCurSel(hWndCompileListBox, 0);
  EnumMdiWindows (service_deps);
}

static BOOL target_run (void)
{
  struct target *target = target_getdata ();
  char cmd[MAX_PATH];

  if (!target)
    return FALSE;

  if (target -> type == type_dll)
    {
      MessageBoxError ("You cannot run a DLL");
      return FALSE;
    }
  else if (target -> type == type_lib)
    {
      MessageBoxError ("You cannot run a Library");
      return FALSE;
    }

  if (test_cmd_process (target -> szTargetName) < 0)
    cmd [0] = 0;
  else
  {
    GetModuleFileName (NULL, cmd, sizeof(cmd));
    strcpy (strrchr(cmd, '\\') + 1, "runcon.exe");
    strcat (cmd, " ");
  }
  strcat (cmd, szProjectDir);
  strcat (cmd, "\\");
  strcat (cmd, target -> szTargetName);

  if (*runopt.opt_run)
    {
      strcat (cmd, " ");
      strcat (cmd, runopt.opt_run);
    }
  if (run_process (cmd))
    return TRUE;
  else
    {
      MessageBoxError (target -> szTargetName);
      return FALSE;
    }
}

static BOOL target_debug (void)
{
  char cmd[MAX_PATH];
  struct target *target = target_getdata ();

  if (!target)
    return FALSE;

  if (target -> type == type_dll)
    {
      MessageBoxError ("You cannot debug a DLL");
      return 0;
    }
  else if (target -> type == type_lib)
    {
      MessageBoxError ("You cannot debug a Library");
      return TRUE;
    }

  strcpy (cmd, "gdb ");
  if (*runopt.opt_debug)
    {
      strcpy (cmd, runopt.opt_debug);
      strcpy (cmd, " ");
    }
  strcat (cmd, target -> szTargetName);
  if (run_process (cmd))
    return TRUE;
  else
    return FALSE;
}

static BOOL target_remove (void)
{
  struct target *target = target_getdata ();

  if (!target)
    return FALSE;

  if (FORWARD_WM_QUERYENDSESSION (target -> hWndTarget, SendMessage))
    FORWARD_WM_MDIDESTROY (hWndMdiClient, target -> hWndTarget, SendMessage);

  return TRUE;
}

static BOOL target_flags (void)
{
  struct target *target = target_getdata ();
  PROPSHEETPAGE psp[4];
  PROPSHEETHEADER psh;
  char title[MAX_PATH];

  if (!target)
    return FALSE;

  psp[0].dwSize = sizeof (PROPSHEETPAGE);
  psp[0].dwFlags = 0;
  psp[0].hInstance = hInstance;
  psp[0].U1(pszTemplate) = "GCC_OPT";
  psp[0].U2(pszIcon) = NULL;
  psp[0].pfnDlgProc = DialogTargetGCCFlags;
  psp[0].pszTitle = NULL;
  psp[0].lParam = (LPARAM) (target);
  psp[0].pfnCallback = NULL;

  psp[1].dwSize = sizeof (PROPSHEETPAGE);
  psp[1].dwFlags = 0;
  psp[1].hInstance = hInstance;
  psp[1].U1(pszTemplate) = "CPP_OPT";
  psp[1].U2(pszIcon) = NULL;
  psp[1].pfnDlgProc = DialogTargetCPPFlags;
  psp[1].pszTitle = NULL;
  psp[1].lParam = (LPARAM) (target);
  psp[1].pfnCallback = NULL;

  psp[2].dwSize = sizeof (PROPSHEETPAGE);
  psp[2].dwFlags = 0;
  psp[2].hInstance = hInstance;
  psp[2].U1(pszTemplate) = "CC_OPT";
  psp[2].U2(pszIcon) = NULL;
  psp[2].pfnDlgProc = DialogTargetCCFlags;
  psp[2].pszTitle = NULL;
  psp[2].lParam = (LPARAM) (target);
  psp[2].pfnCallback = NULL;

  psp[3].dwSize = sizeof (PROPSHEETPAGE);
  psp[3].dwFlags = 0;
  psp[3].hInstance = hInstance;
  psp[3].U1(pszTemplate) = "LD_OPT";
  psp[3].U2(pszIcon) = NULL;
  psp[3].pfnDlgProc = DialogTargetLDFlags;
  psp[3].pszTitle = NULL;
  psp[3].lParam = (LPARAM) (target);
  psp[3].pfnCallback = NULL;

  strcpy (title, "Switches for target ");
  strcat (title, target -> szTargetName);
  strcat (title, "  ");
  strcat (title, target_desc[target -> type].title);

  psh.dwSize = sizeof (PROPSHEETHEADER);
  psh.dwFlags = PSH_PROPSHEETPAGE | PSH_NOAPPLYNOW;
  psh.hwndParent = hWndIde;
  psh.hInstance = hInstance;
  psh.U1(pszIcon) = NULL;
  psh.pszCaption = title;
  psh.nPages = sizeof (psp) / sizeof (PROPSHEETPAGE);
  psh.U2(nStartPage) = 0;
  psh.U3(ppsp) = (LPCPROPSHEETPAGE) & psp;
  psh.pfnCallback = NULL;

  if (PropertySheet (&psh) > 0)
  {    
    SetFileSaveStatus (TRUE);
    if (MessageBox(hWndIde, "mark all files for remake?",
                    "options changed", MB_YESNO|MB_ICONQUESTION) == IDYES)
      target_touchall();
  }

  return TRUE;
}

static void target_add_file (struct target *target, char *text, struct obj_desc *obj_desc)
{
  char string[260];
  char *s;

  if (!target -> sourcefiles)
    {
      target -> sourcefiles = (char **) malloc (sizeof (char *));
      target -> objectfiles = (char **) malloc (sizeof (char *));
    }
  else
    {
      target -> sourcefiles = (char **)
        realloc (target -> sourcefiles, (target -> nfiles + 1) * sizeof (char *));
      target -> objectfiles = (char **)
        realloc (target -> objectfiles, (target -> nfiles + 1) * sizeof (char *));
    }
  if (!target -> sourcefiles || !target -> objectfiles)
    {
      MessageBoxError ("Adding files: out of memory");
      return;
    }
  if (obj_desc -> dst_ext[0] != '#')
    {
      // extract filename
      s = strrchr (text, '\\');
      if (s == NULL)
        s = strrchr (text, '/');
      strcpy (string, (s) ? s + 1 : text);
      if ((s = strrchr (string, '.')) != NULL)
        strcpy (s + 1, obj_desc -> dst_ext);
    }
  else
    strcpy (string, text);

  target -> sourcefiles[target -> nfiles] = strdup (text);
  target -> objectfiles[target -> nfiles] = strdup (string);
  target -> nfiles++;

  AddItemToTree (target -> hWndTargetTreeView, text, obj_desc -> src_ext);
}

static void target_delete_file (char * file)
{
  struct target *target = target_getdata ();
  int i;
  int index;
  
  for (index = 0; index < target->nfiles; ++index)
    if (strcmp(target -> sourcefiles[index], file) == 0)
      break;
      
  free (target -> sourcefiles[index]);
  free (target -> objectfiles[index]);

  target -> nfiles--;

  if (target -> nfiles > 0)
    {
      for (i = index; i <= target -> nfiles; i++)
        {
          target -> sourcefiles[i] = target -> sourcefiles[i + 1];
          target -> objectfiles[i] = target -> objectfiles[i + 1];
        }
      target -> sourcefiles =
        realloc (target -> sourcefiles, target -> nfiles * sizeof (char *));
      target -> objectfiles =
        realloc (target -> objectfiles, target -> nfiles * sizeof (char *));
    }
}

static int target_touch_file (char * filename)
{
  HANDLE hf;
  FILETIME ft;
  SYSTEMTIME st;
  DWORD attr;
  char file [260];
  int j;
  
  /* no unix slaches */
  strcpy (file, filename);
  for (j = 0; file[j]; ++j)
    if (file[j] == '/')
      file[j] = '\\';
  
  attr = GetFileAttributes (file);
  if (attr & FILE_ATTRIBUTE_READONLY)
    SetFileAttributes (file, attr & ~FILE_ATTRIBUTE_READONLY);
  
  hf = CreateFile (file, GENERIC_WRITE, 0, NULL,
                   OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

  if (hf == INVALID_HANDLE_VALUE)
    return -1;

  GetSystemTime (&st);
  SystemTimeToFileTime (&st, &ft);
  SetFileTime (hf, NULL, &ft, &ft);
  CloseHandle (hf);

  if (attr & FILE_ATTRIBUTE_READONLY)
    SetFileAttributes (file, attr);

  return 0;
}

static BOOL target_touchall (void)
{
  struct target *target = target_getdata ();
  int i;

  if (!target)
    return FALSE;

  for (i = 0; i < target -> nfiles; i++)
    target_touch_file (target -> sourcefiles[i]);

  return TRUE;
}

/*
   ----- project functions -----
 */

static void project_menu_update (BOOL enable)
{
  HMENU hMenu = GetMenu (hWndIde);
  UINT flag = (enable) ? MF_ENABLED : MF_GRAYED;

  EnableMenuItem (hMenu, IDM_FILE_SAVE, flag);
  EnableMenuItem (hMenu, IDM_FILE_SAVEAS, flag);
  EnableMenuItem (hMenu, IDM_FILE_CLOSE, flag);
  EnableMenuItem (hMenu, IDM_TARGET_NEW, flag);

  button_project_menu_update (enable);
}

static void project_menu_append (LPSTR szName)
{
  int i;
  char env[260];
  HMENU hMenu;

  /* check duplicate entries */
  for (i = 0; i < 4; ++i)
    if (!LastFiles[i][0])
      break;
    else if (stricmp (szName, LastFiles[i]) == 0)
      return;

  hMenu = GetSubMenu (GetMenu (hWndIde), 0);

  for (i = 0; i < 4; ++i)
    RemoveMenu (hMenu, IDM_FILE_FILE1 + i, MF_BYCOMMAND);

  for (i = 3; i > 0; --i)
    strcpy (LastFiles[i], LastFiles[i - 1]);
  strcpy (LastFiles[0], szName);

  for (i = 0; i < 4; ++i)
    {
      if (LastFiles[i][0])
        {
          env[0] = '&';
          env[1] = '1' + i;
          env[2] = ' ';
          env[3] = 0;
          strcat (env, LastFiles[i]);
          AppendMenu (hMenu, MF_ENABLED, IDM_FILE_FILE1 + i, env);
        }
    }
}

static void project_windowtext (void)
{
  char text[512];

  strcpy (text, szAppTitle);
  strcat (text, "  [");
  strcat (text, szProjectName);
  strcat (text, "]");
  strlwr (text + sizeof (szAppTitle));

  SetWindowText (hWndIde, text);
}

static BOOL project_opendlg (int mode)
{
  char *s;

  if (mode == 0)
    {
      s = "New Project";
      strcpy (szProjectNext, "New.irs");
    }
  else
    {
      s = "Open Project";
      szProjectNext[0] = '\0';
    }

  if (CommDlg (hWndIde, szProjectNext, s, mode))
    {
      char *s;

      strlwr (szProjectNext);

      /* set standard Directory Path */
      strcpy (szProjectDir, szProjectNext);
      s = szProjectDir + strlen (szProjectDir);
      while (s > szProjectDir && *--s != '\\')
        ;
      *s = '\0';

      return TRUE;
    }
  else
    return FALSE;
}

/*
   ide file information:
   --------------------
   [head]
   --------------------
   [target_1]
   [file_1][file_2]
   ....
   [target_n]
   [file_1][file_2]
   --------------------
 */

static BOOL service_save (HWND hWnd)
{
  struct target *target = (struct target *) GetWindowLong (hWnd, 0);
  FILE *stream;
  RECT rect, crect;
  int i;
  char **pptr;

  stream = fopen (szProjectName, "a+b");
  if (!stream)
    {
      MessageBoxError ("Cannot open project");
      return FALSE;
    }

  /* save relative position */
  GetWindowRect (hWndMdiClient, &crect);
  GetWindowRect (target -> hWndTarget, &rect);
  rect.left -= crect.left;
  rect.top -= crect.top;
  rect.right -= crect.left;
  rect.bottom -= crect.top;

  fwrite (target -> szTargetName, sizeof (target -> szTargetName), 1, stream);
  fwrite (&target -> flags, sizeof (target -> flags), 1, stream);
  fwrite (&target -> type, sizeof (target -> type), 1, stream);
  fwrite (&target -> nfiles, sizeof (target -> nfiles), 1, stream);
  fwrite (&rect, sizeof (rect), 1, stream);

  pptr = &(target -> flags.s.gcc_other);
  for (i = 0; i < target->flags.s.string_options; i++, ++pptr)
    {
      if (*pptr)
        fwrite (*pptr, 1, strlen (*pptr) + 1, stream);
      else
        fwrite ("", 1, 1, stream);
    }
  for (i = 0; i < target -> nfiles; i++)
    fwrite (target -> sourcefiles[i], strlen (target -> sourcefiles[i]) + 1,
            1, stream);
  fclose (stream);

  return TRUE;
}

static BOOL project_save (int nTargets)
{
  FILE *stream;
  struct save_project sp;

  stream = fopen (szProjectName, "wb");
  if (!stream)
    {
      MessageBoxError ("Cannot open project");
      return FALSE;
    }
  strcpy (sp.magic, SAVE_MAGIC);
  sp.nTargets = nTargets;
  sp.nSizeOfTarget = sizeof (struct save_target);

  fwrite (&sp, sizeof (sp), 1, stream);
  fclose (stream);

  EnumMdiWindows (service_save);

  // new: write Ide Window rect
  stream = fopen (szProjectName, "a+b");
  if (stream)
  {
    struct save_size sz;
    RECT crect;
    
    GetWindowRect (hWndIde, & sz.rect);

    /* save relative position of compiler window */
    GetWindowRect (hWndMdiClient, &crect);
    GetWindowRect (hWndCompileFrame, & sz.comprect);
    sz.comprect.left -= crect.left;
    sz.comprect.top -= crect.top;
    sz.comprect.right -= crect.left;
    sz.comprect.bottom -= crect.top;

    strcpy (sz.magic, SAVE_SIZE_MAGIC);
    fwrite (&sz, sizeof (sz), 1, stream);
    fclose (stream);
  }

  project_menu_append (szProjectName);

  return TRUE;
}

static BOOL ServiceClose (HWND hWnd)
{
  HWND hWndParent = GetParent (hWnd);

  FORWARD_WM_MDIRESTORE (hWndParent, hWnd, SendMessage);

  if (!FORWARD_WM_QUERYENDSESSION (hWnd, SendMessage))
    return TRUE;

  FORWARD_WM_MDIDESTROY (hWndParent, hWnd, SendMessage);

  return TRUE;
}

static BOOL project_ask_save (int nTargets)
{
  if (need_save)
    {
      int r = MessageBox (hWndIde, "Save the current project?", "RSXIDE",
                          MB_YESNOCANCEL | MB_ICONQUESTION);

      if (r == IDCANCEL)
        return FALSE;
      else if (r == IDYES)
        {
          project_save (nTargets);
          SetFileSaveStatus (FALSE);
        }
    }
  return TRUE;
}

static BOOL project_close (nTargets)
{
  if (project_ask_save (nTargets) == FALSE)
    return FALSE;

  *szProjectName = '\0';
  SetWindowText (hWndIde, szAppTitle);

  EnumMdiWindows (ServiceClose);

  return TRUE;
}

static int project_read (void)
{
  FILE *stream;
  struct target *target;
  struct save_project sp;
  struct save_size sz;
  int p, i, n;
  RECT rect;
  int version = 0;

  stream = fopen (szProjectName, "rb");
  if (!stream)
    {
      MessageBoxError ("Cannot open project");
      return -1;
    }
  fread (&sp, sizeof (sp), 1, stream);

  if (strcmp (sp.magic, SAVE_MAGIC) == 0)
    version = 2;
  else if (strcmp (sp.magic, SAVE_MAGIC_V1) == 0)
    version = 1;

  if (version == 1)
    MessageBox (hWndIde,
                "Old rsxide project file (1.0) detected\n"
                "You should modify the compiler and linker flags\n",
                "Caution!", MB_OK | MB_ICONINFORMATION);

  if (version == 0 || sp.nSizeOfTarget != sizeof (struct save_target))
    {
      MessageBoxError ("This is not a valid rsxide file\n"
                       "Create a new project file");
      return -1;
    }

  for (p = 0; p < sp.nTargets; p++)
    {
      target = (struct target *) malloc (sizeof (struct target));
      if (!target)
        {
          MessageBoxError ("Create Target: Out of memory");
          free (target);
          return -1;
        }
      fread (target -> szTargetName, sizeof (target -> szTargetName), 1, stream);
      fread (&target -> flags, sizeof (target -> flags), 1, stream);
      fread (&target -> type, sizeof (target -> type), 1, stream);
      fread (&n, sizeof (target -> nfiles), 1, stream);
      fread (&rect, sizeof (rect), 1, stream);

      if (version >= 2)
        {
          int size = 1024;
          char *pszTmp = malloc (size);
          char **pptr = &(target -> flags.s.gcc_other);
          int len;

          for (i = 0; i < target->flags.s.string_options; i++)
            {
              len = 0;
              pszTmp[0] = 0;
              while ((pszTmp[len] = fgetc (stream)) != 0)
                {
                  if (++len >= size)
                    realloc (pszTmp, (size += 1024));
                }
              if (pszTmp[0])
                pptr[i] = strdup (pszTmp);
              else
                pptr[i] = NULL;
            }
          free (pszTmp);
        }
      else if (version == 1)
        {
          char *pszLibs;

          if (target -> type)
            target -> type -= 101;     // old version uses IDD

          pszLibs = (target -> flags._old[5][0])
            ? strdup (target -> flags._old[5])
            : NULL;
          memset (&target -> flags, 0, sizeof (target -> flags));
          target -> flags.s.string_options = STRING_OPTIONS;
          target -> flags.s.ld_libs = pszLibs;
        }

      target -> sourcefiles = 0;
      target -> objectfiles = 0;
      target -> nfiles = 0;

      target_create_window (target, rect.left, rect.top,
                            rect.right - rect.left,
                            rect.bottom - rect.top);

      for (i = 0; i < n; i++)
        {
          char name[260];
          int x = 0;
          char *s = NULL; //make compiler happy
          int e;

          while ((name[x] = fgetc (stream)) != 0)
            {
              if (name[x] == '.')
                s = name + x + 1;
              ++x;
            }

          for (e = 0; e < nObjects; ++e)
            if (stricmp (obj_desc[e].src_ext, s) == 0)
              break;

          if (e < nObjects)
            target_add_file (target, name, obj_desc + e);
        }
    }

  // new: read Ide Window rect    
  fread (&sz, sizeof (sz), 1, stream);
  if (!feof(stream) && strcmp (sz.magic, SAVE_SIZE_MAGIC) == 0)
  {
    MoveWindow (hWndIde, sz.rect.left, sz.rect.top,
                         sz.rect.right - sz.rect.left,
                         sz.rect.bottom - sz.rect.top, TRUE);

    MoveWindow (hWndCompileFrame, sz.comprect.left, sz.comprect.top,
                         sz.comprect.right - sz.comprect.left,
                         sz.comprect.bottom - sz.comprect.top, TRUE);
  }
  fclose (stream);

  return sp.nTargets;
}

static int project_open (BOOL bOpen)
{
  int n;

  project_menu_update (TRUE);

  if (!bOpen)
    {
      if (target_create_new () == TRUE)
        n = 1;
      else
        n = 0;
    }
  else
    n = project_read ();

  return n;
}

static struct dim
{
  int x, y, cx, cy, add;
}
cwin;

static BOOL ServiceCascade (HWND hWnd)
{
  HWND hWndParent = GetParent (hWnd);

  FORWARD_WM_MDIRESTORE (hWndParent, hWnd, SendMessage);

  MoveWindow (hWnd, cwin.x + 2, cwin.y + 2, cwin.cx - 4, cwin.cy - 4, TRUE);
  cwin.x += cwin.add;

  return TRUE;
}

static BOOL project_cascade (int nWindows)
{
  RECT rect_cl;
  int r;

  FORWARD_WM_MDIRESTORE (hWndMdiClient, hWndCompileFrame, SendMessage);

  GetClientRect (hWndMdiClient, &rect_cl);
  r = (rect_cl.bottom - rect_cl.top) / 2;

  MoveWindow (hWndCompileFrame,
              rect_cl.left,
              rect_cl.bottom - r,
              rect_cl.right - rect_cl.left,
              r,
              TRUE);

  if (nWindows > 0)
    {
      if (nWindows == 1)
        nWindows++;
      cwin.x = rect_cl.left;
      cwin.y = rect_cl.top;
      cwin.cx = cwin.add = (rect_cl.right - rect_cl.left) / nWindows;
      cwin.cy = (rect_cl.bottom - rect_cl.top) - r;
      EnumMdiWindows (ServiceCascade);
    }
  return TRUE;
}

/*
   ----- Ide window functions -----
 */

static HWND hWndToolbar;
static HWND hWndStatusbar;

#define CTBE_IMAGES         9
#define CTBE_IMAGEWIDTH     18
#define CTBE_IMAGEHEIGHT    17
#define CTBE_BUTTONWIDTH    0
#define CTBE_BUTTONHEIGHT   0

#define TBI_NEW        0
#define TBI_OPEN       1
#define TBI_SAVE       2
#define TBI_MAKEALL    3
#define TBI_EXPLORER   4
#define TBI_MAKE       5
#define TBI_RUN        6
#define TBI_DEBUG      7
#define TBI_OPTIONS    8

TBBUTTON tbButton[] =
{
  {TBI_NEW, IDM_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON,
   {0, 0}, 0, 0},
  {TBI_OPEN, IDM_FILE_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON,
   {0, 0}, 0, 0},
  {TBI_SAVE, IDM_FILE_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON,
   {0, 0}, 0, 0},
  {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP,
   {0, 0}, 0, 0},
  {TBI_MAKEALL, IDM_ACTION_MAKEALL, TBSTATE_ENABLED, TBSTYLE_BUTTON,
   {0, 0}, 0, 0},
  {TBI_EXPLORER, IDM_ACTION_EXPLORER, TBSTATE_ENABLED, TBSTYLE_BUTTON,
   {0, 0}, 0, 0},
  {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP,
   {0, 0}, 0, 0},
  {TBI_MAKE, IDM_TARGET_MAKE, TBSTATE_ENABLED, TBSTYLE_BUTTON,
   {0, 0}, 0, 0},
  {TBI_RUN, IDM_TARGET_RUN, TBSTATE_ENABLED, TBSTYLE_BUTTON,
   {0, 0}, 0, 0},
  {TBI_DEBUG, IDM_TARGET_DEBUG, TBSTATE_ENABLED, TBSTYLE_BUTTON,
   {0, 0}, 0, 0},
  {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP,
   {0, 0}, 0, 0},
  {TBI_OPTIONS, IDM_OPTION_TARGET, TBSTATE_ENABLED, TBSTYLE_BUTTON,
   {0, 0}, 0, 0},
};

static void button_target_menu_update (BOOL enable)
{
  LPARAM lParam = (enable)
  ? MAKELPARAM (TBSTATE_ENABLED, 0)
  : MAKELPARAM (0, 0);

  SendMessage (hWndToolbar, TB_SETSTATE, IDM_ACTION_MAKEALL, lParam);
  SendMessage (hWndToolbar, TB_SETSTATE, IDM_ACTION_EXPLORE_DIR, lParam);
  SendMessage (hWndToolbar, TB_SETSTATE, IDM_TARGET_MAKE, lParam);
  SendMessage (hWndToolbar, TB_SETSTATE, IDM_TARGET_RUN, lParam);
  SendMessage (hWndToolbar, TB_SETSTATE, IDM_TARGET_DEBUG, lParam);
  SendMessage (hWndToolbar, TB_SETSTATE, IDM_OPTION_TARGET, lParam);
}

static void button_project_menu_update (BOOL enable)
{
  LPARAM lParam = (enable)
  ? MAKELPARAM (TBSTATE_ENABLED, 0)
  : MAKELPARAM (0, 0);

  SendMessage (hWndToolbar, TB_SETSTATE, IDM_FILE_SAVE, lParam);
}

//
// set parts and text of the status bar
//
static char szModified[] = "Project modified";

static void InitStatusBar (HWND hwndParent)
{
  const int cSpaceInBetween = 8;
  int ptArray[3];
  SIZE size;
  RECT rect;
  HDC hDC;

  hDC = GetDC (hwndParent);
  GetClientRect (hwndParent, &rect);

  ptArray[2] = rect.right;

  if (GetTextExtentPoint32 (hDC, szModified, sizeof(szModified) - 1, &size))
    ptArray[1] = ptArray[2] - (size.cx) - cSpaceInBetween;
  else
    ptArray[1] = 0;

  if (GetTextExtentPoint32 (hDC, szModified, sizeof(szModified) - 1, &size))
    ptArray[0] = ptArray[1] - (size.cx) - cSpaceInBetween;
  else
    ptArray[0] = 0;

  ReleaseDC (hwndParent, hDC);

  FORWARD_SB_SETPARTS (hWndStatusbar,
                       sizeof (ptArray) / sizeof (ptArray[0]),
                       ptArray,
                       SendMessage);

  FORWARD_SB_SETTEXT (hWndStatusbar, 0, 0, "Menu Help", SendMessage);
  FORWARD_SB_SETTEXT (hWndStatusbar, 1, 0, "", SendMessage);
  FORWARD_SB_SETTEXT (hWndStatusbar, 2, 0, "", SendMessage);
}

static void SetFileSaveStatus (BOOL value)
{
  need_save = value;
  FORWARD_SB_SETTEXT (hWndStatusbar, 1, 0, need_save ? szModified : "", SendMessage);
}

static BOOL create_compile_window (void)
{
  RECT Rect;
  LONG r;
  MDICREATESTRUCT mdicreate;

  /* Create the Compile Frame */
  GetClientRect (hWndMdiClient, &Rect);
  r = (Rect.bottom - Rect.top) / 2;

  mdicreate.szClass = szCompileClass;
  mdicreate.szTitle = szCompileTitle;
  mdicreate.hOwner = hInstance;
  mdicreate.x = Rect.left;
  mdicreate.y = Rect.bottom - r;
  mdicreate.cx = Rect.right - Rect.left;
  mdicreate.cy = r;
  mdicreate.style = 0;
  mdicreate.lParam = 0;

  hWndCompileFrame = FORWARD_WM_MDICREATE (hWndMdiClient, &mdicreate, SendMessage);

  if (!hWndCompileFrame)
    {
      MessageBoxError ("Cannot create Compile Frame");
      return FALSE;
    }
  ShowWindow (hWndCompileFrame, SW_SHOW);

  /* Create the Compile ListBox */

  GetClientRect (hWndCompileFrame, &Rect);
  hWndCompileListBox =
    CreateWindow (
                   "Listbox",
                   "",
                   (LBS_NOTIFY | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT
                    | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | WS_CHILD),
                   0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top,
                   hWndCompileFrame,
                   (HMENU) IDC_LIST,
                   hInstance,
                   NULL);

  if (!hWndCompileListBox)
    {
      MessageBoxError ("Cannot create Compile ListBox");
      return FALSE;
    }
  else
    {
      HANDLE hFont = GetStockObject (SYSTEM_FIXED_FONT);
      HDC hdc;
      SetWindowFont (hWndCompileListBox, hFont, TRUE);
      hdc = GetDC(hWndCompileListBox);
      GetCharWidth32 (hdc, 'A', 'A', &iCharWidth);
      ReleaseDC(hWndCompileListBox, hdc);
      iListboxMax = Rect.right - Rect.left;
      return TRUE;
    }
}

BOOL Ide_OnCreate (HWND hWnd, LPCREATESTRUCT lpCs)
{
  RECT Rect, rectTool;
  CLIENTCREATESTRUCT ccs;

  // begin of common controls
  InitCommonControls ();

  hWndToolbar = CreateToolbarEx (hWnd,
                                 WS_CHILD | WS_VISIBLE | TBSTYLE_TOOLTIPS,
                                 IDC_TOOLBAR,
                                 CTBE_IMAGES,
                                 hInstance,
                                 IDB_TOOLBAR,
                                 tbButton,
                                 sizeof (tbButton) / sizeof (TBBUTTON),
                                 CTBE_BUTTONWIDTH,
                                 CTBE_BUTTONHEIGHT,
                                 CTBE_IMAGEWIDTH,
                                 CTBE_IMAGEHEIGHT,
                                 sizeof (TBBUTTON)
    );

  if (!hWndToolbar)
    return FALSE;

  hWndStatusbar = CreateStatusWindow (
                                       WS_CHILD | WS_VISIBLE | WS_BORDER,
                                       "Status Bar",
                                       hWnd,
                                       IDC_STATUSBAR
    );

  if (!hWndStatusbar)
    return FALSE;

  InitStatusBar (hWnd);

  // end of common controls

  GetClientRect (hWnd, &Rect);

  GetWindowRect (hWndToolbar, &rectTool);
  Rect.top += (rectTool.top - rectTool.bottom);

  GetWindowRect (hWndStatusbar, &rectTool);
  Rect.bottom -= (rectTool.top - rectTool.bottom);

  /* create mdi client */
  ccs.hWindowMenu = GetSubMenu (GetMenu (hWnd), 5);
  ccs.idFirstChild = IDM_WINDOW_CHILD;

  hWndMdiClient = CreateWindow ("MDICLIENT",
                                NULL, WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
                              Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top,
                                hWnd, 0, hInstance, (LPSTR) & ccs);

  if (!hWndMdiClient)
    {
      MessageBoxError ("Cannot create mdi-client");
      return FALSE;
    }

  read_ini (hWnd);

  return TRUE;
}

void Ide_OnDestroy (HWND hWnd)
{
  connect_editor (FALSE);
  write_ini ();

  PostQuitMessage (0);
}

//
// Notify Event: display tooltops
//
LRESULT Ide_OnNotify (HWND hWnd, int id, LPNMHDR lpNotification)
{
  if (lpNotification -> code == TTN_NEEDTEXT)
    {
      static char szBuffer[64];
      LPTOOLTIPTEXT lpToolTipText;
      lpToolTipText = (LPTOOLTIPTEXT) lpNotification;

      LoadString (hInstance,
                  lpToolTipText -> hdr.idFrom,
                  szBuffer,
                  sizeof (szBuffer));

      lpToolTipText -> lpszText = szBuffer;
    }
  return 0;
}

//
// Size Event: resize also statusbar and toolbar
//
void Ide_OnSize (HWND hWnd, UINT state, int cx, int cy)
{
  FORWARD_WM_SIZE (hWndStatusbar, state, cx, cy, SendMessage);
  FORWARD_WM_SIZE (hWndToolbar, state, cx, cy, SendMessage);

  InitStatusBar (hWnd);

  // Position the MDI client window between the tool and status bars
  if (state != SIZE_MINIMIZED)
    {
      RECT rc, rcClient;

      GetClientRect (hWnd, &rcClient);

      GetWindowRect (hWndToolbar, &rc);
      ScreenToClient (hWnd, (LPPOINT) & rc.right);
      rcClient.top = rc.bottom;

      GetWindowRect (hWndStatusbar, &rc);
      ScreenToClient (hWnd, (LPPOINT) & rc.left);
      rcClient.bottom = rc.top;

      MoveWindow (hWndMdiClient,
                  rcClient.left,
                  rcClient.top,
                  rcClient.right - rcClient.left,
                  rcClient.bottom - rcClient.top,
                  TRUE);
    }
}

//
// Menu Event: set text on status bar
//
void Ide_OnMenuSelect (HWND hWnd, HMENU hMenu, int item,
                       HMENU hMenuPopup, UINT flags)
{
  static UINT idPopup[] =
  {
    IDM_POPUP_FILE,
    IDM_POPUP_ACTION,
    IDM_POPUP_TARGET,
    IDM_POPUP_OPTION,
    IDM_POPUP_IDE,
    IDM_POPUP_WINDOW,
    IDM_POPUP_HELP
  };
  char szBuffer[128];
  UINT nStringID;

  szBuffer[0] = 0;                     // First reset the buffer

  if (flags == 0xffff && hMenu == NULL)         // Menu has been closed

    nStringID = 0;

  else if (flags & MFT_SEPARATOR)      // Ignore separators

    nStringID = 0;

  else if (flags & MF_POPUP)
    {                                  // Popup menu

      if (flags & MF_SYSMENU)          // System menu

        nStringID = 0;
      else
        // Get string ID for popup menu from idPopup array.
        nStringID = ((item < sizeof (idPopup) / sizeof (idPopup[0])) ?
                     idPopup[item] : 0);
    }
  else                                 // Must be a command item

    nStringID = item;                  // String ID == Command ID

  if (0 != nStringID)
    LoadString (hInstance, nStringID, szBuffer, sizeof (szBuffer));

  FORWARD_SB_SETTEXT (hWndStatusbar, 0, 0, szBuffer, SendMessage);
}

void Ide_OnCommand (HWND hWnd, int id, HWND hWndCtl, UINT notify)
{
  HWND hWndChild;
  static int nTargets;
  int ret;
  char *s;

  switch (id)
    {
      case IDM_FILE_FILE1:
      case IDM_FILE_FILE2:
      case IDM_FILE_FILE3:
      case IDM_FILE_FILE4:

      strcpy (szProjectNext, LastFiles[id - IDM_FILE_FILE1]);
      /* set standard Directory Path */
      strcpy (szProjectDir, szProjectNext);
      s = szProjectDir + strlen (szProjectDir);
      while (s > szProjectDir && *--s != '\\')
        ;
      *s = '\0';

      case IDM_FILE_NEW:
      case IDM_FILE_OPEN:

      if (*szProjectName)
      {
        if (project_ask_save (nTargets) == FALSE)
          return;
        else
          SetFileSaveStatus (FALSE);
      }

      if (id == IDM_FILE_NEW || id == IDM_FILE_OPEN)
        if (project_opendlg ((id == IDM_FILE_NEW) ? 0 : 1) == FALSE)
          return;

      if (*szProjectName)
        {
          if (project_close (nTargets) == TRUE)
            {
              nTargets = 0;
              project_menu_update (FALSE);
              target_menu_update (FALSE);
              *szProjectName = 0;
            }
          else
            return;
        }
      strcpy (szProjectName, szProjectNext);

      /* fall through */

      case IDM_FILE_CMDOPEN:

      if (id != IDM_FILE_NEW)
        project_menu_append (szProjectName);

      SetCurrentDirectory (szProjectDir);

      project_windowtext ();

      project_menu_update (TRUE);

      nTargets = (project_open ((id == IDM_FILE_NEW) ? 0 : 1));

      if (nTargets >= 0)
        {
          target_menu_update (TRUE);
          if (id == IDM_FILE_NEW)
            project_cascade (nTargets);
        }

      if (id == IDM_FILE_NEW)
        SetFileSaveStatus (TRUE);

      return;

      case IDM_FILE_SAVE:
        if (*szProjectName)
        {
          project_save (nTargets);
          SetFileSaveStatus (FALSE);
        }
      return;

      case IDM_FILE_SAVEAS:
        if (*szProjectName)
        if (CommDlg (hWndIde, szProjectName, "Save As Project File", 2))
          {
            project_windowtext ();
            project_save (nTargets);
            SetFileSaveStatus (FALSE);
          }
      return;

      case IDM_FILE_CLOSE:
        if (project_close (nTargets) == TRUE)
        {
          nTargets = 0;
          project_menu_update (FALSE);
          target_menu_update (FALSE);
          *szProjectName = 0;
        }
      return;

      case IDM_FILE_EXIT:
        if (project_close (nTargets) == TRUE)
        FORWARD_WM_CLOSE (hWndIde, SendMessage);
      return;

      case IDM_ACTION_MAKEALL:
        if (makefile_used == TRUE)
        MessageBoxError ("Makefile is used, wait");
      else
        {
          makefile_used = TRUE;
          makefile_used = target_makeall ();
        }
      return;

      case IDM_ACTION_RUN:
        ret = DialogBoxParam (hInstance, "INPUT", hWnd,
                              DialogInput, (LPARAM) "Type Application to run");
      if (ret)
        run_process ((char *) ret);
      return;

      case IDM_ACTION_RUNBATCH:
        ret = DialogBoxParam (hInstance, "INPUT", hWnd,
                              DialogInput, (LPARAM) "Type Application to run");
      if (ret)
        run_batch ((char *) ret, NULL);
      return;

      case IDM_ACTION_EDIT:
        ret = DialogBoxParam (hInstance, "INPUT", hWnd,
                              DialogInput, (LPARAM) "Type Editor File");
      if (ret)
        {
          connect_editor (TRUE);
          EditDdeFileOpen (szProjectDir, (char *) ret);
        }
      return;

      case IDM_ACTION_EXPLORE_DIR:
        if (winv3x)
          run_process ("winfile");
        else
          run_process ("explorer .");
        return;

      case IDM_ACTION_EXPLORER:
        if (winv3x)
          run_process ("winfile");
        else {
          char buf[260];
          strcpy (buf, "explorer /e,");
          strcat (buf, szProjectDir);
          run_process (buf);
        }
        return;

      case IDM_TARGET_MAKE:
        if (makefile_used == TRUE)
        MessageBoxError ("Makefile is used, wait");
      else
        {
          makefile_used = TRUE;
          makefile_used = target_make ();
        }
      return;

      case IDM_TARGET_RUN:
        target_run ();
      return;

      case IDM_TARGET_DEBUG:
        target_debug ();
      return;

      case IDM_TARGET_NEW:
        if (target_create_new () == TRUE)
        {
          if (nTargets++ == 0)
            target_menu_update (TRUE);
          SetFileSaveStatus (TRUE);
        }
      return;

      case IDM_TARGET_REMOVE:
        target_remove ();
      if (--nTargets == 0)
        target_menu_update (FALSE);
      SetFileSaveStatus (TRUE);
      return;

      case IDM_TARGET_RENAME:
        if (target_rename ())
        SetFileSaveStatus (TRUE);
      return;

      case IDM_TARGET_REMAKE:
        if (makefile_used == TRUE)
        MessageBoxError ("Makefile is used, wait");
      else
        {
          makefile_used = TRUE;
          target_touchall ();
          makefile_used = target_make ();
        }
      return;

      case IDM_TARGET_DEPS:
        target_deps();
        return;
        
      case IDM_OPTION_MAKE:
        ret = DialogBoxParam (hInstance, "INPUT", hWnd,
                              DialogInput, (LPARAM) "Makefile options");
      if (ret)
        strcpy (runopt.opt_make, (char *) ret);
      return;

      case IDM_OPTION_RUN:
        ret = DialogBoxParam (hInstance, "INPUT", hWnd,
                              DialogInput, (LPARAM) "Run options");
      if (ret)
        strcpy (runopt.opt_run, (char *) ret);
      return;

      case IDM_OPTION_DEBUG:
        ret = DialogBoxParam (hInstance, "INPUT", hWnd,
                              DialogInput, (LPARAM) "Debug options");
      if (ret)
        strcpy (runopt.opt_debug, (char *) ret);
      return;

      case IDM_OPTION_TARGET:
        target_flags ();
      return;

      case IDM_IDE_DEFEDITOR:
        DialogBox (hInstance, "IDEDEFAULT", hWnd, DialogIdeFlags);
      return;

      case IDM_IDE_DEFCOMPILER:
      {
        char *cmd = malloc (260);
        strcpy (cmd, "notepad ");
        GetModuleFileName (hInstance, cmd + 8, 260 - 8);
        strcpy (strrchr (cmd, '.') + 1, "ini");
        run_process (cmd);
        free (cmd);
      }
      return;

      case IDM_HELP_INDEX:
      {
        char module[260];
        int i;

        i = GetModuleFileName (hInstance, module, sizeof (module));
        for (; i > 0; i--)             // search rsxide.exe
          if (module[i] == '\\')
            break;
        for (--i; i > 0; i--)          // search bin
          if (module[i] == '\\')
            break;
        strcpy (module + i + 1, "doc\\rsxide.hlp");
        WinHelp (hWnd, module, HELP_INDEX, 0L);
      }
      return;

      case IDM_HELP_ONHELP:
        WinHelp (hWnd, (LPSTR) 0, HELP_HELPONHELP, 0L);
      return;

      case IDM_HELP_ABOUT:
        DialogBox (hInstance, "INFO", hWnd, DialogInfo);
      return;

      case IDM_WINDOW_CASCADE:
        project_cascade (nTargets);

      default:
        hWndChild = FORWARD_WM_MDIGETACTIVE (hWndMdiClient, SendMessage);

      if (IsWindow (hWndChild))
        FORWARD_WM_COMMAND (hWndChild, id, hWndCtl, notify, SendMessage);

      DefFrameProc (hWnd, hWndMdiClient, WM_COMMAND, MAKEWPARAM ((UINT) (id), (UINT) (notify)), (LPARAM) (HWND) (hWndCtl));
      return;
    }
}

void Ide_OnUser (HWND hWnd, int code)
{
  if (code == WMUSER_COMPILER_STOP)
    {
      makefile_used = FALSE;
      SetWindowText (hWndCompileFrame, "Make ready");
      MessageBeep (MB_OK);
    }
}

LRESULT CALLBACK IdeWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
    {
      case WM_CREATE:
        return HANDLE_WM_CREATE (hWnd, wParam, lParam, Ide_OnCreate);

      case WM_DESTROY:
        return HANDLE_WM_DESTROY (hWnd, wParam, lParam, Ide_OnDestroy);

      case WM_COMMAND:
        return HANDLE_WM_COMMAND (hWnd, wParam, lParam, Ide_OnCommand);

      case WM_NOTIFY:
        return HANDLE_WM_NOTIFY (hWnd, wParam, lParam, Ide_OnNotify);

      case WM_SIZE:
        return HANDLE_WM_SIZE (hWnd, wParam, lParam, Ide_OnSize);

      case WM_MENUSELECT:
        return HANDLE_WM_MENUSELECT (hWnd, wParam, lParam, Ide_OnMenuSelect);

      case WM_SYSCOMMAND:
        if (wParam == SC_CLOSE)
        {
          /* test cancel save */
          FORWARD_WM_COMMAND (hWnd, IDM_FILE_CLOSE, 0, 0, SendMessage);
          if (*szProjectName)          /* already open */
            return 0;
        }
      break;

      case WM_USER:
        return HANDLE_WM_USER (hWnd, wParam, lParam, Ide_OnUser);

    }                                  /* switch message */

  return DefFrameProc (hWnd, hWndMdiClient, message, wParam, lParam);
}

/*
   ----- Compile window functions -----
 */

void Compile_OnDestroy (HWND hWnd)
{
  ListBox_ResetContent (hWndCompileListBox);
}

void Compile_OnCommand (HWND hWnd, int id, HWND hWndCtl, UINT notify)
{
  if (id == IDC_LIST && notify == LBN_DBLCLK)
    {
      int index;
      char buffer[512];
      char *t1, *t2;

      index = ListBox_GetCurSel (hWndCompileListBox);
      if (index == LB_ERR)
        return;

      buffer[0] = 0;
      ListBox_GetText (hWndCompileListBox, index, buffer);

      /* skip drive from path */
      t1 = t2 = buffer;
      while (*t1)
      {
          if (!(*t1 == '\\' && *(t1+1) == '\\'))
            *t2++ = *t1;
          t1++;
      }
      t1 = (buffer[1] == ':' && (buffer[2] == '\\' || buffer[2] == '/')) ? buffer + 2 : buffer;

      /* "file.c:5: mistake bla bla" */
      if (!(t1 = strchr (t1, ':')))
        return;
      if (!(t2 = strchr (t1 + 1, ':')))
        return;
      *t1 = 0;
      *t2 = 0;

      if (connect_editor (TRUE))
        {
          EditDdeError (szProjectDir, buffer, atol (t1 + 1));
        }
    }
}

void Compile_OnSize (HWND hWnd, UINT state, int cx, int cy)
{
  MoveWindow (hWndCompileListBox, 0, 0, cx, cy, TRUE);
}

LRESULT CALLBACK CompileWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT r;

  switch (message)
    {
      case WM_SIZE:
        r = HANDLE_WM_SIZE (hWnd, wParam, lParam, Compile_OnSize);
      break;                           /* WM_SIZE must go to DefMdiChildProc */

      case WM_DESTROY:
        return HANDLE_WM_DESTROY (hWnd, wParam, lParam, Compile_OnDestroy);

      case WM_COMMAND:
        return HANDLE_WM_COMMAND (hWnd, wParam, lParam, Compile_OnCommand);

      case WM_SYSCOMMAND:
        if (wParam == SC_CLOSE)
        wParam = SC_MINIMIZE;
      break;

    }                                  /* switch message */

  return DefMDIChildProc (hWnd, message, wParam, lParam);
}

/*
   ----- Target window functions -----
 */

static BOOL Target_OnCreate (HWND hWnd, LPCREATESTRUCT lpCs)
{
  DragAcceptFiles (hWnd, TRUE);
  return TRUE;
}

static void Target_OnDestroy (HWND hWnd)
{
  struct target *target = (struct target *) GetWindowLong (hWnd, 0);
  char **pptr;
  int i;

  // ListBox_ResetContent(target->hWndTargetListBox);

  // free option string
  pptr = &(target -> flags.s.gcc_other);
  for (i = 0; i < target->flags.s.string_options; i++, ++pptr)
    if (*pptr)
      free (*pptr);

  // free file names            
  for (i = 0; i < target -> nfiles; ++i)
    {
      free (target -> sourcefiles[i]);
      free (target -> objectfiles[i]);
    }
  free (target -> sourcefiles);
  free (target -> objectfiles);

  // free target
  free (target);

  DragAcceptFiles (hWnd, FALSE);
}

static void Target_OnDropFiles (HWND hWnd, HDROP hDrop)
{
  struct target *target = (struct target *) GetWindowLong (hWnd, 0);
  UINT i, n, e = 0;
  char text[MAX_PATH];
  char *ext;

  n = DragQueryFile (hDrop, 0xffffffff, NULL, 0);

  for (i = 0; i < n; i++)
    {

      DragQueryFile (hDrop, i, text, MAX_PATH);
      strlwr (text);

      if ((ext = strrchr (text, '.')) == NULL)
        break;
      else
        ++ext;

      for (e = 0; e < nObjects; ++e)
        {

          if (stricmp (obj_desc[e].src_ext, ext) == 0)
            {
              int j;
              /* string is ok, test directory match */
              int len = strlen (szProjectDir);

              if (strnicmp (szProjectDir, text, len))
                {
                  /* test dir .. */
                  for (--len; len > 0; len--)
                    if (szProjectDir[len] == '\\')
                      break;
                  if (len >= 2 && strnicmp (szProjectDir, text, len) == 0)
                    {
                      text[--len] = '.';
                      text[--len] = '.';
                    }
                  else if (len >= 2 && strnicmp (szProjectDir, text, 2) == 0)
                    len = 2;
                  else
                    len = 0;
                }
              else                     /* current dir: take only name */
                len++;

              /* gcc compile prints \\ if you use backslash */
              if (!(text[0] == '\\' && text[1] == '\\'))  /* UNC */
                for (j = 0; text[j]; ++j)
                  if (text[j] == '\\')
                    text[j] = '/';
                  
              target_add_file (target, text + len, obj_desc + e);
              SetFileSaveStatus (TRUE);
              break;
            }
        }
    }
  if (e >= nObjects)
    MessageBeep (MB_ICONHAND);
  else
    MessageBeep (MB_OK);
  DragFinish (hDrop);
}

static void Target_OnSize (HWND hWnd, UINT state, int cx, int cy)
{
  struct target *target = (struct target *) GetWindowLong (hWnd, 0);

  if (target)
    MoveWindow (target -> hWndTargetTreeView, 0, 0, cx, cy, TRUE);
}

static HTREEITEM hItemSelected; /* context menu item */

static void Target_OnNotify (HWND hWnd, int id, LPNMHDR lpNmHdr)
{
  struct target *target = (struct target *) GetWindowLong (hWnd, 0);
  static HTREEITEM hItem;

  if (lpNmHdr -> code == TVN_ITEMEXPANDED)
    {
      TV_ITEM tvi;
      int index = (((LPNM_TREEVIEW) lpNmHdr) -> action == TVE_EXPAND) ? idxOpen : idxClose;
      tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
      tvi.hItem = ((LPNM_TREEVIEW) lpNmHdr) -> itemNew.hItem;
      tvi.iImage = iImageIndex[index];
      tvi.iSelectedImage = iImageIndex[index];
      TreeView_SetItem (lpNmHdr -> hwndFrom, &tvi);
    }
  else if (lpNmHdr -> code == TVN_SELCHANGED)
    {
      hItem = ((LPNM_TREEVIEW) lpNmHdr) -> itemNew.hItem;
    }
  else if (lpNmHdr -> code == NM_RCLICK || lpNmHdr -> code == NM_DBLCLK)
    {
      TV_ITEM tvi;
      char buf[260];

      tvi.hItem = TreeView_GetDropHilight (lpNmHdr -> hwndFrom);
      if (tvi.hItem == NULL)
        tvi.hItem = hItem;
      else
        TreeView_SelectItem (target -> hWndTargetTreeView, tvi.hItem);

      tvi.mask = TVIF_PARAM | TVIF_TEXT;
      tvi.pszText = buf;
      tvi.cchTextMax = sizeof (buf);
      if (TreeView_GetItem (lpNmHdr -> hwndFrom, &tvi) == FALSE)
        return;

      if (lpNmHdr -> code == NM_RCLICK && tvi.lParam == 0)      // child items
        {
          char * ext = strrchr (buf, '.') + 1;
          int e;
          POINT p;
          HMENU hMenu;

          for (e = 0; e < nObjects; ++e)
            if (stricmp (obj_desc[e].src_ext, ext) == 0)
              break;

          hItemSelected = tvi.hItem;
          hMenu = CreatePopupMenu ();
          if (e < nObjects && obj_desc[e].byeditor)
            AppendMenu (hMenu, MF_ENABLED, IDM_POPUP_EDIT, "&Edit Source");
          AppendMenu (hMenu, MF_ENABLED, IDM_POPUP_RENAME, "&Rename Source");
          AppendMenu (hMenu, MF_ENABLED, IDM_POPUP_TOUCH, "&Touch Source");
          AppendMenu (hMenu, MF_ENABLED, IDM_POPUP_DELETE, "&Delete Source");
          GetCursorPos (&p);
          TrackPopupMenu (hMenu, 0, p.x, p.y, 0, hWnd, NULL);
          DestroyMenu (hMenu);
        }
      else if (lpNmHdr -> code == NM_DBLCLK && tvi.lParam == 0)      // child items
        {
           hItemSelected = tvi.hItem;
           FORWARD_WM_COMMAND(hWnd, IDM_POPUP_EDIT, NULL, 0, PostMessage);
        }

    }
}

static void Target_OnCommand (HWND hWnd, int id, HWND hWndCtl, UINT notify)
{
  TV_ITEM tvi;
  char buf[260];
  struct target *target = (struct target *) GetWindowLong (hWnd, 0);
  
  if (!target)
    return;

  tvi.hItem = hItemSelected;
  tvi.mask = TVIF_PARAM | TVIF_TEXT;
  tvi.pszText = buf;
  tvi.cchTextMax = sizeof (buf);

  if (TreeView_GetItem (target -> hWndTargetTreeView, &tvi) == FALSE)
    return;

  if (tvi.lParam != 0) // child items
    return;

  switch (id)
    {
      case IDM_POPUP_EDIT:
        {
          int e;
          char * ext = strrchr (buf, '.') + 1;

          for (e = 0; e < nObjects; ++e)
            if (stricmp (obj_desc[e].src_ext, ext) == 0)
              break;

          if (e < nObjects && obj_desc[e].byeditor)
            {
              connect_editor (TRUE);
              EditDdeFileOpen (szProjectDir, buf);
            }
        }
        break;

      case IDM_POPUP_RENAME:
        {
          char * ret = (char *) DialogBoxParam (hInstance, "INPUT", hWnd,
                            DialogInput, (LPARAM) buf);
          if (ret)
          {
            char *s = strchr (ret, '.');
            int e;
            
            if (s)
            {
              ++s;
              for (e = 0; e < nObjects; ++e)
                if (stricmp (obj_desc[e].src_ext, s) == 0)
                  break;
              if (e >= nObjects)
              {
                MessageBoxError ("unknown source file extention");
                break;
              }
              DeleteTreeItem (target -> hWndTargetTreeView, hItemSelected);
              target_delete_file (buf);

              target_add_file (target, ret, obj_desc + e);
              SetFileSaveStatus (TRUE);
            }
            else
              MessageBoxError ("no source file extention");
          }
        }
        break;
              
      case IDM_POPUP_DELETE:
        DeleteTreeItem (target -> hWndTargetTreeView, hItemSelected);
        target_delete_file (buf);
        SetFileSaveStatus (TRUE);
        break;

      case IDM_POPUP_TOUCH:
        target_touch_file (buf);
        break;
    }
}

LRESULT CALLBACK TargetWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT r;

  switch (message)
    {
      case WM_CREATE:
        return HANDLE_WM_CREATE (hWnd, wParam, lParam, Target_OnCreate);

      case WM_DESTROY:
        return HANDLE_WM_DESTROY (hWnd, wParam, lParam, Target_OnDestroy);

      case WM_DROPFILES:
        return HANDLE_WM_DROPFILES (hWnd, wParam, lParam, Target_OnDropFiles);

      case WM_SIZE:
        r = HANDLE_WM_SIZE (hWnd, wParam, lParam, Target_OnSize);
      break;                           /* WM_SIZE must go to DefMdiChildProc */

      case WM_COMMAND:
        return HANDLE_WM_COMMAND (hWnd, wParam, lParam, Target_OnCommand);

      case WM_NOTIFY:
        Target_OnNotify (hWnd, (int) wParam, (LPNMHDR) lParam);
      return FALSE;

      case WM_SYSCOMMAND:
        if (wParam == SC_CLOSE)
        wParam = SC_MINIMIZE;
      break;

    }                                  /* switch message */

  return DefMDIChildProc (hWnd, message, wParam, lParam);
}

/*
   ----- Application start functions -----
 */

BOOL InitApplication (HINSTANCE hInstance)
{
  WNDCLASS wc;
  BOOL b;

  wc.style = 0;
  wc.lpfnWndProc = IdeWndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon (hInstance, szAppClass);
  wc.hCursor = LoadCursor (NULL, IDC_ARROW);
  wc.hbrBackground = GetStockObject (GRAY_BRUSH);
  wc.lpszMenuName = szAppClass;
  wc.lpszClassName = szAppClass;

  b = RegisterClass (&wc);

  wc.style = CS_NOCLOSE;
  wc.lpfnWndProc = CompileWndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon (hInstance, "RSXIDEC");
  wc.hCursor = LoadCursor (NULL, IDC_ARROW);
  wc.hbrBackground = GetStockObject (LTGRAY_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = szCompileClass;

  b &= RegisterClass (&wc);

  wc.style = CS_NOCLOSE;
  wc.lpfnWndProc = TargetWndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = sizeof (struct target *);     /* pointer to target */
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon (hInstance, "RSXIDET");
  wc.hCursor = LoadCursor (NULL, IDC_ARROW);
  wc.hbrBackground = GetStockObject (LTGRAY_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = szTargetClass;

  b &= RegisterClass (&wc);

  return b;
}

BOOL InitInstance (HINSTANCE hInstance, int nCmdShow)
{
  int cx, cy, dy;

  dy = GetSystemMetrics (SM_CYCAPTION);
  cx = GetSystemMetrics (SM_CXSCREEN) - dy * 2;
  cy = GetSystemMetrics (SM_CYSCREEN);
  cy = (cy - cy / 5) - dy * 2;
  if (cx > 600)
    cx = 600;
  if (cy > 400)
    cy = 400;

  hWndIde = CreateWindow (
                           szAppClass, szAppTitle,
                           WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                           dy, dy, cx, cy,
                           NULL,
                           NULL,
                           hInstance,
                           NULL);

  if (!hWndIde)
    return (FALSE);

  ShowWindow (hWndIde, nCmdShow);
  UpdateWindow (hWndIde);

  create_compile_window ();

  project_menu_update (FALSE);
  target_menu_update (FALSE);

  return TRUE;
}

static void register_ctl3d (BOOL init, HINSTANCE hInst)
{
  typedef BOOL (WINAPI * CTL3D_REGISTER) (HINSTANCE hModule);
  typedef BOOL (WINAPI * CTL3D_UNREGISTER) (HINSTANCE hModule);
  typedef BOOL (WINAPI * CTL3D_AUTOSUBCLASS) (HINSTANCE hModule);

  static CTL3D_REGISTER pRegister3d;
  static CTL3D_UNREGISTER pUnRegister3d;
  static CTL3D_AUTOSUBCLASS pAutoSubclass3d;
  static HANDLE hCtl3d;
  static BOOL bCtl3d;

  if (init == FALSE)
    {
      if (bCtl3d == TRUE)
        (*pUnRegister3d) (hInst);
      bCtl3d = FALSE;
    }
  else
    {
      UINT error_mode = SetErrorMode (SEM_NOOPENFILEERRORBOX);
      hCtl3d = LoadLibrary ("CTL3D32.DLL");     // Get Handle

      SetErrorMode (error_mode);

      if ((unsigned int) hCtl3d > 32)
        {                              /* SDK32: error = NULL */
          pRegister3d = (CTL3D_REGISTER)
            GetProcAddress (hCtl3d, "Ctl3dRegister");
          pUnRegister3d = (CTL3D_UNREGISTER)
            GetProcAddress (hCtl3d, "Ctl3dUnregister");
          pAutoSubclass3d = (CTL3D_AUTOSUBCLASS)
            GetProcAddress (hCtl3d, "Ctl3dAutoSubclass");

          if (!pRegister3d || !pUnRegister3d || !pAutoSubclass3d)
            {
              bCtl3d = FALSE;
            }
          else if ((*pRegister3d) (hInst) == TRUE)
            {
              bCtl3d = TRUE;
              (*pAutoSubclass3d) (hInst);
            }
        }
    }
}

int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdParam, int nCmdShow)
{
  MSG msg;
  DWORD ver;
  HWND hWndLogo;
  int len;

  hInstance = hInst;
  ver = GetVersion ();
  win32s = ((ver & 0x80000000) && !(ver & 0x40000000)) ? 1 : 0;
  winv3x = ((ver & 0xff) < 0x04) ? 1 : 0;

  if (winv3x)
    register_ctl3d (TRUE, hInst);

  if (!InitApplication (hInstance))
    {
      MessageBox (NULL, "register class", NULL, MB_OK | MB_ICONINFORMATION);
      return (FALSE);
    }
  if (!InitInstance (hInstance, nCmdShow))
    {
      MessageBox (NULL, "create windows", NULL, MB_OK | MB_ICONINFORMATION);
      return (FALSE);
    }

  len = 0;
  if (lpszCmdParam)
    {
      len = strlen (lpszCmdParam);
      if (len > 0)
        {
          if (lpszCmdParam[0] == '\"' && lpszCmdParam[len - 1] == '\"')
            {
              lpszCmdParam[len - 1] = '\0';
              lpszCmdParam++;
            }
          if (access (lpszCmdParam, 0) == 0)
            {
              LPSTR namepos;
              char *s;

              GetFullPathName (lpszCmdParam, sizeof (szProjectName), szProjectName, &namepos);
              strcpy (szProjectDir, szProjectName);
              s = szProjectDir + strlen (szProjectDir);
              while (s > szProjectDir && *--s != '\\')
                ;
              *s = '\0';
              FORWARD_WM_COMMAND (hWndIde, IDM_FILE_CMDOPEN, 0, 0, PostMessage);
            }
        }
    }
  if (!szProjectName[0])
    hWndLogo = CreateDialog (hInst, "INFO", hWndIde, DialogInfo);

  if (!len)
    GetCurrentDirectory (sizeof (szProjectDir), szProjectDir);

  while (GetMessage (&msg, NULL, 0, 0))
    {
      if (!TranslateMDISysAccel (hWndMdiClient, &msg))
        {
          TranslateMessage (&msg);
          DispatchMessage (&msg);
        }
    }

  if (winv3x)
    register_ctl3d (FALSE, hInst);

  return msg.wParam;
}
