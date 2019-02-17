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
	RECT rect;
	PAINTSTRUCT ps;
	HFONT hFont;
	HGDIOBJ hOldFont;

	hdc = BeginPaint(hWnd, &ps);

	GetClientRect(hWnd, &rect);
	float
		width = rect.right - rect.left,
		height = rect.bottom - rect.top,
		hgint = height / 16,
		wdint = width / 32;

	hFont = CreateFont(hgint, wdint/2, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");
	SetBkMode(hdc, TRANSPARENT);
	hOldFont = SelectObject(hdc, hFont);

	DrawText(hdc, "Center", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DrawText(hdc, "TopLeft", -1, &rect, DT_SINGLELINE | DT_LEFT  | DT_TOP);
	DrawText(hdc, "TopRight", -1, &rect, DT_SINGLELINE | DT_RIGHT | DT_TOP);
	DrawText(hdc, "BottomLeft", -1, &rect, DT_SINGLELINE | DT_LEFT | DT_BOTTOM);
	DrawText(hdc, "BottomRight", -1, &rect, DT_SINGLELINE | DT_RIGHT | DT_BOTTOM);

	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);
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