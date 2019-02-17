#include <windows.h> 
#include <cmath>
#include <ctime>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "Pulsing Circles";
COLORREF BKG_CLR = RGB(50, 50, 50);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(0));
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
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		700,
		700,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hWnd) return FALSE;
	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);
	return TRUE;
}

struct circle
{
	int id;
	int x;
	int y;
	int r;
	int sr;
	COLORREF c;
	BOOL pulsing;
	BOOL expanding;
	circle(int _x = 0, int _y = 0, int _r = 40, COLORREF _c = RGB(255, 255, 255))
	{
		static int count = 0;
		id = ++count;
		x = _x;
		y = _y;
		r = _r;
		sr = r;
		c = _c;
		pulsing = FALSE;
	}
	void draw(HDC hdc)
	{
		HBRUSH hBr = CreateSolidBrush(c);
		SelectObject(hdc, hBr);
		Ellipse(hdc, x - r, y - r, x + r, y + r);
		DeleteObject(hBr);
	}
	BOOL hit(HWND hWnd, int _x, int _y)
	{
		COLORREF _c = GetPixel(GetDC(hWnd), _x, _y);

		//if ((_x - x)*(_x - x) + (_y - y)*(_y - y) < r*r)
		if (_c == c)
		{
			if (!pulsing)
			{
				pulsing = TRUE;
				expanding = TRUE;
				SetTimer(hWnd, id, 10, NULL);
			}
			else
			{
				pulsing = FALSE;
				expanding = FALSE;
				KillTimer(hWnd, id);
				r = sr;
				RECT rc = { x - r - 10, y - r - 10, x + r + 10, y + r + 10 };
				InvalidateRect(hWnd, &rc, TRUE);
			}

			return TRUE;
		}
		return FALSE;
	}
};

vector<circle> vct;

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

	for (circle& o : vct)
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
	switch (message)
	{
	case WM_CREATE:
	{
		for (int i = 0; i < 3; i++)
			vct.push_back(circle(100 + rand() % 500, 100 + rand() % 500, 20 + rand() % 40, RGB(rand() % 256, rand() % 256, rand() % 256)));
		break;
	}

	case WM_ERASEBKGND:
		return (LRESULT)1;

	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 700;
		lpMMI->ptMinTrackSize.y = 700;
		break;
	}

	case WM_LBUTTONDOWN:
	{
		int
			x = LOWORD(lParam),
			y = HIWORD(lParam);
		for (circle& o : vct)
			if (!o.pulsing)
				o.hit(hWnd, x, y);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		int
			x = LOWORD(lParam),
			y = HIWORD(lParam);
		for (circle& o : vct)
			if (o.pulsing)
				o.hit(hWnd, x, y);
		break;
	}
	case WM_PAINT:
		Paint(hWnd);
		break;
	case WM_TIMER:
	{
		RECT rc;
		vector<circle>::iterator it = find_if(vct.begin(), vct.end(), [=](const circle& o) {return o.id == wParam; });
		if (it->r <= it->sr + 10 && it->expanding)
		{
			it->r += 1;
			rc = { it->x - it->r, it->y - it->r, it->x + it->r, it->y + it->r };
		}
		else
		{
			it->expanding = FALSE;
			rc = { it->x - it->r, it->y - it->r, it->x + it->r, it->y + it->r };
			it->r -= 1;
			if (it->r == it->sr)
				it->expanding = TRUE;
		}

		InvalidateRect(hWnd, &rc, TRUE);
		break;
	}
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
