#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdlib.h>
#include <string.h>

static char szClassName[14] = "Hello, World!";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

class Main
{
    public:
    static HINSTANCE hInstance;
    static HINSTANCE hPrevInstance;
    static int nCmdShow;
    static int MessageLoop(void);
};

class Window
{
    protected:
    HWND hWnd;
    public:
    HWND GetHandle(void) {
	return hWnd;
    }

    BOOL Show(int nCmdShow) {
	return ShowWindow(hWnd, nCmdShow);
    }
    void Update(void) {
	UpdateWindow(hWnd);
    }
    virtual long WndProc(UINT iMessage, WPARAM wParam, LPARAM lParam) = 0;
};

class MainWindow:public Window
{
    public:
    static void Register(void) {
	WNDCLASS wndclass;

	 wndclass.style = CS_HREDRAW | CS_VREDRAW;
         wndclass.lpfnWndProc = ::WndProc;
	 wndclass.cbClsExtra = 0;
	 wndclass.cbWndExtra = sizeof(MainWindow *);
	 wndclass.hInstance = Main::hInstance;
	 wndclass.hIcon = LoadIcon(Main::hInstance, "whello");
	 wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	 wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	 wndclass.lpszMenuName = NULL;
	 wndclass.lpszClassName = szClassName;

	if (!RegisterClass(&wndclass))
	     exit(FALSE);
    }

     MainWindow(void) {
	hWnd = CreateWindow(szClassName,
			    szClassName,
			    WS_OVERLAPPEDWINDOW,
			    CW_USEDEFAULT,
			    CW_USEDEFAULT,
			    CW_USEDEFAULT,
			    CW_USEDEFAULT,
			    NULL,
			    NULL,
			    Main::hInstance,
			    (LPSTR) this);
	if (!hWnd) {
	    MessageBox(NULL, "CreateWindow", NULL, MB_OK);
	    exit(FALSE);
	}
	 Show(Main::nCmdShow);
	Update();
    }
    long WndProc(UINT iMessage, WPARAM wParam, LPARAM lParam);

    void Paint(void);
};

HINSTANCE Main::hInstance = 0;
HINSTANCE Main::hPrevInstance = 0;
int Main::nCmdShow = 0;

int Main::MessageLoop(void)
{
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
	TranslateMessage(&msg);
	DispatchMessage(&msg);
    }
    return msg.wParam;
}

void MainWindow::Paint(void)
{
    PAINTSTRUCT ps;

    static char message[] =
    "GNU C/C++ opens the World of 32-bit Windows Programming!";

    BeginPaint(hWnd, &ps);

    TextOut(ps.hdc, 10, 10, message, sizeof(message) - 1);

    EndPaint(hWnd, &ps);
}

long MainWindow::WndProc(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage) {
	case WM_CREATE:
	break;
    case WM_PAINT:
	Paint();
	break;
    case WM_DESTROY:
	PostQuitMessage(0);
	break;
    default:
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
    }
    return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
				  LPARAM lParam)
{
    Window *pWindow = (Window *) GetWindowLong(hWnd, 0);

    if (pWindow == 0) {
	if (iMessage == WM_CREATE) {
	    LPCREATESTRUCT lpcs;

	    lpcs = (LPCREATESTRUCT) lParam;
	    pWindow = (Window *) lpcs->lpCreateParams;

	    SetWindowLong(hWnd, 0, (LONG) pWindow);

	    return pWindow->WndProc(iMessage, wParam, lParam);
	} else
	    return DefWindowProc(hWnd, iMessage, wParam, lParam);
    } else
	return pWindow->WndProc(iMessage, wParam, lParam);

}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpszCmdLine,
    int nCmdShow)
{
   // disable warning
    lpszCmdLine = lpszCmdLine;

    Main::hInstance = hInstance;
    Main::hPrevInstance = hPrevInstance;
    Main::nCmdShow = nCmdShow;

    if (!Main::hPrevInstance) {
	MainWindow::Register();
    }
    MainWindow MainWnd;

    return Main::MessageLoop();
}
