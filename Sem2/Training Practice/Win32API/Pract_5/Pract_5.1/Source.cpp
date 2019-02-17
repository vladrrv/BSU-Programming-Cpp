#include <windows.h> 
#include <windowsx.h> 
#include <cmath>
#include <cstdio>
#include <string>
#include <commctrl.h>
#include "resource.h"

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
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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

int COL = 0, SPEED = 1, RAD = 40;

void Paint(HWND hWnd, int x, int y)
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
		x = -x;
	SelectObject(hdcMem, GetStockObject(DC_BRUSH));
	SelectObject(hdcMem, GetStockObject(DC_PEN));
	switch (COL)
	{
	case 0:
		SetDCBrushColor(hdcMem, RGB(200, 40, 40));
		break;
	case 1:
		SetDCBrushColor(hdcMem, RGB(40, 200, 40));
		break;
	case 2:
		SetDCBrushColor(hdcMem, RGB(40, 40, 200));
		break;
	default:
		SetDCBrushColor(hdcMem, RGB(200, 200, 200));
		break;
	}
	SetDCPenColor(hdcMem, RGB(0, 100, 0));
	Ellipse(hdcMem, x - RAD, y - RAD, x + RAD, y + RAD);

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

BOOL CALLBACK ChangeParams(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int
		old_color = 0,
		old_speed = 0,
		old_pos = 0,
		old_rad = 0,
		pos = 1,
		wpar = 0;
	switch (message)
	{
	case WM_INITDIALOG:
	{
		old_rad = RAD;
		old_color = COL;
		old_speed = SPEED;
		old_pos = pos;
		SetDlgItemText(hdlg, IDC_EDIT1, std::to_string(RAD).c_str());
		SendDlgItemMessage(hdlg, IDC_SLIDER1, TBM_SETPOS, 1, pos);
		switch (COL)
		{
		case 0:
			SendDlgItemMessage(hdlg, IDC_RADIO1, BM_SETCHECK, 1, 0);
			break;
		case 1:
			SendDlgItemMessage(hdlg, IDC_RADIO2, BM_SETCHECK, 1, 0);
			break;
		case 2:
			SendDlgItemMessage(hdlg, IDC_RADIO3, BM_SETCHECK, 1, 0);
			break;
		}
		break;
	}
	case WM_HSCROLL:
	{
		wpar = HIWORD(wParam);
		if (wpar != 0)
		{
			pos = wpar;
			SPEED = pos;
		}
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hdlg, 0);
			break;
		case IDCANCEL:
			pos = old_pos;
			RAD = old_rad;
			COL = old_color;
			SPEED = old_speed;
			EndDialog(hdlg, 0);
			break;
		case IDC_RADIO1:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				SendDlgItemMessage(hdlg, IDC_RADIO1, BM_SETCHECK, 1, 0);
				COL = 0;
				break;
			}
			break;
		case IDC_RADIO2:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				SendDlgItemMessage(hdlg, IDC_RADIO2, BM_SETCHECK, 1, 0);
				COL = 1;
				break;
			}
			break;
		case IDC_RADIO3:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				SendDlgItemMessage(hdlg, IDC_RADIO3, BM_SETCHECK, 1, 0);
				COL = 2;
				break;
			}
			break;
		}

		switch (HIWORD(wParam))
		{
		case EN_CHANGE:
		{
			char c[32];
			int r = 0;
			Edit_GetLine((HWND)lParam, 0, c, 32);
			r = atoi(c);
			if (r != 0)
				RAD = r;
			break;
		}
		}
		break;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int
		x = RAD, y = 0, inc = 1;
	int r = RAD;
	static RECT rc;
	static BOOL bStop = FALSE;
	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hWnd, 1, 1, NULL);
		break;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_PARAMETERS_CHANGE:
			DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, ChangeParams);
			break;
		}
		break;
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
		if (!bStop)
		{
			y = rc.bottom / 2 - 100 * sin((float)x / 100.0);
			x += inc*SPEED;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	}
	case WM_PAINT:
		GetClientRect(hWnd, &rc);
		if (x + r > rc.right)
		{
			x = rc.right - r;
			inc = -1;
		}
		if (x - r < rc.left)
		{
			x = rc.left + r;
			inc = 1;
		}
		Paint(hWnd, x, y);
		break;

	case WM_RBUTTONDOWN:
	{
		bStop = !bStop;
		break;
	}
	case WM_DESTROY:
	{
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
