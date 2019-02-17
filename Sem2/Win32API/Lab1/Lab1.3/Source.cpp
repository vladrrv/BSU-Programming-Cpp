//#undef UNICODE 
#include <windows.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "1.3";

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
	wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(50,50,50)));
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

void displayDrawings(HWND hWnd)
{
	HDC hdc;
	RECT rect, r;
	PAINTSTRUCT ps;
	LOGBRUSH lbr;
	HPEN hPen;
	HBRUSH hBrush;
	HFONT hFont;
	HGDIOBJ hOldPen, hOldBrush, hOldFont;
	
	hdc = BeginPaint(hWnd, &ps);

	GetClientRect(hWnd, &rect);
	float
		width = rect.right - rect.left,
		height = rect.bottom - rect.top,
		hgint = height / 8,
		wdint = width / 8;
	r = { 0, 0, (int)(width / 2), (int)(height / 2) };
	SetBkMode(hdc, TRANSPARENT);
	hPen = CreatePen(PS_DASHDOTDOT, 1, RGB(150, 150, 150));
	hOldPen = SelectObject(hdc, hPen);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	MoveToEx(hdc, width / 2, 0, NULL);
	LineTo(hdc, width / 2, height);
	MoveToEx(hdc, 0, height / 2, NULL);
	LineTo(hdc, width, height / 2);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);

	hFont = CreateFont(hgint / 2, wdint / 10, 0, 0, FW_DEMIBOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Monotype Corsiva");
	hOldFont = SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(200, 200, 200));
	DrawText(hdc, "Ellipse", -1, &r, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
	r.left = width / 2;
	r.right = width;
	DrawText(hdc, "Rectangle", -1, &r, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
	r.top = height / 2;
	r.bottom = height;
	DrawText(hdc, "Rhomb", -1, &r, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
	r.left = 0;
	r.right = width / 2;
	DrawText(hdc, "Pie", -1, &r, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);

	hPen = CreatePen(PS_DASH, 1, RGB(255, 0, 0));
	hBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(145, 100, 0));
	hOldPen = SelectObject(hdc, hPen);
	hOldBrush = SelectObject(hdc, hBrush);
	SetDCBrushColor(hdc, RGB(255, 200, 0));
	Ellipse(hdc, wdint, hgint, width / 2 - wdint, height / 2 - hgint);
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);

	hPen = CreatePen(PS_SOLID, 2, RGB(50, 200, 0));
	hBrush = CreateHatchBrush(HS_CROSS, RGB(50, 100, 0));
	hOldPen = SelectObject(hdc, hPen);
	hOldBrush = SelectObject(hdc, hBrush);
	Rectangle(hdc, width / 2 + wdint, hgint, width - wdint, height / 2 - hgint);
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);

	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 50));
	hBrush = CreateHatchBrush(HS_HORIZONTAL, RGB(100, 100, 0));
	hOldPen = SelectObject(hdc, hPen);
	hOldBrush = SelectObject(hdc, hBrush);
	MoveToEx(hdc, width / 4 - width / 8, 3 * height / 4, NULL);
	AngleArc(hdc, width / 4 - width / 8, 3 * height / 4, width / 4, -15, 30);
	LineTo(hdc, width / 4 - width / 8, 3 * height / 4);
	AngleArc(hdc, width / 4 - width / 8, 3 * height / 4, width / 4, -15, 30.3);
	ExtFloodFill(hdc, width / 4, 3 * height / 4, RGB(50, 50, 50), FLOODFILLSURFACE);
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);

	POINT coord[] =
	{ 
		{ width / 2 + wdint, 3 * height / 4 },
		{3 * width / 4, height / 2 + hgint},
		{ width - wdint, 3 * height / 4 },
		{ 3 * width / 4, height - hgint } 
	};
	hPen = CreatePen(PS_DOT, 1, RGB(100, 100, 255));
	hBrush = CreateSolidBrush(RGB(0, 0, 105));
	hOldPen = SelectObject(hdc, hPen);
	hOldBrush = SelectObject(hdc, hBrush);
	Polygon(hdc, coord, 4);
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);

	EndPaint(hWnd, &ps);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 500;
		lpMMI->ptMinTrackSize.y = 500;
	}
	case WM_PAINT:
		displayDrawings(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}