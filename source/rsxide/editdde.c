/* editdde.c - bind editor to ide (with dde commands)

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
#include "editdde.h"

BOOL connect_editor(BOOL init);

typedef BOOL (*EXECUTE)(char *szCommand);

char dde_editor[MAX_PATH];
char dde_service[NCHAR_DDE];
char dde_topic[NCHAR_DDE];
char dde_fileopen[NCHAR_DDE];
char dde_goto[NCHAR_DDE];
char dde_markline[NCHAR_DDE];

struct dde_editor dde_editors[7] = {
  {
    "Watcom Vi for Windows",
    "viw -s ddesinit.vi -p \"VIW Edit\"",
    "VIW",
    "Edit",
    "EditFile %s",
    "Locate %d 1 0",
    "Locate %d 1 80"
  },
  {
    "Programmer's File Editor",
    "d:\\win32app\\pfe\\pfe32.exe",
    "PFE32",
    "Editor",
    "[FileOpen(\"%s\",0)]",
    "[EditGotoLine(%d,0)]",
    "[CaretEndOfLine(1)]"
  },
  {
    "Microsoft WinWord",
    "d:\\msoffice\\winword\\winword.exe /m",
    "WinWord",
    "System",
    "[DateiÖffnen(\"%s\",0)]",
    "[BearbeitenGeheZu(\"z%d\")]",
    "[EndeZeile(1)]"
  },
  {
    "Zeus 2.x for Windows",
    "d:\\win32app\\zeus200\\zeus32.exe",
    "Zeus32",
    "System",
    "[open(\"%s\")]",
    "",
    ""
  },
  {
    "Generic DDE Editor",
    "Program.exe",
    "Program",
    "System",
    "[open(\"%s\")]",
    "",
    ""
  },
  {
    "UltraEdit",
    "E:\\programme\\ultraedt\\UEdit32",
    "UEdit32",
    "System",
    "[open(\"%s\")]",
    "[open(\"%s\"/%d/1)]",
    ""
  },
  {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
  }
};

extern  HINSTANCE   hInstance;

static  HCONV       hConv;
static  DWORD       idInstance;
static  BOOL        bDdemlInitialized;
static  BOOL        bConnected;
static  BOOL        bAppSpawned;
static  FARPROC     lpDdeProc;
static  HWND        hWndEditor;
static  EXECUTE     pExecute;

BOOL connect_editor (BOOL init)
{
  if (init == TRUE)
    {
      if (bConnected == FALSE)
        return EditDdeConnect ();
      else
        return TRUE;
    }
  else
    {
      if (bConnected == TRUE)
          EditDdeDisconnect ();
      return FALSE;
    }
}

static void doReset(void)
{
    hConv = NULL;
    bDdemlInitialized = FALSE;
    bConnected = FALSE;
    bAppSpawned = FALSE;
}

static BOOL do_execute(char *szCommand)
{
    HDDEDATA    hddeData;

    hddeData = DdeClientTransaction( szCommand, strlen( szCommand ) + 1,
                                     hConv, NULL, CF_TEXT, XTYP_EXECUTE,
                                     5000, NULL );
    return( hddeData != 0 );
}

static BOOL do_request(char *szCommand)
{
    HDDEDATA    hddeData;
    HSZ         hszItem;

    hszItem = DdeCreateStringHandle(idInstance, szCommand, CP_WINANSI);

    hddeData = DdeClientTransaction(NULL, 0, hConv, hszItem, CF_TEXT,
                    XTYP_REQUEST, 5000, NULL );

    DdeFreeStringHandle( idInstance, hszItem);

    return( hddeData != 0 );
}

#ifdef WATCOM
#define EXPORT __export
#else
#define EXPORT
#endif

HDDEDATA EXPORT WINAPI DdeCallback
    (UINT uType, UINT uFmt, HCONV hconv, HSZ hsz1, HSZ hsz2, HDDEDATA hdata,
    DWORD dwData1, DWORD dwData2)
{
    if (uType == XTYP_DISCONNECT) {
        if (bConnected)
            doReset();
        return (NULL);
    }
    return(NULL);
}

BOOL EditDdeConnect(void)
{
    HSZ     hszService, hszTopic;
    int     rc = 0;

    if( bConnected ) {
        return( TRUE );
    }

    // initialize our idInstance in ddeml
    if( !bDdemlInitialized ) {
        lpDdeProc = MakeProcInstance( (FARPROC) DdeCallback, hInstance );
        if( DdeInitialize( &idInstance, (PFNCALLBACK) lpDdeProc,
                           APPCMD_CLIENTONLY, 0L ) != DMLERR_NO_ERROR ) {
            return( FALSE );
        }
        bDdemlInitialized = TRUE;
    }

    // get handles to access strings
    hszService = DdeCreateStringHandle(idInstance, dde_service, CP_WINANSI);
    hszTopic= DdeCreateStringHandle(idInstance, dde_topic, CP_WINANSI);

    // attempt connection
    hConv = DdeConnect(idInstance, hszService, hszTopic, (PCONVCONTEXT)NULL);
    if( hConv == 0 ) {
        // run editor (magically grabs focus)
        // DEBUGGERS NOTE: if debugging through here, give cw a moment
        //                 to load up as it won't respond to our
        //                 DDEConnect right away
        rc = WinExec(dde_editor, SW_RESTORE);
        if( rc >= 32 ) {
            // editor is up - try again (otherwise give up)
            hConv = DdeConnect( idInstance, hszService, hszTopic,
                                (PCONVCONTEXT) NULL );
        }
    }

    DdeFreeStringHandle(idInstance, hszService);
    DdeFreeStringHandle(idInstance, hszTopic);

    if( hConv == 0 ) {
        return( FALSE );
    }

    bConnected = TRUE;

    if( rc >= 32 ) {
        // we spawned & connected ok
        bAppSpawned = TRUE;
    }

    if (strcmp("VIW", dde_service) == 0)
        pExecute = do_request;
    else
        pExecute = do_execute;

    hWndEditor = GetForegroundWindow();
    return( TRUE );
}

int EditDdeDisconnect(void)
{
    if (!bConnected)
        return (TRUE);

    DdeUninitialize(idInstance);
    idInstance = 0;

    if (bAppSpawned)
        SendMessage(hWndEditor, WM_CLOSE, 0, 0L);
    hWndEditor = NULL;

    doReset();

    return (TRUE);
}

BOOL EditDdeFileOpen(LPSTR szDir, LPSTR szFile)
{
    char szCommand[MAX_PATH+20];
    char path[MAX_PATH];
    BOOL rc;
    int j;
    
    if (!bConnected)
        return( FALSE );

    if (szFile[1] == ':')                           // absolute path
    {
      strcpy (path, szFile);
    }
    else if (szFile[0] == '\\' || szFile[0] == '/') // no drive
    {
      path [0] = szDir[0];
      path [1] = szDir[1];
      strcpy (path + 2, szFile);
    }
    else                                            // no path
    {
      strcpy (path, szDir);
      strcat (path, "\\");
      strcat (path, szFile);
    }
    for (j = 0; path[j]; ++j)
      if (path[j] == '/')
        path[j] = '\\';
    
    sprintf(szCommand, dde_fileopen, path);
    rc = (*pExecute)(szCommand);

    return rc;
}

int EditDdeMarkLine(long line)
{
    char szCommand[100];
    int rc = 0;

    if(!bConnected)
        return( FALSE );

    /* goto line */
    if (*dde_goto) {
        sprintf(szCommand, dde_goto, line);
        rc = (*pExecute) (szCommand);
    }

    if (*dde_markline) {
        if (strchr(dde_markline, '%'))
            sprintf(szCommand, dde_markline, line);
        else
            strcpy(szCommand, dde_markline);
        rc |= (*pExecute) (szCommand);
    }

    SetForegroundWindow(hWndEditor);

    return (rc);
}

int EditDdeError(LPSTR szDir, LPSTR szFile, long line)
{
    if (*dde_goto && strstr(dde_goto, "%s"))  /* open and line together */
    {
        char szCommand[MAX_PATH+20];
        char path[MAX_PATH];
        BOOL rc;
        int j;
    
        if (!bConnected)
            return( FALSE );

        if (szFile[1] == ':')                           // absolute path
        {
          strcpy (path, szFile);
        }
        else if (szFile[0] == '\\' || szFile[0] == '/') // no drive
        {
          path [0] = szDir[0];
          path [1] = szDir[1];
          strcpy (path + 2, szFile);
        }
        else                                            // no path
        {
          strcpy (path, szDir);
          strcat (path, "\\");
          strcat (path, szFile);
        }
        for (j = 0; path[j]; ++j)
          if (path[j] == '/')
            path[j] = '\\';
        
        sprintf(szCommand, dde_goto, path, line);
        rc = (*pExecute)(szCommand);

        return rc;
    }
    else
    {
        EditDdeFileOpen(szDir, szFile);
        return EditDdeMarkLine(line);
    }
}

