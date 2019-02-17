#include <windows.h> 
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "Moving Ball";
COLORREF BKG_CLR = RGB(50, 50, 50);

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
	ShowWindow(hWnd, SW_MAXIMIZE);
	UpdateWindow(hWnd);
	return TRUE;
}

void Paint(HWND hWnd, int x, int y, float a)
{
	RECT rc;
	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	hdc = BeginPaint(hWnd, &ps);
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

	if (x < 0)
	{
		x = -x;
		a = 360-a;
	}
	a = a*3.14 / 180;
	SelectObject(hdcMem, GetStockObject(DC_BRUSH));
	SelectObject(hdcMem, GetStockObject(DC_PEN));
	SetDCBrushColor(hdcMem, RGB(40, 200, 40));
	SetDCPenColor(hdcMem, RGB(0, 100, 0));
	Ellipse(hdcMem, x - 40, y - 40, x + 40, y + 40);
	MoveToEx(hdcMem, x, y, NULL);
	LineTo(hdcMem, x+40*cos(a), y+40*sin(a));

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int
		x=40, y=-40, a = 0, inc = 2, r = 40;
	static RECT rc;
	static BOOL bStop = FALSE;
	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hWnd, 1, 1, NULL);
		break;
	}

	case WM_ERASEBKGND:
		return (LRESULT)1;

	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 500;
		lpMMI->ptMinTrackSize.y = 500;
		break;
	}
	case WM_TIMER:
	{
		a += inc;
		a %= 360;
		y = rc.bottom/2-100*sin((float)x/100.0);
		x += inc;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_PAINT:
		GetClientRect(hWnd, &rc);
		if (x + r > rc.right)
		{
			x = rc.right - r;
			inc = -2;
		}
		if (x - r < rc.left)
		{
			x = rc.left + r;
			inc = 2;
		}
		Paint(hWnd, x, y, a);
		break;

	case WM_RBUTTONDOWN:
	{
		if (!bStop)
		{
			KillTimer(hWnd, 1);
			bStop = TRUE;
		}
		else
		{
			SetTimer(hWnd, 1, 1, NULL);
			bStop = FALSE;
		}
		break;
	}
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
