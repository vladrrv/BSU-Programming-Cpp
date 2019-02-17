#include <windows.h>
#include <windowsx.h> 
#include <commctrl.h>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "resource.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "Ratings";
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

struct Competitor
{
	string name;
	float rating;
	COLORREF col;
};
vector<Competitor> vct;
void rd_file()
{
	ifstream infile("input.txt");
	while (!infile.eof())
	{
		string n;
		float r;
		infile >> n >> r;
		vct.push_back(Competitor{ n, r, RGB(20+rand() % 150, 20+rand() % 150, 20+rand() % 150) });
	}
	infile.close();
}

void PaintPie(HWND hWnd)
{
	RECT rc, txt;
	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	HFONT hFont = CreateFont(25, 8, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Arial");
	HBITMAP hbmMem;
	HBRUSH hbrBkGnd;
	HGDIOBJ hbmOld;
	hdc = BeginPaint(hWnd, &ps);
	GetClientRect(hWnd, &rc);
	int
		x = rc.right / 2,
		y = rc.bottom / 2,
		r = (x + y) / 4;
	hdcMem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);
	hbmOld = SelectObject(hdcMem, hbmMem);

	hbrBkGnd = CreateSolidBrush(BKG_CLR);
	FillRect(hdcMem, &rc, hbrBkGnd);
	DeleteObject(hbrBkGnd);
	SetBkMode(hdcMem, TRANSPARENT);

	SelectObject(hdcMem, GetStockObject(DC_BRUSH));
	SelectObject(hdcMem, GetStockObject(DC_PEN));
	SetTextColor(hdcMem, RGB(200, 200, 200));
	SetDCBrushColor(hdcMem, RGB(40, 200, 40));
	SetDCPenColor(hdcMem, RGB(0, 100, 0));
	int
		x0 = x + r, y0 = y,
		x1 = x0, y1 = y0,
		x2, y2, dx = 0, dy = 0;
	float acc = 0, a;
	for (Competitor o : vct)
	{
		SetDCBrushColor(hdcMem, o.col);
		float m = (acc + o.rating / 2);
		float mid = 3.14*m / 50;
		acc += o.rating;
		a = 3.14*acc / 50;

		x1 = x + r*cos(a);
		y1 = y - r*sin(a);
		x2 = x + r*cos(mid);
		y2 = y - r*sin(mid);
		Pie(hdcMem, x - r, y - r, x + r, y + r, x0, y0, x1, y1);
		txt = { x2 - 100 + dx, y2 - 100 + dy, x2 + 100 + dx, y2 + 100 + dy };
		int esc = (int)(180 * mid / 3.14 * 10);
		if (esc > 900 && esc < 2700)
			esc %= 1800;
		hFont = CreateFont(25, 8, esc, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Arial");
		SelectObject(hdcMem, hFont);
		DrawText(hdcMem, (o.name + " " + to_string((int)o.rating) + "%").c_str(), -1, &txt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		DeleteObject(hFont);
		x0 = x1;
		y0 = y1;
	}

	BitBlt(hdc,
		rc.left, rc.top,
		rc.right - rc.left, rc.bottom - rc.top,
		hdcMem,
		0, 0,
		SRCCOPY);

	SelectObject(hdcMem, hbmOld);
	DeleteObject(hFont);
	DeleteObject(hbmMem);
	DeleteDC(hdcMem);
	EndPaint(hWnd, &ps);
}

void PaintCol(HWND hWnd)
{
	RECT rc, txt;
	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	HFONT hFont = CreateFont(30, 10, 900, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Arial");
	HBITMAP hbmMem;
	HBRUSH hbrBkGnd;
	HGDIOBJ hbmOld;
	hdc = BeginPaint(hWnd, &ps);
	GetClientRect(hWnd, &rc);
	int
		x = rc.right / 2,
		y = rc.bottom / 2,
		r = 400;
	hdcMem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);
	hbmOld = SelectObject(hdcMem, hbmMem);

	hbrBkGnd = CreateSolidBrush(BKG_CLR);
	FillRect(hdcMem, &rc, hbrBkGnd);
	DeleteObject(hbrBkGnd);
	SetBkMode(hdcMem, TRANSPARENT);

	SelectObject(hdcMem, GetStockObject(DC_BRUSH));
	SelectObject(hdcMem, GetStockObject(DC_PEN));
	SetTextColor(hdcMem, RGB(200, 200, 200));
	int
		x_start = 0,
		col_height = 0,
		d = rc.right / vct.size();

	SelectObject(hdcMem, hFont);

	for (Competitor o : vct)
	{
		SetDCBrushColor(hdcMem, o.col);
		col_height = (1.0-o.rating / 100) * rc.bottom;
		Rectangle(hdcMem, x_start, col_height, x_start + d, rc.bottom);
		txt = { x_start + d / 4, col_height - 200, x_start + d / 2, col_height };
		DrawText(hdcMem, (o.name + " " + to_string((int)o.rating) + "%").c_str(), -1, &txt, DT_SINGLELINE | DT_BOTTOM);
		x_start += d;
	}
	DeleteObject(hFont);

	BitBlt(hdc,
		rc.left, rc.top,
		rc.right - rc.left, rc.bottom - rc.top,
		hdcMem,
		0, 0,
		SRCCOPY);

	SelectObject(hdcMem, hbmOld);
	DeleteObject(hFont);
	DeleteObject(hbmMem);
	DeleteDC(hdcMem);
	EndPaint(hWnd, &ps);
}

BOOL CALLBACK ChangeParams(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static vector<Competitor> vct_old;
	static COLORREF acrCustClr[16];
	static BOOL bChanged;
	switch (message)
	{
	case WM_INITDIALOG:
	{
		bChanged = FALSE;
		for (Competitor o : vct)
			ComboBox_AddItemData(GetDlgItem(hdlg, IDC_COMBO1), o.name.c_str());
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hdlg, 0);
			break;
		case IDCANCEL:
			if (bChanged)
				vct = vct_old;
			InvalidateRect(GetParent(hdlg), NULL, TRUE);
			EndDialog(hdlg, 0);
			break;
		case IDC_BUTTON1:
			char c[32];
			ComboBox_GetText(GetDlgItem(hdlg, IDC_COMBO1), c, 32);
			vector<Competitor>::iterator
				it = find_if(vct.begin(), vct.end(), [&](Competitor& o)
			{
				return o.name == string(c);
			});
			if (it != vct.end())
			{
				if (!bChanged)
				{
					bChanged = TRUE;
					vct_old = vct;
				}
				CHOOSECOLOR cc{ sizeof(CHOOSECOLOR), hdlg, 0, it->col, acrCustClr, CC_RGBINIT | CC_FULLOPEN | CC_SOLIDCOLOR, 0, 0, 0 };
				ChooseColor(&cc);
				it->col = cc.rgbResult;
				InvalidateRect(GetParent(hdlg), NULL, TRUE);
			}

			break;
		}

		break;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT rc, r;
	static BOOL bDiag = TRUE;
	switch (message)
	{
	case WM_CREATE:
	{
		srand(time(0));
		rd_file();
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
	case WM_PAINT:
		if (bDiag)
			PaintPie(hWnd);
		else
			PaintCol(hWnd);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			bDiag = !bDiag;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_RIGHT:
			bDiag = !bDiag;
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
