#include <windows.h>
#include <cstdio>
#include <string>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "TIMER";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	if (!hPrevInstance)
	{
		if (!InitApplication(hInstance))
			return (FALSE);
	}
	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
COLORREF BKG_CLR = RGB(50, 50, 50);
BOOL InitApplication(HINSTANCE hInstance)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(BKG_CLR);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	return RegisterClass(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd = CreateWindow(
		szClassName,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hWnd) return FALSE;
	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);
	return TRUE;
}

void showText(HWND hWnd, HDC hdc, std::string str)
{
	RECT rc;
	GetClientRect(hWnd, &rc);
}

void Paint(HWND hWnd, HDC hdc, std::string str)
{
	RECT rc;
	HDC hdcMem;
	HBITMAP hbmMem;
	HFONT hFont;
	HBRUSH hbrBkGnd, hbr;
	HGDIOBJ hbmOld, hbrold, hOldFont;
	PAINTSTRUCT ps;
	GetClientRect(hWnd, &rc);
	int
		w = rc.right,
		h = rc.bottom,
		scale = w / 16,
		a = w / 8,
		b = a;
	hdc = BeginPaint(hWnd, &ps);
	hdcMem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);
	hbmOld = SelectObject(hdcMem, hbmMem);

	hbrBkGnd = CreateSolidBrush(BKG_CLR);
	FillRect(hdcMem, &rc, hbrBkGnd);
	DeleteObject(hbrBkGnd);
	hbr = CreateSolidBrush(RGB(90,100,100));
	hbrold = SelectObject(hdcMem, hbr);
	Ellipse(hdcMem, w / 2 - a, h / 2 - b, w / 2 + a, h / 2 + b);
	SelectObject(hdcMem, hbrold);
	DeleteObject(hbr);

	SetBkMode(hdcMem, TRANSPARENT);
	hFont = CreateFont(3 * scale, scale, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Comic Sans MS");
	hOldFont = SelectObject(hdcMem, hFont);
	SetTextColor(hdcMem, RGB(200, 200, 200));
	DrawText(hdcMem, str.c_str(), -1, &rc, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);

	BitBlt(hdc,
		rc.left, rc.top,
		rc.right - rc.left, rc.bottom - rc.top,
		hdcMem,
		0, 0,
		SRCCOPY);

	SelectObject(hdcMem, hbmOld);
	DeleteObject(hbmMem);
	DeleteDC(hdcMem);
	EndPaint(hWnd, &ps);
}
#define MY_HOTKEY 100
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	static RECT r, er;
	static std::string str;
	static int clock;
	static BOOL bRun = FALSE, ctrl = FALSE;
	static UINT_PTR timerID;
	switch (message)
	{
	case WM_CREATE:
		RegisterHotKey(hWnd, MY_HOTKEY, MOD_CONTROL, 0x53);
		clock = 0;
		str = std::to_string(clock);
		bRun = TRUE;
		timerID = SetTimer(hWnd, 1, 1000, NULL);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_ERASEBKGND:
		return (LRESULT)1;
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 500;
		lpMMI->ptMinTrackSize.y = 500;
	}
	case WM_PAINT:
		Paint(hWnd, hdc, str);
		break;
	case WM_HOTKEY:
		switch (wParam)
		{
		case MY_HOTKEY:
			bRun = TRUE;
			KillTimer(hWnd, timerID);
			clock = 0;
			str = std::to_string(clock);
			InvalidateRect(hWnd, NULL, TRUE);
			timerID = SetTimer(hWnd, 1, 1000, NULL);
			break;
		}
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ADD:
			if (!bRun)
			{
				bRun = TRUE;
				timerID = SetTimer(hWnd, timerID, 1000, NULL);
			}
			str = std::to_string(clock);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_SUBTRACT:
			if (bRun)
			{
				bRun = FALSE;
				KillTimer(hWnd, timerID);
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		break;
	case WM_TIMER:
		str = std::to_string(++clock);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, timerID);
		PostQuitMessage(0);
		ReleaseDC(hWnd, hdc);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}