#include <windows.h>
#include <cmath>
#include <cstdio>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "Moving Car";
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

float
SPEED = 10;

void drawCar(RECT rc, HDC hdc, int x, int y, float a)
{
	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(100, 100, 100));
	HBRUSH hBrWheel = CreateSolidBrush(RGB(30, 30, 30));
	HBRUSH hBrush = CreateSolidBrush(RGB(min(min(rc.right - x, x), 250), 100, 105));
	HGDIOBJ hOldPen, hOldBrush;
	hOldBrush = SelectObject(hdc, hBrush);
	hOldPen = SelectObject(hdc, hPen);
	a *= 3.14 / 180;
	Rectangle(hdc, x - 200, y - 50, x + 200, y + 50);
	Rectangle(hdc, x - 100, y - 50, x + 100, y - 150);
	int x1 = x + 140,
		y1 = y + 70,
		x2 = x - 140,
		y2 = y1;

	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
	
	hOldPen = SelectObject(hdc, hPen);
	hOldBrush = SelectObject(hdc, hBrWheel);
	Ellipse(hdc, x1 - 40, y1 - 40, x1 + 40, y1 + 40);
	Ellipse(hdc, x1 - 10, y1 - 10, x1 + 10, y1 + 10);
	Ellipse(hdc, x2 - 40, y2 - 40, x2 + 40, y2 + 40);
	Ellipse(hdc, x2 - 10, y2 - 10, x2 + 10, y2 + 10);
	int x0 = 20 * cos(a),
		y0 = 20 * sin(a);
	Ellipse(hdc, x1 - x0 - 5, y1 - y0 - 5, x1 - x0 + 5, y1 - y0 + 5);
	Ellipse(hdc, x1 + x0 - 5, y1 + y0 - 5, x1 + x0 + 5, y1 + y0 + 5);
	Ellipse(hdc, x2 - x0 - 5, y2 - y0 - 5, x2 - x0 + 5, y2 - y0 + 5);
	Ellipse(hdc, x2 + x0 - 5, y2 + y0 - 5, x2 + x0 + 5, y2 + y0 + 5);

	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrWheel);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

void Paint(HWND hWnd, int x, int y, float a, float t, BOOL bTrans)
{
	t *= 3.14 / 180;
	RECT rc;
	HPEN hPen;
	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	HBITMAP hbmMem;
	HBRUSH hbrBkGnd;
	HGDIOBJ hbmOld;
	hdc = BeginPaint(hWnd, &ps);
	GetClientRect(hWnd, &rc);

	float
		h = rc.bottom,
		w = rc.right,
		b = atan(h / w),
		s = sqrt(w*w + h*h)*sin(t / 2),
		dh = s*cos(t / 2 + b),
		dw = s*sin(t / 2 + b);

	XFORM xForm{ cos(t), sin(t), -sin(t), cos(t), dw, -dh };
	SetGraphicsMode(hdc, GM_ADVANCED);
	SetWorldTransform(hdc, &xForm);

	hdcMem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);
	hbmOld = SelectObject(hdcMem, hbmMem);

	hbrBkGnd = CreateSolidBrush(BKG_CLR);
	FillRect(hdcMem, &rc, hbrBkGnd);
	DeleteObject(hbrBkGnd);
	SetBkMode(hdcMem, TRANSPARENT);
	
	if (bTrans)
		hPen = CreatePen(PS_SOLID, 3, RGB(50, 180, 50));
	else
		hPen = CreatePen(PS_SOLID, 3, RGB(180, 50, 50));

	SelectObject(hdcMem, hPen);
	SelectObject(hdcMem, GetStockObject(HOLLOW_BRUSH));
	Ellipse(hdcMem, 0, (rc.bottom - rc.right) / 2, rc.right, (rc.bottom + rc.right) / 2);
	DeleteObject(hPen);

	if (bTrans)
		drawCar(rc, hdcMem, (x > 200) ? x - (rc.right - rc.left) : x + (rc.right - rc.left), y, a);
	drawCar(rc, hdcMem, x, y, a);
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
		x = 200, y = 0, a = 0, t = 0, inc = 5;
	static RECT rc, r;
	static BOOL bTrans = TRUE, bBoost = FALSE;

	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hWnd, 1, 100, NULL);
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

		if (!bTrans)
		{
			if (abs(x) + 200 >= rc.right)
				inc = -inc;
			if (abs(x) - 200 < rc.left)
				inc = -inc;
		}
		x+=inc;
		if (x > rc.right + 200 && rc.right != 0)
			x %= rc.right;
		else if (x < -200)
			x += rc.right;
		r = { 0, y - 300, rc.right, y + 300 };
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_PAINT:
		GetClientRect(hWnd, &rc);
		y = rc.bottom / 2;
		Paint(hWnd, x, y, a, t, bTrans);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ADD:
			KillTimer(hWnd, 1);
			if (SPEED >= 500)
			{
				bBoost = TRUE;
				inc += (inc>0)? 2: -2;
				SetTimer(hWnd, 1, 1, NULL);
			}
			else
			{
				SPEED *= 2.0;
				SetTimer(hWnd, 1, 1000.0 / SPEED, NULL);
			}
			break;
		case VK_SUBTRACT:
			KillTimer(hWnd, 1);
			if (SPEED / 2.0 > 0.01 && !bBoost)
			{
				SPEED /= 2.0;
				SetTimer(hWnd, 1, 1000.0 / SPEED, NULL);
			}
			else if (bBoost)
			{
				if (abs(inc) != 5)
					inc += (inc > 0) ? -2 : 2;
				else
					bBoost = FALSE;
				SetTimer(hWnd, 1, 1000.0 / SPEED, NULL);
			}
			break;
		case VK_SPACE:
			bTrans = !bTrans;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_UP:
			t += 10;
			t %= 360;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_DOWN:
			t -= 10;
			t %= 360;
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
