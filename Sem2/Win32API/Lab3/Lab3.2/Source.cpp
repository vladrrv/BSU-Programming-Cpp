#include <windows.h> 
#include <cmath>
#include <cstdio>
#include <string>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "TrafficLights";
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
		250,
		750,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hWnd) return FALSE;
	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);
	return TRUE;
}

void Paint(HWND hWnd,
	HBRUSH hBrDRed,	HBRUSH hBrDYellow,	HBRUSH hBrDGreen,
	HBRUSH hBrRed,	HBRUSH hBrYellow,	HBRUSH hBrGreen,
	BOOL bRed, BOOL bYellow, BOOL bGreen,
	HFONT hFont, std::string str)
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
	/**/
	SelectObject(hdcMem, hFont);
	SetTextColor(hdcMem, RGB(200, 200, 200));
	DrawText(hdcMem, str.c_str(), -1, &rc, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	if (bRed)
	{
		SelectObject(hdcMem, hBrRed);
		Ellipse(hdcMem, 5, 5, rc.right - 5, rc.bottom / 3 - 5);
	}
	if (bYellow)
	{
		SelectObject(hdcMem, hBrYellow);
		Ellipse(hdcMem, 5, rc.bottom / 3 + 5, rc.right - 5, 2 * rc.bottom / 3 - 5);
	}
	if (bGreen)
	{
		SelectObject(hdcMem, hBrGreen);
		Ellipse(hdcMem, 5, 2 * rc.bottom / 3 + 5, rc.right - 5, rc.bottom - 5);
	}
	SelectObject(hdcMem, hBrDRed);
	Ellipse(hdcMem, 5, 5, rc.right - 5, rc.bottom / 3 - 5);
	SelectObject(hdcMem, hBrDYellow);
	Ellipse(hdcMem, 5, rc.bottom / 3 + 5, rc.right - 5, 2 * rc.bottom / 3 - 5);
	SelectObject(hdcMem, hBrDGreen);
	Ellipse(hdcMem, 5, 2 * rc.bottom / 3 + 5, rc.right - 5, rc.bottom - 5);


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
	static std::string str;
	static int clock = 11;
	static HFONT hFont = CreateFont(240, 80, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Comic Sans MS");
	static HBRUSH
		hBrDRed = CreateHatchBrush(HS_DIAGCROSS, RGB(100, 40, 40)),
		hBrDYellow = CreateHatchBrush(HS_DIAGCROSS, RGB(80, 80, 40)),
		hBrDGreen = CreateHatchBrush(HS_DIAGCROSS, RGB(40, 80, 40)),
		hBrRed = CreateSolidBrush(RGB(180, 0, 0)),
		hBrYellow = CreateSolidBrush(RGB(180, 160, 0)),
		hBrGreen = CreateSolidBrush(RGB(0, 140, 0));
	static UINT_PTR timer1, timer2, timer3;
	static BOOL
		bRed = TRUE,
		bYellow = FALSE,
		bGreen = FALSE;

	switch (message)
	{
	case WM_CREATE:
	{
		timer2 = SetTimer(hWnd, 2, 1000, NULL);
		break;
	}

	case WM_ERASEBKGND:
		return (LRESULT)1;

	case WM_GETMINMAXINFO:
	{
		int h = GetSystemMetrics(SM_CYMAXIMIZED);
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.y = 750;
		lpMMI->ptMinTrackSize.x = 250;
		lpMMI->ptMaxTrackSize.y = h;
		lpMMI->ptMaxTrackSize.x = h / 3;
	}
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1:
			if (bRed && !bYellow)
				bYellow = TRUE;
			else if (bRed && bYellow)
			{
				bRed = FALSE;
				bYellow = FALSE;
				bGreen = TRUE;
				KillTimer(hWnd, timer1);
			}
			else if (bYellow)
			{
				bYellow = FALSE;
				bRed = TRUE;
				KillTimer(hWnd, timer1);
			}
			else
			{
				KillTimer(hWnd, timer3);
				bYellow = TRUE;
				bGreen = FALSE;
			}
			break;
		case 2:
			str = std::to_string(--clock);
			if (clock == 1)
			{
				clock = 12;
				timer1 = SetTimer(hWnd, 1, 1000, NULL);
			}
			if (clock == 4 && bGreen)
				timer3 = SetTimer(hWnd, 3, 600, NULL);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 3:
			bGreen = !bGreen;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_PAINT:
		Paint(hWnd,
			hBrDRed, hBrDYellow, hBrDGreen,
			hBrRed, hBrYellow, hBrGreen,
			bRed, bYellow, bGreen,
			hFont, str);
		break;

	case WM_DESTROY:
		DeleteObject(hBrDRed);
		DeleteObject(hBrDYellow);
		DeleteObject(hBrDGreen);
		DeleteObject(hBrRed);
		DeleteObject(hBrYellow);
		DeleteObject(hBrGreen);
		DeleteObject(hFont);
		KillTimer(hWnd, timer1);
		KillTimer(hWnd, timer2);
		KillTimer(hWnd, timer3);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
