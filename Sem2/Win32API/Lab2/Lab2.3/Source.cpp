#include <windows.h> 
#include <cmath>
#include <ctime>
#include <cstdio>
#include <string>
#include <vector>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "BALLS";

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
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
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

struct circle
{
	int x;
	int y;
	int r;
	COLORREF c;
	circle(int _x = 0, int _y = 0, COLORREF _c = RGB(255, 255, 255))
	{
		x = _x;
		y = _y;
		r = 10;
		c = _c;
	}
	void draw(HDC hdc)
	{
		HBRUSH hBr = CreateSolidBrush(c);
		HGDIOBJ hOldBr = SelectObject(hdc, hBr);
		Ellipse(hdc, x - r, y - r, x + r, y + r);
		SelectObject(hdc, hOldBr);
		DeleteObject(hBr);
	}
	BOOL hit(HWND hWnd, int _x, int _y)
	{
		if ((_x - x)*(_x - x) + (_y - y)*(_y - y) < r*r)
		{
			r += 10;
			RECT rc = { x - r,y - r, x + r, y + r };
			InvalidateRect(hWnd, &rc, TRUE);
			return TRUE;
		}
		return FALSE;
	}
};

std::vector<circle> vct;
void Paint(HWND hWnd)
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

	for (circle o : vct)
		o.draw(hdcMem);

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
	static BOOL dontcreate = FALSE;
	switch (message)
	{
	case WM_CREATE:
		srand(time(0));
		break;
	case WM_ERASEBKGND:
		return (LRESULT)1;
	case WM_LBUTTONDOWN:
	{
		int
			x = LOWORD(lParam),
			y = HIWORD(lParam);
		for (circle& o : vct)
			if (o.hit(hWnd, x, y))
				dontcreate = TRUE;
		if (!dontcreate)
		{
			vct.push_back(circle(x, y, RGB(rand() % 256, rand() % 256, rand() % 256)));
			RECT r{ x - 10,y - 10,x + 10,y + 10 };
			InvalidateRect(hWnd, &r, TRUE);
		}
		else
			dontcreate = FALSE;
		break; 
	}
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 500;
		lpMMI->ptMinTrackSize.y = 500;
	}
	case WM_PAINT:
		Paint(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
