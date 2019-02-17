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
	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE - 1);
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
	RECT rect, cur;
	PAINTSTRUCT ps;
	int 
		width,
		height,
		clrR = 80,
		clrG = 70,
		clrB = 55;
	float
		step,
		newWidth,
		newHeight;

	LPSTR
		ell = "Ellipse";
	HPEN hPen;
	HBRUSH hBrush;
	HGDIOBJ hOldPen, hOldBrush;

	GetClientRect(hWnd, &rect);
	width = (rect.right - rect.left);
	height = (rect.bottom - rect.top);
	newWidth = width;
	newHeight = height;

	hdc = BeginPaint(hWnd, &ps);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 100));
	hOldPen = SelectObject(hdc, hPen);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
	while (newWidth > width / 2 && newHeight > height / 2)
	{
		step = ((float)width / GetSystemMetrics(SM_CXMAXIMIZED) + (float)height / GetSystemMetrics(SM_CYMAXIMIZED))*2;
		hBrush = CreateSolidBrush(RGB(clrR++, clrG++, clrB));
		hOldBrush = SelectObject(hdc, hBrush);
		newWidth -= step;
		newHeight -= step;
		SetRect(&cur, width - (int)newWidth, height - (int)newHeight, (int)newWidth, (int)newHeight);
		FillRect(hdc, &cur, hBrush);
		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);
	}
	
	EndPaint(hWnd, &ps);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
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