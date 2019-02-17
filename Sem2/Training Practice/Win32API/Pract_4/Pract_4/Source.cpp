#include <windows.h> 
#include <cmath>
#include <cstdio>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "PLOT";
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
	wc.hCursor = NULL;
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

float f(float);
const int NPOINTS = 100;
float
		a = 0.02,
		b = 0.5,
		c = -0.9,
	SCALE,
  X_SCALE,
  Y_SCALE,
     ZOOM = 1,
	X_MIN = -40,
	X_MAX = 40,
	Y_MAX = max(max(f(X_MIN), f(X_MAX)), f(-b/(2*a))),
	Y_MIN = min(min(f(X_MIN), f(X_MAX)), f(-b/(2*a))),
 ACCURACY = (X_MAX - X_MIN) / NPOINTS;

float f(float x)
{
	return a*x*x + b*x + c;
	//return a*sin(x)*sin(x) + b*sin(x) + c;
}

void displayPlot(HWND hWnd, HDC hdc)
{
	RECT rect, txt;
	POINT apt[NPOINTS];
	GetClientRect(hWnd, &rect);
	float
		width = rect.right - rect.left,
		height = rect.bottom - rect.top,
		h = height / 2,
		w = width / 2;

	X_SCALE = width / 64 * ZOOM;
	Y_SCALE = height / 64 * ZOOM;
	SCALE = (X_SCALE + Y_SCALE) / 2;

	HPEN hPen;
	HBRUSH hBrush;
	HFONT hFont;
	HGDIOBJ hOldPen, hOldBrush, hOldFont;

	hPen = CreatePen(PS_SOLID, 1, RGB(180, 180, 180));
	hOldPen = SelectObject(hdc, hPen);
	MoveToEx(hdc, width / 2, 0, NULL);
	LineTo(hdc, width / 2, height);
	MoveToEx(hdc, 0, height / 2, NULL);
	LineTo(hdc, width, height / 2);

	for (int i = X_MIN; i <= X_MAX; i++)
	{
		int x = w + X_SCALE * i;
		MoveToEx(hdc, x, h - log(X_SCALE), NULL);
		LineTo(hdc, x, h + log(X_SCALE));
	}
	for (int i = Y_MIN; i <= Y_MAX; i++)
	{
		int y = h - Y_SCALE * i;
		MoveToEx(hdc, w - log(Y_SCALE), y, NULL);
		LineTo(hdc, w + log(Y_SCALE), y);
	}
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);

	SetBkMode(hdc, TRANSPARENT);
	hPen = CreatePen(PS_DASH, 1, RGB(150, 150, 150));
	hOldPen = SelectObject(hdc, hPen);
	MoveToEx(hdc, w + X_MIN * X_SCALE, 0, NULL);
	LineTo(hdc, w + X_MIN * X_SCALE, height);
	MoveToEx(hdc, w + X_MAX * X_SCALE, 0, NULL);
	LineTo(hdc, w + X_MAX * X_SCALE, height);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);

	hFont = CreateFont(30, 10, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Comic Sans MS");
	hOldFont = SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(200, 200, 200));
	txt = { 0, (int)h, (int)w, (int)height };
	DrawText(hdc, "O", -1, &txt, DT_TOP | DT_RIGHT);
	txt = { 0, 0, (int)w, (int)h };
	DrawText(hdc, "y ", -1, &txt, DT_TOP | DT_RIGHT);
	txt = { (int)w, (int)h, (int)width, (int)height };
	DrawText(hdc, "x ", -1, &txt, DT_TOP | DT_RIGHT);

	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);

	for (int i = 0; i < NPOINTS; i++)
	{
		apt[i].x = w + (X_MIN + i * ACCURACY) * X_SCALE;
		apt[i].y = h - f(X_MIN + i * ACCURACY) * Y_SCALE;
	}

	hPen = CreatePen(PS_SOLID, 2, RGB(100, 100, 250));
	hOldPen = SelectObject(hdc, hPen);
	Polyline(hdc, apt, NPOINTS);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

void elRect(HDC hdc, int x1, int y1, int x2, int y2)
{
	HBRUSH hOldBrush;
	HPEN hPen;
	HGDIOBJ hOldPen, hOldFont;
	SetROP2(hdc, R2_NOTXORPEN);
	SetBkMode(hdc, TRANSPARENT);
	hPen = CreatePen(PS_DOT, 1, RGB(20, 20, 20));
	hOldPen = SelectObject(hdc, hPen);
	SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
	Rectangle(hdc, x1, y1, x2, y2);
	SetROP2(hdc, R2_COPYPEN);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

void drawPt(HWND hWnd, HDC hdc, int ptx, int pty)
{
	HFONT hFont;
	RECT
		rect,
		r = { ptx, pty, ptx + 80, pty + 30 };
	GetClientRect(hWnd, &rect);
	float
		width = rect.right - rect.left,
		height = rect.bottom - rect.top,
		h = height / 2,
		w = width / 2,
		x = (ptx - w) / X_SCALE,
		y = (h - pty) / Y_SCALE;
	HPEN hPen;
	HBRUSH hBrush;
	HGDIOBJ hOldPen, hOldBrush, hOldFont;

	char c[32] = "(", buf[256];
	snprintf(buf, 5, "%f", x);
	strcat_s(c, buf);
	strcat_s(c, ", ");
	snprintf(buf, 5, "%f", y);
	strcat_s(c, buf);
	strcat_s(c, ")");

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(250, 250, 250));
	hFont = CreateFont(16, 6, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Comic Sans MS");
	hOldFont = SelectObject(hdc, hFont);
	DrawText(hdc, c, -1, &r, DT_TOP | DT_CENTER);
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);

	hBrush = CreateSolidBrush(RGB(255, 100, 205));
	hPen = CreatePen(PS_DOT, 1, RGB(180, 50, 100));
	hOldBrush = SelectObject(hdc, hBrush);
	hOldPen = SelectObject(hdc, hPen);
	Ellipse(hdc, ptx - 5, pty - 5, ptx + 5, pty + 5);
	SelectObject(hdc, hOldBrush);
	SelectObject(hdc, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);

	hPen = CreatePen(PS_DOT, 1, RGB(25, 100, 100));
	hOldPen = SelectObject(hdc, hPen);
	SetROP2(hdc, R2_NOTXORPEN);
	MoveToEx(hdc, ptx, h, NULL);
	LineTo(hdc, ptx, pty);
	MoveToEx(hdc, w, pty, NULL);
	LineTo(hdc, ptx, pty);
	SetROP2(hdc, R2_COPYPEN);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

void Paint(HWND hWnd, BOOL bShowCoord, BOOL bTracking, int x1, int y1, int x2, int y2)
{
	RECT rc;
	HDC hdc, hdcMem;
	PCURSORINFO pci;
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

	displayPlot(hWnd, hdcMem);
	if (bShowCoord)
		drawPt(hWnd, hdcMem, x2, y2);
	else if (bTracking)
		elRect(hdcMem, x1, y1, x2, y2);
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

BOOL checkPos(HWND hWnd, int ptx, int pty)
{
	RECT rect, r;
	GetClientRect(hWnd, &rect);
	float
		width = rect.right - rect.left,
		height = rect.bottom - rect.top,
		h = height / 2,
		w = width / 2,
		x = (ptx - w) / X_SCALE,
		y = (h - pty) / Y_SCALE;
	return (x > X_MIN) && (x < X_MAX) && (abs(f(x) - y) < (10.0 / SCALE / ZOOM));
}

float evalX(RECT rect, int ptx)
{
	float w = (rect.right - rect.left) / 2;
	return (ptx - w) / X_SCALE;
}
int fpt(HWND hWnd, int x)
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	return rc.bottom / 2 - Y_SCALE*f(evalX(rc, x));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HCURSOR
		hCurs1 = LoadCursor(NULL, IDC_CROSS),
		hCurs2 = LoadCursor(NULL, IDC_ARROW);
	static int
		x1, y1,
		x2, y2,
		x_stop, y_stop;
	static BOOL
		bTracking,
		bShowCoord,
		bStop;

	switch (message)
	{
	case WM_CREATE:
	{
		SetCursor(hCurs2);
		bTracking = FALSE;
		bShowCoord = FALSE;
		break;
	}

	case WM_ERASEBKGND:
		return (LRESULT)1;

	case WM_LBUTTONDOWN:
	{
		if (!bShowCoord)
		{
			SetCursor(hCurs1);
			bTracking = TRUE;
			x1 = x2 = LOWORD(lParam);
			y1 = y2 = HIWORD(lParam);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break; 
	}

	case WM_LBUTTONUP:
		if (bTracking)
		{
			RECT er;
			bTracking = FALSE;
			InvalidateRect(hWnd, NULL, TRUE);
			x2 = LOWORD(lParam);
			y2 = HIWORD(lParam);
			er = { x1, y1, x2, y2 };
			InvalidateRect(hWnd, &er, TRUE);
			SetCursor(hCurs2);
		}
		break;

	case WM_MOUSEMOVE:
		if (bTracking)
		{
			x2 = LOWORD(lParam);
			y2 = HIWORD(lParam);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		else if (bShowCoord)
		{
			x2 = LOWORD(lParam);
			y2 = fpt(hWnd, x2);
			bStop = checkPos(hWnd, x2, y2);
			if (!bStop)
			{
				x2 = x_stop;
				y2 = y_stop;
			}
			else
			{
				x_stop = x2;
				y_stop = y2;
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else
			SetCursor(hCurs2);
		break;

	case WM_RBUTTONDOWN:
		if (!bTracking)
		{
			x2 = LOWORD(lParam);
			y2 = HIWORD(lParam);
			if (!bShowCoord)
				bShowCoord = checkPos(hWnd, x2, y2);
			if (bShowCoord)
			{
				SetCursor(hCurs1);
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		break;

	case WM_RBUTTONUP:
		if (bShowCoord)
		{
			SetCursor(hCurs2);
			bShowCoord = FALSE;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;

	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 500;
		lpMMI->ptMinTrackSize.y = 500;
	}

	case WM_PAINT:
		Paint(hWnd, bShowCoord, bTracking, x1, y1, x2, y2);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ADD:
			ZOOM *= 1.1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_SUBTRACT:
			ZOOM /= 1.1;
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
