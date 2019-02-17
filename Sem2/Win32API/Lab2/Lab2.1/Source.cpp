#include <windows.h> 
#include <cmath>
#include <cstdio>
#include <string>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "ZOOMTEXT";

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

float SCALE = 10;
void showText(HWND hWnd, HDC hdc, std::string str)
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	HFONT hFont;
	HGDIOBJ hOldFont;
	SetBkMode(hdc, TRANSPARENT);
	hFont = CreateFont(3 * SCALE, SCALE, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Comic Sans MS");
	hOldFont = SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(200, 200, 200));
	DrawText(hdc, str.c_str(), -1, &rc, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);
}

void Paint(HWND hWnd, std::string str)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	RECT rc;
	HDC hdcMem;
	HBITMAP hbmMem;
	HBRUSH hbrBkGnd;
	HGDIOBJ hbmOld;
	GetClientRect(hWnd, &rc);

	hdcMem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);
	hbmOld = SelectObject(hdcMem, hbmMem);

	hbrBkGnd = CreateSolidBrush(BKG_CLR);
	FillRect(hdcMem, &rc, hbrBkGnd);
	DeleteObject(hbrBkGnd);
	SetBkMode(hdcMem, TRANSPARENT);

	showText(hWnd, hdcMem, str);

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
void f(HWND hWnd)
{
	KillTimer(hWnd, 1);
	MessageBox(hWnd, "Reached minimal font size!", "Warning", MB_OK);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT r, er;
	static std::string str = "Some text here";
	switch (message)
	{
	case WM_ERASEBKGND:
		return (LRESULT)1;
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 500;
		lpMMI->ptMinTrackSize.y = 500;
	}
	case WM_PAINT:
		Paint(hWnd, str);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ADD:
			SCALE *= 1.1;
			str += " +";
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_SUBTRACT:
			if ((int)(SCALE / 1.1) > 0)
				SCALE /= 1.1;
			else
			{
				MessageBox(hWnd, "Reached minimal font size!", "Warning", MB_OK);
				//SetTimer(hWnd, 1, 10, (TIMERPROC)f);
				break;
			}
			str.insert(0, "- ");
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
