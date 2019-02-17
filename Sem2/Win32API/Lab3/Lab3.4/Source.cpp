#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <windows.h>
#include <windowsx.h> 
#include <commctrl.h>
#include <cmath>
#include <cstdio>
#include <string>
#include "resource.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "PLOT";
COLORREF BKG_CLR = RGB(50, 50, 50);

HWND hwndMain;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	if (!hPrevInstance)
	{
		if (!InitApplication(hInstance))
			return (FALSE);
	}
	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateAccelerator(hwndMain, hAccel, &msg);
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
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = szClassName;
	return RegisterClass(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hwndMain = CreateWindow(
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
	if (!hwndMain) return FALSE;
	ShowWindow(hwndMain, SW_NORMAL);
	UpdateWindow(hwndMain);
	return TRUE;
}

const int NPOINTS = 1000;
float
a = 3,
b = 1.2,
c = -1,
SCALE = 1,
X_SCALE = 1,
Y_SCALE = 1,
X_DELTA = 0,
Y_DELTA = 0,
ZOOM = 1,
X_MIN = -40,
X_MAX = 30,
ACCURACY = (X_MAX - X_MIN) / NPOINTS;
POINT apt[NPOINTS];
int FUNC = -1;
COLORREF PLOTCOLOR = RGB(180, 180, 180);
unsigned THICKNESS = 1;

float f(float x)
{
	switch (FUNC)
	{
	case 0:
		return a*x*x + b*x + c;
	case 1:
		return a*sin(b*x)*x + c;
	case 2:
		return a*sin(x) + b*x;
	case 3:
		return pow(b, x);
	case 4:
		return a*atan(x);
	default:
		return 0;
	}
}

BOOL checkPos(HWND hWnd, int ptx, int pty)
{
	float
		h = Y_DELTA,
		w = X_DELTA,
		x = (ptx - w) / X_SCALE,
		y = (pty + h) / Y_SCALE;
	return (x > X_MIN) && (x < X_MAX) && (abs(f(x) - y) < (16.0 / SCALE));
}

float evalX(int ptx)
{
	float w = X_DELTA;
	return (ptx - w) / X_SCALE;
}
float evalY(int pty)
{
	float h = Y_DELTA;
	return (pty + h) / Y_SCALE;
}
int fpt(HWND hWnd, int x)
{
	return (float)Y_DELTA + (float)Y_SCALE*f(evalX(x));
}

void recalcPts(RECT rc)
{
	float
		halfwidth = (rc.right - rc.left) / 2,
		halfheight = (rc.bottom - rc.top) / 2;
	X_SCALE = halfwidth / 32 * ZOOM;
	Y_SCALE = halfheight / 32 * ZOOM;
	SCALE = (X_SCALE + Y_SCALE) / 2;
	ACCURACY = (X_MAX - X_MIN) / NPOINTS;
	for (int i = 0; i < NPOINTS; i++)
	{
		int x = X_DELTA + (X_MIN + i * ACCURACY) * X_SCALE,
			y = Y_DELTA + f(X_MIN + i * ACCURACY) * Y_SCALE;
		apt[i].x = (x > halfwidth) ? halfwidth + 1 : (x < -halfwidth) ? -halfwidth - 1 : x;
		apt[i].y = (y > halfheight) ? halfheight + 1 : (y < -halfheight) ? -halfheight - 1 : y;
	}
}
void displayPlot(RECT rc, HDC hdc)
{
	RECT txt;
	HPEN hPen;
	HFONT hFont;
	HGDIOBJ hOldPen, hOldFont;
	int
		halfwidth = (rc.right - rc.left) / 2,
		halfheight = (rc.bottom - rc.top) / 2;
	float
		width = halfwidth * 2,
		height = halfheight * 2,
		h = Y_DELTA,
		w = X_DELTA;
	float
		xh = 20 + log(X_SCALE),
		yh = 20 + log(Y_SCALE);

	hPen = CreatePen(PS_SOLID, 1, RGB(180, 180, 180));
	hOldPen = SelectObject(hdc, hPen);
	MoveToEx(hdc, w, -halfheight, NULL);
	LineTo(hdc, w, halfheight);
	MoveToEx(hdc, -halfwidth, h, NULL);
	LineTo(hdc, halfwidth, h);

	hFont = CreateFont(xh, xh / 3, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Comic Sans MS");
	hOldFont = SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(100, 100, 100));

	for (int i = 0; i >= evalX(-halfwidth); i -= (int)(40.0 / X_SCALE + 1))
	{
		int x = w + X_SCALE * i;
		char c[32];
		_itoa_s(i, c, 10);
		MoveToEx(hdc, x, h - log(X_SCALE), NULL);
		LineTo(hdc, x, h + log(X_SCALE));
		txt = { (int)(x - xh / 5.0 * strlen(c)), (int)h, (int)(x + xh / 5.0 * strlen(c)), (int)(h - xh) };
		DrawText(hdc, c, -1, &txt, DT_SINGLELINE | DT_TOP | DT_LEFT);
	}
	for (int i = 0; i <= evalX(halfwidth); i += (int)(40.0 / X_SCALE + 1))
	{
		int x = w + X_SCALE * i;
		char c[32];
		_itoa_s(i, c, 10);
		MoveToEx(hdc, x, h - log(X_SCALE), NULL);
		LineTo(hdc, x, h + log(X_SCALE));
		txt = { (int)(x - xh / 5.0 * strlen(c)), (int)h, (int)(x + xh / 5.0 * strlen(c)), (int)(h - xh) };
		DrawText(hdc, c, -1, &txt, DT_SINGLELINE | DT_TOP | DT_LEFT);
	}

	hFont = CreateFont(yh, yh / 3, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Comic Sans MS");
	hOldFont = SelectObject(hdc, hFont);

	for (int i = 0; i >= evalY(-halfheight); i -= (int)(40.0 / Y_SCALE + 1))
	{
		int y = h - Y_SCALE * i;
		char c[32];
		_itoa_s(i, c, 10); strcat_s(c, " ");
		MoveToEx(hdc, w - log(Y_SCALE), y, NULL);
		LineTo(hdc, w + log(Y_SCALE), y);
		txt = { (int)(w - (yh / 3)*strlen(c)), (int)(y + yh / 2), (int)w, (int)(y - yh / 2) };
		if (i != 0)
			DrawText(hdc, c, -1, &txt, DT_SINGLELINE | DT_TOP | DT_RIGHT);
	}
	for (int i = 0; i <= evalY(halfheight); i += (int)(40.0 / Y_SCALE + 1))
	{
		int y = h - Y_SCALE * i;
		char c[32];
		_itoa_s(i, c, 10); strcat_s(c, " ");
		MoveToEx(hdc, w - log(Y_SCALE), y, NULL);
		LineTo(hdc, w + log(Y_SCALE), y);
		txt = { (int)(w - (yh / 3)*strlen(c)), (int)(y + yh / 2), (int)w, (int)(y - yh / 2) };
		if (i != 0)
			DrawText(hdc, c, -1, &txt, DT_SINGLELINE | DT_TOP | DT_RIGHT);
	}

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);

	SetBkMode(hdc, TRANSPARENT);
	hPen = CreatePen(PS_DASH, 1, RGB(150, 150, 150));
	hOldPen = SelectObject(hdc, hPen);
	MoveToEx(hdc, w + X_MIN * X_SCALE, -halfheight, NULL);
	LineTo(hdc, w + X_MIN * X_SCALE, halfheight);
	MoveToEx(hdc, w + X_MAX * X_SCALE, -halfheight, NULL);
	LineTo(hdc, w + X_MAX * X_SCALE, halfheight);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);

	hFont = CreateFont(30, 10, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Comic Sans MS");
	hOldFont = SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(200, 200, 200));
	txt = { -100+(int)w, (int)h, (int)w, (int)h-100 };
	DrawText(hdc, "O", -1, &txt, DT_SINGLELINE | DT_TOP | DT_RIGHT);
	txt = { (int)w, halfheight, (int)w + 100, halfheight - 100 };
	DrawText(hdc, " y", -1, &txt, DT_SINGLELINE | DT_TOP | DT_LEFT);
	txt = { (int)(halfwidth - 100), 100 + (int)h, halfwidth, (int)h };
	DrawText(hdc, "x ", -1, &txt, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);

	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);

	hPen = CreatePen(PS_SOLID, THICKNESS, PLOTCOLOR);
	hOldPen = SelectObject(hdc, hPen);
/*
	MoveToEx(hdc, halfwidth, 0, NULL);
	LineTo(hdc, 0, halfheight);
	MoveToEx(hdc, -halfwidth, 0, NULL);
	LineTo(hdc, 0, -halfheight);
	MoveToEx(hdc, -halfwidth, 0, NULL);
	LineTo(hdc, 0, halfheight);
	MoveToEx(hdc, halfwidth, 0, NULL);
	LineTo(hdc, 0, -halfheight);
*/
	Polyline(hdc, apt, NPOINTS);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}


void drawPt(HDC hdc, int ptx, int pty)
{
	HFONT hFont;
	RECT r{ ptx, pty, ptx + 100, pty - 30 };
	float
		h = Y_DELTA,
		w = X_DELTA,
		x = (ptx - w) / X_SCALE,
		y = (pty - h) / Y_SCALE;
	HPEN hPen;
	HBRUSH hBrush;
	HGDIOBJ hOldPen, hOldBrush, hOldFont;

	char c[32] = "(", buf[256];
	snprintf(buf, 6, "%f", x);
	strcat_s(c, buf);
	strcat_s(c, ", ");
	snprintf(buf, 6, "%f", y);
	strcat_s(c, buf);
	strcat_s(c, ")");

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(250, 250, 250));
	hFont = CreateFont(16, 6, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Comic Sans MS");
	hOldFont = SelectObject(hdc, hFont);
	DrawText(hdc, c, -1, &r, DT_SINGLELINE | DT_TOP | DT_CENTER);
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);

	hBrush = CreateSolidBrush(RGB(255, 100, 205));
	hPen = CreatePen(PS_DOT, 1, RGB(180, 50, 100));
	hOldBrush = SelectObject(hdc, hBrush);
	hOldPen = SelectObject(hdc, hPen);
	Ellipse(hdc, ptx - 5, pty + 5, ptx + 5, pty - 5);
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

void Paint(HWND hWnd, RECT rc, BOOL bShowCoord, int x, int y)
{
	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	hdc = BeginPaint(hWnd, &ps);
	HBITMAP hbmMem;
	HBRUSH hbrBkGnd;
	HGDIOBJ hbmOld;

	int halfwidth = (rc.right - rc.left) / 2,
		halfheight = (rc.bottom - rc.top) / 2;

	SetWindowOrgEx(hdc, -halfwidth, halfheight, NULL);
	SetMapMode(hdc, MM_LOENGLISH);
	SetWindowExtEx(hdc, 100, 100, NULL);

	hdcMem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);
	hbmOld = SelectObject(hdcMem, hbmMem);
	SetWindowOrgEx(hdcMem, -halfwidth, halfheight, NULL);
	SetMapMode(hdcMem, MM_LOENGLISH);
	SetWindowExtEx(hdc, 100, 100, NULL);

	hbrBkGnd = CreateSolidBrush(BKG_CLR);
	RECT r{ -halfwidth, halfheight, halfwidth, -halfheight };
	FillRect(hdcMem, &r, hbrBkGnd);
	DeleteObject(hbrBkGnd);
	SetBkMode(hdcMem, TRANSPARENT);

	displayPlot(rc, hdcMem);
	if (bShowCoord)
		drawPt(hdcMem, x, y);
	BitBlt(hdc,
		-halfwidth, -halfheight,
		halfwidth*2, halfheight*2,
		hdcMem,
		-halfwidth, -halfheight,
		SRCCOPY);

	SelectObject(hdcMem, hbmOld);
	DeleteObject(hbmMem);
	DeleteDC(hdcMem);
	EndPaint(hWnd, &ps);
}

COLORREF SetColor(HWND hWnd, BOOL bC)
{
	static COLORREF acrCustClr[16];
	char c[32];
	CHOOSECOLOR cc{ sizeof(CHOOSECOLOR), hWnd, 0, (bC)? PLOTCOLOR: BKG_CLR, acrCustClr, CC_RGBINIT, 0, 0, 0 };
	ChooseColor(&cc);
	return cc.rgbResult;
}

BOOL CALLBACK ChangeParams(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT rc;
	static HWND hPar, hcb;
	static float
		x_min_old = 0,
		x_max_old = 0,
		zoom_old = 0;
	static int
		func_old = 0,
		wpar = 0,
		pos = 0,
		pos_old = 0,
		thck_old = 0;
	static POINT apt_old[NPOINTS];
	static COLORREF acrCustClr[16], clr_old;
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hPar = GetParent(hdlg);
		GetClientRect(hPar, &rc);
		memcpy(apt_old, apt, NPOINTS * sizeof(POINT));
		pos_old = pos;
		x_min_old = X_MIN;
		x_max_old = X_MAX;
		zoom_old = ZOOM;
		func_old = FUNC;
		clr_old = PLOTCOLOR;
		thck_old = THICKNESS;
		SetDlgItemText(hdlg, IDC_EDIT1, to_string(x_min_old).c_str());
		SetDlgItemText(hdlg, IDC_EDIT2, to_string(x_max_old).c_str());
		SendDlgItemMessage(hdlg, IDC_SLIDER1, TBM_SETPOS, 1, ZOOM * 50);
		switch (FUNC)
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
		case 3:
			SendDlgItemMessage(hdlg, IDC_RADIO4, BM_SETCHECK, 1, 0);
			break;
		}
		hcb = GetDlgItem(hdlg, IDC_COMBO1);
		ComboBox_AddItemData(hcb, "1px (Thin)");
		ComboBox_AddItemData(hcb, "2px (Normal)");
		ComboBox_AddItemData(hcb, "3px (Thick)");
		ComboBox_SetCurSel(hcb, THICKNESS - 1);
		break;
	}
	case WM_HSCROLL:
	{
		wpar = HIWORD(wParam);
		if (wpar != 0)
		{
			pos = wpar;
			ZOOM = (double)pos / 50;
		}
		recalcPts(rc);
		InvalidateRect(hPar, NULL, TRUE);
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			InvalidateRect(hPar, NULL, TRUE);
			EndDialog(hdlg, 0);
			break;
		}
		case IDCANCEL:
		{
			pos = pos_old;
			ZOOM = zoom_old;
			X_MIN = x_min_old;
			X_MAX = x_max_old;
			FUNC = func_old;
			PLOTCOLOR = clr_old;
			THICKNESS = thck_old;
			memcpy(apt, apt_old, NPOINTS * sizeof(POINT));
			recalcPts(rc);
			InvalidateRect(hPar, NULL, TRUE);
			EndDialog(hdlg, 0);
			break;
		}
		case IDC_BUTTON1:
		{
			PLOTCOLOR = SetColor(hdlg, TRUE);
			break;
		}
		case IDC_COMBO1:
		{
			THICKNESS = ComboBox_GetCurSel(hcb) + 1;
			break;
		}
		case IDC_RADIO1:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				SendDlgItemMessage(hdlg, IDC_RADIO1, BM_SETCHECK, 1, 0);
				FUNC = 0;
				recalcPts(rc);
			}
			break;
		case IDC_RADIO2:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				SendDlgItemMessage(hdlg, IDC_RADIO2, BM_SETCHECK, 1, 0);
				FUNC = 1;
				recalcPts(rc);
			}
			break;
		case IDC_RADIO3:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				SendDlgItemMessage(hdlg, IDC_RADIO3, BM_SETCHECK, 1, 0);
				FUNC = 2;
				recalcPts(rc);
			}
			break;
		case IDC_RADIO4:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				SendDlgItemMessage(hdlg, IDC_RADIO4, BM_SETCHECK, 1, 0);
				FUNC = 3;
				recalcPts(rc);
			}
			break;
		case IDC_EDIT1:
		{
			if (HIWORD(wParam) == EN_CHANGE)
			{
				char c[32];
				int x = 0;

				Edit_GetLine((HWND)lParam, 0, c, 32);
				x = atoi(c);
				X_MIN = x;
				recalcPts(rc);
			}
			break;
		}
		case IDC_EDIT2:
		{
			if (HIWORD(wParam) == EN_CHANGE)
			{
				char c[32];
				int x = 0;

				Edit_GetLine((HWND)lParam, 0, c, 32);
				x = atoi(c);
				X_MAX = x;
				recalcPts(rc);
			}
			break;
		}
		}
		InvalidateRect(hPar, NULL, TRUE);
		break;
	}
	return FALSE;
}

BOOL CALLBACK About(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			EndDialog(hdlg, 0);
			break;
		}
		}
	case WM_DESTROY:
		{
			EndDialog(hdlg, 0);
			break;
		}
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HCURSOR
		hCurs1 = LoadCursor(NULL, IDC_CROSS),
		hCurs2 = LoadCursor(NULL, IDC_ARROW);
	static HMENU hMenu1, hMenu2;
	static HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
	static RECT rc;
	static int
		x, y,
		x_stop, y_stop;
	static BOOL
		bShowCoord,
		bStop;

	switch (message)
	{
	case WM_CREATE:
	{
		hMenu1 = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU2));
		hMenu1 = GetSubMenu(hMenu1, 0);
		hMenu2 = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU3));
		hMenu2 = GetSubMenu(hMenu2, 0);
		SetCursor(hCurs2);
		bShowCoord = FALSE;
		break;
	}
	case WM_ERASEBKGND:
		return (LRESULT)1;

	case WM_RBUTTONDOWN:
	{
		POINT pt{LOWORD(lParam), HIWORD(lParam)};
		if (checkPos(hWnd, pt.x - (rc.right / 2 - rc.left), (rc.bottom - rc.top) / 2 - pt.y))
		{
			ClientToScreen(hWnd, &pt);
			TrackPopupMenu(hMenu1, 0, pt.x, pt.y, 0, hWnd, NULL);
		}
		else
		{
			ClientToScreen(hWnd, &pt);
			TrackPopupMenu(hMenu2, 0, pt.x, pt.y, 0, hWnd, NULL);
		}
		break; 
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_OPTIONS_CUSTOMIZE:
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, ChangeParams);
			break;
		case ID_INFO_ABOUT:
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, About);
			break;
		case ID_POPUP_BACKGROUND:
			BKG_CLR = SetColor(hWnd, FALSE);
			break;
		case ID_POPUP_LINECOLOR:
			PLOTCOLOR = SetColor(hWnd, TRUE);
			break;
		case ID_LINETHICKNESS_1PX:
			CheckMenuItem(hMenu1, ID_LINETHICKNESS_1PX, MF_CHECKED);
			CheckMenuItem(hMenu1, ID_LINETHICKNESS_2PX, MF_UNCHECKED);
			CheckMenuItem(hMenu1, ID_LINETHICKNESS_3PX, MF_UNCHECKED);
			THICKNESS = 1;
			break;
		case ID_LINETHICKNESS_2PX:
			CheckMenuItem(hMenu1, ID_LINETHICKNESS_2PX, MF_CHECKED);
			CheckMenuItem(hMenu1, ID_LINETHICKNESS_1PX, MF_UNCHECKED);
			CheckMenuItem(hMenu1, ID_LINETHICKNESS_3PX, MF_UNCHECKED);
			THICKNESS = 2;
			break;
		case ID_LINETHICKNESS_3PX:
			CheckMenuItem(hMenu1, ID_LINETHICKNESS_3PX, MF_CHECKED);
			CheckMenuItem(hMenu1, ID_LINETHICKNESS_2PX, MF_UNCHECKED);
			CheckMenuItem(hMenu1, ID_LINETHICKNESS_1PX, MF_UNCHECKED);
			THICKNESS = 3;
			break;
		case ID_F1:
			FUNC = 0;
			recalcPts(rc);
			break;
		case ID_F2:
			FUNC = 1;
			recalcPts(rc);
			break;
		case ID_F3:
			FUNC = 2;
			recalcPts(rc);
			break;
		case ID_F4:
			FUNC = 3;
			recalcPts(rc);
			break;
		case ID_LEFT:
			X_MIN -= 10;
			recalcPts(rc);
			break;
		case ID_RIGHT:
			X_MAX += 10;
			recalcPts(rc);
			break;
		case ID_S_RIGHT:
			X_MIN += 10;
			recalcPts(rc);
			break;
		case ID_S_LEFT:
			X_MAX -= 10;
			recalcPts(rc);
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}

	case WM_MOUSEMOVE:
		if (bShowCoord)
		{
			x = LOWORD(lParam) - rc.right / 2;
			y = fpt(hWnd, x);
			bStop = checkPos(hWnd, x, y);
			if (!bStop)
			{
				x = x_stop;
				y = y_stop;
			}
			else
			{
				x_stop = x;
				y_stop = y;
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else
			SetCursor(hCurs2);
		break;

	case WM_LBUTTONDOWN:
	{
		x = LOWORD(lParam) - (rc.right / 2 - rc.left);
		y = (rc.bottom - rc.top) / 2 - HIWORD(lParam);
		if (!bShowCoord)
			bShowCoord = checkPos(hWnd, x, y);
		if (bShowCoord)
		{
			SetCursor(hCurs1);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	}

	case WM_LBUTTONUP:
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
		break;
	}

	case WM_PAINT:
		Paint(hWnd, rc, bShowCoord, x, y);
		break;

	case WM_SIZE:
		GetClientRect(hWnd, &rc);
		recalcPts(rc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ADD:
			ZOOM *= 1.1;
			recalcPts(rc);
			break;
		case VK_SUBTRACT:
			if ((int)(10 * ZOOM / 1.1) > 0)
			{
				ZOOM /= 1.1;
				recalcPts(rc);
			}
			else
				MessageBox(hWnd, "Minimal zoom reached!", "Warning", MB_OK);
			break;
		case VK_UP:
			Y_DELTA -= 10;
			recalcPts(rc);
			break;
		case VK_DOWN:
			Y_DELTA += 10;
			recalcPts(rc);
			break;
		case VK_LEFT:
			X_DELTA += 10;
			recalcPts(rc);
			break;
		case VK_RIGHT:
			X_DELTA -= 10;
			recalcPts(rc);
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
