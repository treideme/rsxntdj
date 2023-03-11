#ifdef __GNUC__
#include <crtrsxnt.h>
#endif

#define WIN32_LEAN_AND_MEAN
#define STRICT         // Striktere Typprüfungen einschalten
#include <windows.h>   // Windows.h einlesen
#include <richedit.h>  // Alle RichEdit-Details finden sich in richedit.h
#include <windowsx.h>  // Windowsx.h für die Message Cracker
#include <stdio.h>     // wegen sprintf

#include "winedit.h"   // Resource-IDs

CHAR szClassName[]="RTEdit";  // Fensterklasse für das Haupt-Window
CHAR szWndTitle[]="WinEdit";  // Titel des Hauptfensters
CHAR szFilename[]="Dokument"; // Default-Dateiname
// Textstring im Rich Text Format für die Initialisierung der
// RichEdit-Control via Clipboard
CHAR szRTFText[]="{\\rtf1\\ansi\\deff0\\deftab720{\\fonttbl{\\f0\\fnil "
  "MS Sans Serif;}{\\f1\\fnil\\fcharset2 Symbol;}{\\f2\\fswiss\\fprq2 "
  "System;}{\\f3\\fnil Times New Roman;}}"
  "{\\colortbl\\red0\\green0\\blue0;}"
  "\\deflang1033\\pard\\plain\\f3\\fs30 Hallo, dies ist ein Testtext!"
  "\\par"
  "\\par \\plain\\f3\\fs30\\b Diese Zeile ist FETT..."
  "\\par"
  "\\par \\plain\\f3\\fs30\\i ... diese ist KURSIV ..."
  "\\par"
  "\\par \\plain\\f3\\fs30\\ul und die ist UNTERSTRICHEN, oder?"
  "\\par"
  "\\par \\plain\\f3\\fs50 Und die \\plain\\f3\\fs50\\b "
  "letzte\\plain\\f3\\fs50  ist \\plain\\f3\\fs50\\i "
  "etwas\\plain\\f3\\fs50  \\plain\\f3\\fs50\\ul gr\\'f6\\'dfer!"
  "\\par \\plain\\f3\\fs50}";
HINSTANCE hInst; // für die Instanz-Handle
HWND hwndRTEdit; // für die RichEdit-Window-Handle
HFONT hFont;     // für den verwendeten Font

// DialogBox-Callback-Prozedur für den modalen WINEDIT_INFODLG-Dialog
BOOL CALLBACK InfoDlgProc(HWND hwnd,UINT msg,UINT wParam,LONG lParam);
BOOL CALLBACK InfoDlgProc(HWND hwnd,UINT msg,UINT wParam,LONG lParam)
{
  switch (msg) {
    case WM_INITDIALOG:
      return TRUE;           // Windows setzt den Focus
    case WM_COMMAND:         // OK- oder Close-Button gedrückt
      switch (LOWORD(wParam)) {
        case IDOK:           // OK
        case IDCANCEL:       // Close
          EndDialog(hwnd,0); // Dialog beenden
          return TRUE;
      }
  }
  return FALSE; // Andere Messages werden nicht behandelt
}

// Formatiert den markierten Text in der RichEdit-Control (wenn keine
// Markierung existiert, werden die Default-Attribute modifiziert)
VOID FormatText(int id);
VOID FormatText(int id)
{
  CHARFORMAT cf;
  cf.cbSize=sizeof(cf);
  // Aktuelle Formateinstellungen lesen
  SendMessage(hwndRTEdit,EM_GETCHARFORMAT,TRUE,(LPARAM)&cf);
  // ... und entsprechend anpassen
  switch (id) {
    case ID_FORMAT_FETT:
      cf.dwMask=CFM_BOLD;
      cf.dwEffects^=CFE_BOLD;
      break;
    case ID_FORMAT_KURSIV:
      cf.dwMask=CFM_ITALIC;
      cf.dwEffects^=CFE_ITALIC;
      break;
    case ID_FORMAT_UNTERSTRICHEN:
      cf.dwMask=CFM_UNDERLINE;
      cf.dwEffects^=CFE_UNDERLINE;
      break;
    case ID_FORMAT_GROESSER:
      cf.dwMask=CFM_SIZE;
      cf.yHeight+=20; // Die RichEdit-Fontgröße wird in Twips
                      // (1/1440 inch) gemessen
      break;
  }
  // Alles wieder zurück zur Control
  SendMessage(hwndRTEdit,EM_SETCHARFORMAT,SCF_SELECTION,(LPARAM)&cf);
}

// WM_CREATE-Handler, erzeugt die RichEdit-Control sowie den Font, mit
// dem die Control arbeiten soll. Dann wird der Anfangstext von szRTFText
// via Speicher-Handle und Clipboard in die Control kopiert.
BOOL RTEdit_OnCreate(HWND hwnd,LPCREATESTRUCT lpCreateStruct);
BOOL RTEdit_OnCreate(HWND hwnd,LPCREATESTRUCT lpCreateStruct)
{
  // Child-Fenster der RichEdit-Klasse erzeugen
  hwndRTEdit=CreateWindow("RichEdit",  // Klassenname "RichEdit"
    "",  // Hier kein Window-Text, wird später gesetzt
    WS_CHILD|WS_VISIBLE|WS_BORDER|WS_VSCROLL| // Window-Stilbits
    // sowie weitere RichEdit-spezifische Optionen
    ES_LEFT|        // Text linksbündig
    ES_MULTILINE|   // mehrzeilig
    ES_AUTOVSCROLL, // mit vertikaler Scrollbar, falls erforderlich
    0,0,            // x,y-Position im Haupt-Window
    10,10,          // Breite und Höhe (in Pixel), wird später korrigiert
    hwnd,           // Parent-Fenster ist das Haupt-Window
    (HMENU)ID_RICHEDIT, // Child-Id
    hInst,          // Instanz-Handle
    NULL);          // keine zusätzlichen benutzerdefinierten Daten
  if (hwndRTEdit) { // Window da ?
    UINT cfRTF;
    HGLOBAL hgRTF;
    LPVOID lpRTF;
    // Font aus der Times-Roman-Familie erzeugen
    hFont=CreateFont(0,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,
      ANSI_CHARSET,0,0,0,VARIABLE_PITCH|FF_ROMAN,NULL);
    // ... und an die RichEdit-Control senden
    SendMessage(hwndRTEdit,WM_SETFONT,(WPARAM)hFont,FALSE);
    // Clipboard mit dem Anfangstext initialisieren
    // Zuerst Text in die Speicher-Handle hg kopieren
    hgRTF=GlobalAlloc(GHND,sizeof(szRTFText));
    lpRTF=GlobalLock(hgRTF);
    strcpy(lpRTF,szRTFText);
    GlobalUnlock(hgRTF);
     // Dann das RTF-Format registrieren und Handle im Clipboard ablegen
    cfRTF=RegisterClipboardFormat(CF_RTF);
    OpenClipboard(hwnd); // Clipboard öffnen...
    EmptyClipboard();    // ... leeren...
    hFont=SetClipboardData(cfRTF,hgRTF); // ... und Handle kopieren
    CloseClipboard(); // Clipboard schließen
    // RichEdit anweisen, den RTF-Text vom Clipboard zu lesen
    // (möglich wäre natürlich auch der Aufruf der Funktion
    // RTEdit_OnCommand(), die weiter unten definiert wird)
    SendMessage(hwndRTEdit,WM_PASTE,0,0);
    // Clipboard-Inhalt wieder löschen
    OpenClipboard(hwnd);
    EmptyClipboard();
    CloseClipboard();
  }
  return hwndRTEdit!=NULL; // !=0 heißt Erfolg
}

// Behandelt die WM_SIZE-Nachrichten für das Haupt-Window und paßt die
// Größe des RichEdit-Child-Windows an die des Toplevel-Windows an
VOID RTEdit_OnSize(HWND hwnd,UINT state,int cx,int cy);
VOID RTEdit_OnSize(HWND hwnd,UINT state,int cx,int cy)
{
  MoveWindow(hwndRTEdit,0,0,cx,cy,TRUE);
}

// Behandelt die WM_SETFOCUS-Messages und gibt den Eingabe-Fokus gleich
// weiter an die RichEdit-Control
VOID RTEdit_OnSetFocus(HWND hwnd,HWND hwndOldFocus);
VOID RTEdit_OnSetFocus(HWND hwnd,HWND hwndOldFocus)
{
  SetFocus(hwndRTEdit);
}

// Behandelt alle WM_COMMAND-Nachrichten, die von Menus oder via
// Accelerators erzeugt werden.
VOID RTEdit_OnCommand(HWND hwnd,int id,HWND hwndCtl,UINT codeNotify);
VOID RTEdit_OnCommand(HWND hwnd,int id,HWND hwndCtl,UINT codeNotify)
{
  switch (id) {
    case ID_DATEI_BEENDEN:
      // Fenster zerstören, alles weitere siehe bei WM_DESTROY
      DestroyWindow(hwnd);
      break;
    case ID_BEARBEITEN_AUSSCHNEIDEN:
    case ID_FORMAT_KLEINER:
      // Nicht implementiert, ein wenig Arbeit für die Leser muß sein
      MessageBox(hwnd,"Bleibt eine Aufgabe für den Leser...",
        szWndTitle,MB_ICONEXCLAMATION|MB_OK);
      break;
    // Undo-Message an Control schicken
    case ID_BEARBEITEN_RUECKGAENGIG:
      SendMessage(hwndRTEdit,EM_UNDO,0,0);
      break;
    // Copy-Message
    case ID_BEARBEITEN_KOPIEREN:
      SendMessage(hwndRTEdit,WM_COPY,0,0);
      break;
    // Paste-Message
    case ID_BEARBEITEN_EINFUEGEN:
      SendMessage(hwndRTEdit,WM_PASTE,0,0);
      break;
    // Clear-Message
    case ID_BEARBEITEN_LOESCHEN:
      SendMessage(hwndRTEdit,WM_CLEAR,0,0);
      break;
    // Markierung via EM_EXSETSEL setzen
    case ID_BEARBEITEN_ALLESAUSWAEHLEN: {
      CHARRANGE cr;
      cr.cpMin=0;  // 0, -1 bedeutet gesamten Text
      cr.cpMax=-1;
      SendMessage(hwndRTEdit,EM_EXSETSEL,0,(LPARAM)&cr);
      break;
      }
    // Entsprechendes Format modifizieren
    case ID_FORMAT_FETT:
    case ID_FORMAT_KURSIV:
    case ID_FORMAT_UNTERSTRICHEN:
    case ID_FORMAT_GROESSER:
      FormatText(id);
      break;
    // WINEDIT_INFODLG als modale DialogBox anzeigen
    case ID_HILFE_INFO:
      DialogBox(hInst,     // Instanz-Handle
        "WINEDIT_INFODLG", // Name der Dialog-Ressource
        hwnd,              // Window-Handle des Parents
        InfoDlgProc);      // Dialog-Callback-Funktion
      break;
  }
}

// Behandelt WM_INITMENUPOPUP-Nachrichten und deaktiviert ggf. bestimmte
// Menueinstellungen im Bearbeiten-Menu, die zur Zeit nicht aktiviert
// werden können.
VOID RTEdit_OnInitMenuPopup(HWND hwnd,HMENU hMenu,UINT uItem,
  BOOL fSystemMenu);
VOID RTEdit_OnInitMenuPopup(HWND hwnd,HMENU hMenu,UINT uItem,
  BOOL fSystemMenu)
{
  if (uItem==1) { // 0 == Datei-Menu, 1 == Bearbeiten-Menu etc.
    // Die notwendigen Informationen bei der RichEdit-Control erfragen
    BOOL f1=SendMessage(hwndRTEdit,EM_CANUNDO,0,0);  // Undo möglich?
    BOOL f2=SendMessage(hwndRTEdit,EM_CANPASTE,0,0); // Paste möglich?
    // Ist Text in der Control markiert?
    LRESULT l=SendMessage(hwndRTEdit,EM_SELECTIONTYPE,0,0);
    // Die betroffenen Menu-Einträge entweder grau oder aktiv schalten
    EnableMenuItem(hMenu,ID_BEARBEITEN_RUECKGAENGIG,
      f1?MF_ENABLED:MF_GRAYED);
    EnableMenuItem(hMenu,ID_BEARBEITEN_AUSSCHNEIDEN,
      l!=SEL_EMPTY?MF_ENABLED:MF_GRAYED);
    EnableMenuItem(hMenu,ID_BEARBEITEN_KOPIEREN,
      l!=SEL_EMPTY?MF_ENABLED:MF_GRAYED);
    EnableMenuItem(hMenu,ID_BEARBEITEN_EINFUEGEN,
      f2?MF_ENABLED:MF_GRAYED);
  }
}

// Behandelt die WM_DESTROY-Nachricht: zerstört den Font und legt eine
// WM_QUIT-Message in der Message-Queue ab
VOID RTEdit_OnDestroy(HWND hwnd);
VOID RTEdit_OnDestroy(HWND hwnd)
{
  DeleteObject(hFont); // hFont freigeben
  PostQuitMessage(0);  // WM_QUIT in die Nachrichtenschlange legen
}

// Die (simple) Window-Prozedur
LRESULT CALLBACK RTEditWndProc(HWND hwnd,UINT msg,WPARAM wP,LPARAM lP);
LRESULT CALLBACK RTEditWndProc(HWND hwnd,UINT msg,WPARAM wP,LPARAM lP)
{
  switch (msg) {
    // WM_CREATE erhält ein Window direkt nach seiner Erzeugung, z.B. um
    // weitere Initialisierungen vorzunehmen.
    case WM_CREATE:
      return HANDLE_WM_CREATE(hwnd,wP,lP,RTEdit_OnCreate);
    // Bei jeder Vergrößerung oder Verkleinerung
    case WM_SIZE:
      return HANDLE_WM_SIZE(hwnd,wP,lP,RTEdit_OnSize);
    // Wenn die Applikation den Fokus erhält
    case WM_SETFOCUS:
      return HANDLE_WM_SETFOCUS(hwnd,wP,lP,RTEdit_OnSetFocus);
    // Signalisiert eine Menu- oder Acceleratorauswahl
    case WM_COMMAND:
      return HANDLE_WM_COMMAND(hwnd,wP,lP,RTEdit_OnCommand);
    // Ein Popup-Menu soll gleich dargestellt werden
    case WM_INITMENUPOPUP:
      return HANDLE_WM_INITMENUPOPUP(hwnd,wP,lP,RTEdit_OnInitMenuPopup);
    // Das Hauptfenster wird geschlossen, dabei wird automatisch auch das
    // RichEdit-Child-Window zerstört.
    case WM_DESTROY:
      return HANDLE_WM_DESTROY(hwnd,wP,lP,RTEdit_OnDestroy);
  }
  // Alle anderen Nachrichten landen bei der Standard-Behandlung
  return DefWindowProc(hwnd,msg,wP,lP);
}

// Das Hauptprogramm
INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
  LPSTR lpCmdLine,INT nCmdShow)
{
  WNDCLASS wc;
  HWND hwnd;
  HACCEL hAccel;
  HINSTANCE hRichEditDLL;
  MSG msg;
  CHAR szTitle[300];

  hInst=hInstance; // Instance-Handle in globale Variable schreiben

  // RichEdit-DLL in der 32-Bit-Form laden
  hRichEditDLL=LoadLibrary("RICHED32.DLL");
  // Da RICHED32.DLL nicht auf allen 32-Bit-Systemen installiert sein
  // muß, wird das Resultat geprüft
  if (hRichEditDLL==0) {
     // Nicht gefunden?
    MessageBox(NULL,"RICHED32.DLL leider, leider nicht gefunden, "
      "WinEdit wird daher beendet...",szWndTitle,MB_ICONHAND|MB_OK);
    return 0;
  }
  // Accelerator-Tabelle laden
  hAccel=LoadAccelerators(hInstance,"WINEDIT_ACCELERATORS");

  // WNDCLASS-Struktur füllen
  wc.style=CS_HREDRAW|CS_VREDRAW;   // Klassen-Optionen
  wc.lpfnWndProc=RTEditWndProc;     // Adresse der Window-Prozedur
  wc.cbClsExtra=0; wc.cbWndExtra=0; // ignorieren
  wc.hInstance=hInstance;           // Instanz-Handle, ignorieren
  wc.hIcon=LoadIcon(hInstance,IDI_APPLICATION); // Icon (Default)
  wc.hCursor=LoadCursor(NULL,IDC_ARROW);        // Cursor (Default)
  wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);    // Hintergrund (Default)
  wc.lpszMenuName="WINEDIT_HAUPTMENU";          // Name des Hauptmenus
  wc.lpszClassName=szClassName;     // Klassenname, siehe 1. Parameter
                                    // von CreateWindow()
  RegisterClass(&wc);               // Klasse bei Windows registrieren

  sprintf(szTitle,"%s - %s",szFilename,szWndTitle);
  hwnd=CreateWindow(szClassName, // Fenster der Klasse erzeugen
                    szTitle,     // Fenster-Titel (Window-Text)
                    WS_OVERLAPPEDWINDOW, // Fenstertyp, weitere Optionen
                    CW_USEDEFAULT,0,     // x,y-Position auf dem Schirm
                    480,320,     // Breite und Höhe (in Pixel)
                    NULL,        // Parent-Fenster (keines)
                    NULL,        // Menu-Handle (keine, siehe WNDCLASS)
                    hInstance,   // Instanz-Handle
                    NULL);       // Zusätzliche Daten

  // Das Fenster wird unsichtbar erzeugt, daher sichtbar machen
  ShowWindow(hwnd,nCmdShow); // nCmdShow ist letzter WinMain()-Parameter

  // Eine Nachrichtenschleife wie aus dem Bilderbuch
  while (GetMessage(&msg,NULL,0,0)) {
    // Ggf. WM_KEYDOWN in Accelerator übersetzen
    if (!TranslateAccelerator(hwnd,hAccel,&msg)) {
      // Kein Accelerator, daher muß die Message übersetzt ...
      TranslateMessage(&msg);
      // und an den Adressaten weitergeleitet werden
      DispatchMessage(&msg);
    }
  }

  // RICHED32.DLL freigeben
  FreeLibrary(hRichEditDLL);

  // Finito
  return 0;
}
