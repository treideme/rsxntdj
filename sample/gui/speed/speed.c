/*
** this file is changed from c't listing Jan 94 about Win32s
*/

#ifdef __GNUC__
#include <crtrsxnt.h>
#endif

#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define getrandom(min, max) ((rand() % (int)(((max)+1) - (min))) + (min))

char szAppName[] = "speed";
char szTitle[] = "speed test";
HWND hwndMain;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wP, LPARAM lP);
void	CALLBACK DrawPoint(int xPos, int yPos, LONG lpData);
BOOL	InitApplication(HINSTANCE hInstance);
BOOL	InitInstance(HINSTANCE hInstance, int nCmdShow);

void CALLBACK DrawPoint(int xPos, int yPos, LONG lpData)
{
    static int iCount = 0;

    if (++iCount == 8) {
	HDC hdc = (HDC) lpData;

	iCount = 0;
	MoveToEx(hdc, xPos, yPos - 3, NULL);
	LineTo(hdc, xPos, yPos + 3);
	MoveToEx(hdc, xPos - 3, yPos, NULL);
	LineTo(hdc, xPos + 3, yPos);
    }
}

#define MAX_DDA_CALLS 10
void TestProc1(void)
{
    HDC hdc = GetDC(hwndMain);
    int i, j;
    char chBuf[80];
    LINEDDAPROC lpfnDraw;
    RECT rc;

#ifdef __16BIT__
    lpfnDraw = (LINEDDAPROC) MakeProcInstance((FARPROC) DrawPoint,
		     (HINSTANCE) GetWindowLong(hwndMain, GWL_HINSTANCE));
#else
    lpfnDraw = DrawPoint;
#endif

    GetClientRect(hwndMain, &rc);
    for (j = 0; j < MAX_DDA_CALLS; j++) {
        sprintf(chBuf, "Durchlauf: %i", j);
	SetWindowText(hwndMain, chBuf);
	if (j & 1)
	    SelectObject(hdc, GetStockObject(WHITE_PEN));
	else
	    SelectObject(hdc, GetStockObject(BLACK_PEN));
	for (i = 0; i < rc.bottom; i += 8)
	    LineDDA(0, i, rc.right, rc.bottom - i, lpfnDraw, (LPARAM)hdc);
	for (i = 0; i < rc.right; i += 8)
	    LineDDA(i, 0, rc.right - i, rc.bottom, lpfnDraw, (LPARAM)hdc);
    }
    FreeProcInstance((FARPROC) lpfnDraw);
    ReleaseDC(hwndMain, hdc);
    SetWindowText(hwndMain, szTitle);
}

void TestProc2(void)
{
#define POINTS 400
    static POINT apt[POINTS];
    HDC hdc = GetDC(hwndMain);
    int i, j;
    HPEN hpen1;
    char chBuf[80];
    RECT rc;
    GetClientRect(hwndMain, &rc);
    MoveToEx(hdc, 0, 0, NULL);
    for (j = 0; j < 400; j++) {
        sprintf(chBuf, "Durchlauf: %i", j);
	SetWindowText(hwndMain, chBuf);
	for (i = 0; i < POINTS; i++) {
	    apt[i].x = getrandom(0, rc.right);
	    apt[i].y = getrandom(0, rc.bottom);
	}
	if (j & 1)
	    hpen1 = GetStockObject(WHITE_PEN);
	else
	    hpen1 = GetStockObject(BLACK_PEN);
	SelectObject(hdc, hpen1);
	Polyline(hdc, apt, POINTS);
    }
    ReleaseDC(hwndMain, hdc);
    SetWindowText(hwndMain, szTitle);
#undef POINTS
}

#define NUMBER 5000
#define BUF_SIZE  12
#ifdef __EMX__
  #define HUGE_PTR
#else
  #define HUGE_PTR _huge
#endif

typedef struct {
    DWORD val;
    char  achName[BUF_SIZE];
  } SORT;
typedef SORT HUGE_PTR * HPSORT;

void TestProc3(VOID)
{
  HPSORT hpsort;
  HANDLE hp_handle;
  int i,j;
  char chBuf[80];

  hp_handle=GlobalAlloc(GMEM_FIXED,(DWORD)NUMBER*sizeof(SORT));
  if (!hp_handle) {
    MessageBox(NULL, "No memory for test3", szTitle, MB_OK);
    return ;
  }

  hpsort=(HPSORT)GlobalLock(hp_handle);

  for (i=0;i<NUMBER;i++) hpsort[i].val=getrandom(0,30000);
  for (i=1;i<NUMBER;i++ ) {
    if (i%100==0) {
      sprintf(chBuf,"Durchlauf: %i",i);
      SetWindowText(hwndMain,chBuf);
    }
    for (j=i-1;j>=0;j--)
      if (hpsort[j].val>hpsort[j+1].val) {
	SORT temp=hpsort[j];
	hpsort[j]=hpsort[j+1];
	hpsort[j+1]=temp;
      }
  }
  for (i=0;i<NUMBER-1;i++)
    if (hpsort[i].val>hpsort[i+1].val) MessageBeep(0);

  GlobalUnlock(hp_handle);
  GlobalFree(hp_handle);

  SetWindowText(hwndMain,szTitle);
}

typedef void (*TESTPROC)(void);

void DoTest(TESTPROC lpfnTestproc)
{
    DWORD dw = GetTickCount();
    char chBuf[80];
    lpfnTestproc();
    dw = GetTickCount() - dw;
    sprintf(chBuf, "Zeitdauer (ms): %ld", dw);
    MessageBox(NULL, chBuf, szTitle, MB_OK);
    InvalidateRect(hwndMain, NULL, TRUE);
}

void DoAllTests(void)
{
    DWORD dw = GetTickCount();
    char chBuf[80];
    TestProc1();
    TestProc2();
    TestProc3();
    dw = GetTickCount() - dw;
    sprintf(chBuf, "Zeitdauer (ms): %ld", dw);
    MessageBox(NULL, chBuf, szTitle, MB_OK);
    InvalidateRect(hwndMain, NULL, TRUE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wP, LPARAM lP)
{
    PAINTSTRUCT ps;
    HDC hdc;
    char chBuf[80];

    switch (msg) {
    case WM_CHAR:
	if (wP == '1')
	    DoTest(TestProc1);
	else if (wP == '2')
	    DoTest(TestProc2);
	else if (wP=='3')
	    DoTest(TestProc3);
	else if (wP == '0')
	    DoAllTests();
	return 0;
    case WM_PAINT:
	hdc = BeginPaint(hwnd, &ps);
	strcpy(chBuf, "0 = Alle Tests   1 = LineDDA   2 = PolyLine   "
		"3 = BubbleSort");
	TextOut(hdc, 5, 5, chBuf, strlen(chBuf));
	EndPaint(hwnd, &ps);
	return 0;
    case WM_DESTROY:
	PostQuitMessage(0);
	return 0;
    }
    return DefWindowProc(hwnd, msg, wP, lP);

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    if (!InitApplication(hInstance))
	return FALSE;
    if (!InitInstance(hInstance, nCmdShow))
	return FALSE;
    while (GetMessage(&msg, NULL, 0, 0)) {
	TranslateMessage(&msg);
	DispatchMessage(&msg);
    }
    return msg.wParam;
}

BOOL InitApplication(HINSTANCE hInstance)
{
    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szAppName;
    return RegisterClass(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hwndMain = CreateWindow(szAppName, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 440, 440, NULL, NULL, hInstance, NULL);
    if (!hwndMain)
	return FALSE;
    ShowWindow(hwndMain, nCmdShow);
    UpdateWindow(hwndMain);
    return TRUE;
}
