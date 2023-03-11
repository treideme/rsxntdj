#ifdef __GNUC__
#include <crtrsxnt.h>
#endif

#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sol.h"

#define MAX_FIELDS 7

/* globals */
static char szAppname[] = "solo";
static HINSTANCE hInstance;

static int brett[MAX_FIELDS][MAX_FIELDS];
static int
    dcx1[MAX_FIELDS][MAX_FIELDS], dcx2[MAX_FIELDS][MAX_FIELDS],
    dcy1[MAX_FIELDS][MAX_FIELDS], dcy2[MAX_FIELDS][MAX_FIELDS]; /* dc-points */
static struct { int x, y, dx, dy;} zug[32];
static int zugnr = 0;

static void initboard(int nfields)
{
    int i, j;

    for (i = 0; i < nfields; i++)
        for (j = 0; j < nfields; j++) {
            brett[i][j] = 2;
        }
        
    /* freies Feld */
    brett[nfields/2][nfields/2] = 1;
    
    /* keine steine */                
    for (i = 0; i < nfields/2 - 1; i++)
        for (j = 0; j < nfields/2 -1; j++) {
            brett[i][j] = 0;
            brett[nfields - 1 - i][nfields - 1 - j] = 0;            
            brett[nfields - 1 - i][j] = 0;
            brett[i][nfields - 1 - j] = 0; 
        }
}

static void setboard(int fieldx, int fieldy, int nfields)
{
    int i, j;
    int rx, ry;

    rx = fieldx + (fieldx / (nfields - 1));
    ry = fieldy + (fieldy / (nfields - 1));

    for (i = 0; i < nfields; i++)
        for (j = 0; j < nfields; j++) {
            dcx1[i][j] = 20 + i * rx;
            dcy1[i][j] = 20 + j * ry;
            dcx2[i][j] = 20 + fieldx + i * rx;
            dcy2[i][j] = 20 + fieldy + j * ry;
        }
}

static int endnow(int nfields)
{
    struct { BOOL x, y; } vorher;       /* vorher ein stein */
    struct { BOOL x, y; } ok;           /* mind. zwei steine hintereinander */
    struct { int x, y; } anzahl;        /* */
    int x, y, points = 0;
    
    for (x = 0; x < nfields; x++) {
        anzahl.y = 0;
        anzahl.x = 0;
        vorher.y = FALSE;
        vorher.x = FALSE;
        ok.y = FALSE;
        ok.x = FALSE;

        for (y = 0; y < nfields; y++) {
            if (brett[x][y] == 2) { 
                if (vorher.y)
                    ok.y = TRUE;
                anzahl.y++;
                vorher.y = TRUE;
            } else                 
                vorher.y = FALSE;

            if (brett[y][x] == 2) {
                if (vorher.x)
                    ok.x = TRUE;
                anzahl.x++;
                vorher.x = TRUE;
            } else
                vorher.x = FALSE;
        }
        
        points += anzahl.y;

        if (ok.y && anzahl.y != 7 && x >= 2 && x <= 4) /* < 7 steine in mitte */
            return 0;
        if (ok.y && anzahl.y != 3 && (x < 2 || x > 4)) /* < 3 steine und aussen */
            return 0;
        if (ok.x && anzahl.x != 7 && x >= 2 && x <= 4) 
            return 0;
        if (ok.x && anzahl.x != 3 && (x < 2 || x > 4)) 
            return 0;
    }
    return points;
}

static void paint(HDC hdc)
{
    int i, j;
    HANDLE hOldbrush;
    HBRUSH hStoneBrush, hEmptyBrush;

    hEmptyBrush = CreateSolidBrush(RGB(255, 0, 0));
    hStoneBrush = CreateSolidBrush(RGB(0, 0, 0));

    SelectObject(hdc, hEmptyBrush);
    for (i = 0; i <= 6; i++)
        for (j = 0; j <= 6; j++) {
            if (brett[i][j] >= 1)
                Ellipse(hdc, dcx1[i][j], dcy1[i][j], dcx2[i][j], dcy2[i][j]);
        }
    hOldbrush = SelectObject(hdc, hStoneBrush);
    for (i = 0; i <= 6; i++)
        for (j = 0; j <= 6; j++) {
            if (brett[i][j] == 2) {
                Ellipse(hdc, dcx1[i][j], dcy1[i][j], dcx2[i][j], dcy2[i][j]);
            }
        }

    SelectObject(hdc, hOldbrush);
    DeleteObject(hEmptyBrush);
    DeleteObject(hStoneBrush);
}

static void play(HWND hwnd, int x, int y, int dx, int dy, BOOL forw)
{
    HDC hdc;
    HBRUSH hGreyBrush, hBlackBrush;
    HANDLE hOldbrush;

    hdc = GetDC(hwnd);

    if (forw) {
        zug[zugnr].x = x;
        zug[zugnr].y = y;
        zug[zugnr].dx = dx;
        zug[zugnr].dy = dy;
        zugnr++;
        hGreyBrush = CreateSolidBrush(RGB(255, 0, 0));
        hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
        brett[x][y] = 2;
        brett[x + dx + dx][y + dy + dy] = 1;
        brett[x + dx][y + dy] = 1;
    } else {                    /* zug zurücknehmen */
        zugnr--;
        x = zug[zugnr].x;
        y = zug[zugnr].y;
        dx = zug[zugnr].dx;
        dy = zug[zugnr].dy;
        hBlackBrush = CreateSolidBrush(RGB(255, 0, 0));
        hGreyBrush = CreateSolidBrush(RGB(0, 0, 0));
        brett[x][y] = 1;
        brett[x + dx + dx][y + dy + dy] = 2;
        brett[x + dx][y + dy] = 2;
    }

    hOldbrush = SelectObject(hdc, hBlackBrush);
    Ellipse(hdc, dcx1[x][y], dcy1[x][y], dcx2[x][y], dcy2[x][y]);

    SelectObject(hdc, hGreyBrush);
    Ellipse(hdc, dcx1[x + dx][y + dy], dcy1[x + dx][y + dy], dcx2[x + dx][y + dy], dcy2[x + dx][y + dy]);
    Ellipse(hdc, dcx1[x + dx + dx][y + dy + dy], dcy1[x + dx + dx][y + dy + dy],
         dcx2[x + dx + dx][y + dy + dy], dcy2[x + dx + dx][y + dy + dy]);

    SelectObject(hdc, hOldbrush);
    DeleteObject(hGreyBrush);
    DeleteObject(hBlackBrush);

    ReleaseDC(hwnd, hdc);
}

static void setfield(HWND hwnd, int x, int y, int farbe)
{
    HDC hdc;
    HBRUSH hnewBrush;
    HANDLE holdbrush;

    hdc = GetDC(hwnd);

    if (farbe)
        hnewBrush = CreateSolidBrush(RGB(0, 128, 0));
    else
        hnewBrush = CreateSolidBrush(RGB(0, 0, 0));

    holdbrush = SelectObject(hdc, hnewBrush);
    Ellipse(hdc, dcx1[x][y], dcy1[x][y], dcx2[x][y], dcy2[x][y]);

    SelectObject(hdc, holdbrush);
    DeleteObject(hnewBrush);

    ReleaseDC(hwnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    int i, j, x, y;
    BOOL ok;
    static BOOL selected = FALSE;
    static struct {
        int x, y;
    } next;
    static struct {
        int x, y;
    } first;
    static char string2[128], string1[9];
    static HMENU hMenu;
    static HMENU hMenu_englisch;

    switch (message) {
    case WM_CREATE:
        hMenu = GetMenu(hwnd);
        hMenu_englisch = LoadMenu(hInstance, "MENU_ENGLISCH");
        CheckMenuItem(hMenu, IDM_DEUTSCH, MF_CHECKED);
        initboard(7);
        setboard(30, 30, 7);
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        paint(hdc);
        EndPaint(hwnd, &ps);
        return 0;

    case WM_SIZE:
        if (wParam == SIZENORMAL) {
            x = LOWORD(lParam) - 25;
            y = HIWORD(lParam) - 25;

            setboard(x * 6 / 50, y * 6 / 50, 7);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_LBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        if (x < 0 || y < 0)
            return 0;
        ok = FALSE;
        for (i = 0; i <= 6; i++)
            for (j = 0; j <= 6; j++)
                if ((dcx1[i][j] < x)
                    && (dcx2[i][j] > x)
                    && (dcy1[i][j] < y)
                    && (dcy2[i][j] > y)) {
                    ok = TRUE;
                    next.x = i;
                    next.y = j;
                }
        if (ok == FALSE)
            return 0;

        if ((next.x < 2 && next.y < 2) || (next.x > 4 && next.y > 4) ||
            (next.x < 2 && next.y > 4) || (next.x > 4 && next.y < 2)) {
            ok = FALSE;
            return 0;
        }
        if (selected == FALSE)
            if (brett[next.x][next.y] == 2) {
                first.x = next.x;
                first.y = next.y;
                selected = TRUE;
                setfield(hwnd, next.x, next.y, 1);
                return 0;
            } else {
                MessageBox(hwnd, "1. Punkt ist leer", "SOLO", MB_OK);
                return 0;
            }

        /* else selected = TRUE */
        if ((first.x == next.x) && (first.y == next.y)) {
            selected = FALSE;
            setfield(hwnd, first.x, first.y, 0);
            return 0;
        }
        if (brett[next.x][next.y] == 2) {
            selected = FALSE;
            MessageBox(hwnd, "2. Punkt ist besetzt", "SOLO", MB_OK);
            setfield(hwnd, first.x, first.y, 0);
            return 0;
        }
        if (next.x == first.x && abs(next.y - first.y) == 2 && brett[next.x][(next.y + first.y) >> 1] == 2)
            if (next.y > first.y)
                play(hwnd, next.x, next.y, 0, -1, TRUE);
            else
                play(hwnd, next.x, next.y, 0, 1, TRUE);
        else if (next.y == first.y && abs(next.x - first.x) == 2 && brett[(next.x + first.x) >> 1][next.y] == 2) {
            if (next.x > first.x)
                play(hwnd, next.x, next.y, -1, 0, TRUE);
            else
                play(hwnd, next.x, next.y, 1, 0, TRUE);
        } else {
            MessageBox(hwnd, "Inkorrecter Zug!", "SOLO", MB_OK);
            setfield(hwnd, first.x, first.y, 0);
            selected = FALSE;
            return 0;
        }

        selected = FALSE;
        if ((i = endnow(7)) != 0) {
            strcpy(string2, "Steine = ");
            _itoa(i, string1, 10);
            strcat(string2, string1);
            if (i == 1)
                strcat(string2, "\n\n!! BRAVO !!");
            if (i == 2)
                strcat(string2, "\n\nFast geschafft!");
            if (i >= 3)
                strcat(string2, "\n\nDas war's nicht!");
            if (i >= 5)
                strcat(string2, "\nGanz und gar nicht!");            
            MessageBox(hwnd, string2, "SOLO", MB_OK);
        }
        return 0;

    case WM_COMMAND:

        switch (LOWORD(wParam)) {

        case IDM_NEU:
            initboard(7);
            selected = FALSE;
            zugnr = 0;
            InvalidateRect(hwnd, (LPRECT) NULL, TRUE);
            UpdateWindow(hwnd);

            return 0;

        case IDM_UNDO:
            if (selected == TRUE) {
                selected = FALSE;
                setfield(hwnd, first.x, first.y, 0);
            }
            if (zugnr > 0)
                play(hwnd, 0, 0, 0, 0, FALSE);
            return 0;

        case IDM_ENDE:
            SendMessage(hwnd, WM_CLOSE, 0, 0L);
            return 0;

        case IDM_HILFE:
            MessageBox(hwnd,
                       "Erklaerung des Spiels:\n"
                       "Die schwarzen Felder sind die Spielsteine,\n"
                       "die grauen leere Felder.\n"
                       "Bei einem gueltigen Zug springt man mit einem\n"
                       "Stein ueber ein weiteren in einem leeren Feld.\n"
                       "Dabei wird der uebersprungende Stein entfernt.\n"
                       "Ziel des Spieles ist es am Ende nur noch einen\n"
                       "Stein uebrig zu behalten.\n"
                       "\nSpielen eines Steines:\n"
                       "Zuerst den Stein mit der Maus anklicken, dieser\n"
                       "wird etwas heller, dann das Zielfeld anklicken.\n"
                       "Man kann den ersten Stein ein zweites mal an-\n"
                       "waehlen, falls man den Stein doch nicht ziehen will.\n"
                       ,"HILFE", MB_OK);
            return 0;

        case IDM_AUTOR:
            MessageBox(hwnd, "SOL\n"
                       "Version 1.1\n\n"
                       "(c) 1991 Rainer Schnitker",
                       "Autor", MB_OK|MB_ICONINFORMATION);
            return 0;

        case IDM_DEUTSCH:
            SetMenu(hwnd, hMenu);
            CheckMenuItem(hMenu, IDM_ENGLISCH, MF_UNCHECKED);
            CheckMenuItem(hMenu, IDM_DEUTSCH, MF_CHECKED);
            return 0;

        case IDM_ENGLISCH:
            SetMenu(hwnd, hMenu_englisch);
            CheckMenuItem(hMenu_englisch, IDM_DEUTSCH, MF_UNCHECKED);
            CheckMenuItem(hMenu_englisch, IDM_ENGLISCH, MF_CHECKED);
            return 0;

        }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);

}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    hInstance = hInst;

    if (!hPrevInstance) {
        wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_BYTEALIGNCLIENT;
        wndclass.lpfnWndProc = WndProc;
        wndclass.cbClsExtra = 0;
        wndclass.cbWndExtra = 0;
        wndclass.hInstance = hInstance;
        wndclass.hIcon = LoadIcon(hInstance, szAppname);
        wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wndclass.hbrBackground = GetStockObject(GRAY_BRUSH);
        wndclass.lpszMenuName = szAppname;
        wndclass.lpszClassName = szAppname;
        RegisterClass(&wndclass);
    }
    hwnd = CreateWindow(szAppname, szAppname,
                        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
                        50, 10, 300, 340,
                        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
