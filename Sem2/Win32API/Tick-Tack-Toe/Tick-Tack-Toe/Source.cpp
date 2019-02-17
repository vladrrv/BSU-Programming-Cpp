#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <windows.h>
#include <windowsx.h> 
#include <commctrl.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include "resource.h"
#include "Cell.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "Tick-Tack-Toe";
COLORREF BKG_CLR = RGB(50, 50, 50);

HWND hwndMain;

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
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAINMENU);
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
		200 * (log(N)+0.5),
		200 * (log(M)+0.5) + GetSystemMetrics(SM_CYMENU),
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hwndMain) return FALSE;
	ShowWindow(hwndMain, SW_NORMAL);
	UpdateWindow(hwndMain);
	return TRUE;
}


vector<Cell> field;

Cell *seq_begin = NULL, *seq_end = NULL;

void Paint(HWND hWnd, RECT rc)
{
	HDC hdc, hdcMem;
	HPEN hPen;
	HGDIOBJ hOldPen;
	PAINTSTRUCT ps;
	HBITMAP hbmMem;
	HBRUSH hbrBkGnd;
	HGDIOBJ hbmOld;
	hdc = BeginPaint(hWnd, &ps);

	hdcMem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);
	hbmOld = SelectObject(hdcMem, hbmMem);

	hbrBkGnd = CreateSolidBrush(BKG_CLR);
	FillRect(hdcMem, &rc, hbrBkGnd);
	DeleteObject(hbrBkGnd);
	SetBkMode(hdcMem, TRANSPARENT);

	float
		w = (float)(rc.right - rc.left) / N,
		h = (float)(rc.bottom - rc.top) / M;
	SelectObject(hdcMem, GetStockObject(DC_PEN));
	SetDCPenColor(hdcMem, RGB(100, 100, 100));
	for (int i = 1; i < M; i++)
	{
		int	y = i*h;
		MoveToEx(hdcMem, rc.left, y, 0);
		LineTo(hdcMem, rc.right, y);
	}
	for (int j = 1; j < N; j++)
	{
		int	x = j*w;
		MoveToEx(hdcMem, x, rc.top, 0);
		LineTo(hdcMem, x, rc.bottom);
	}
	for (Cell c : field)
		c.draw(rc, hdcMem);

	if (seq_begin != NULL && seq_end != NULL)
	{
		int
			x1 = seq_begin->getCenter(rc).x,
			y1 = seq_begin->getCenter(rc).y,
			x2 = seq_end->getCenter(rc).x,
			y2 = seq_end->getCenter(rc).y;
		hPen = CreatePen(PS_SOLID, 4, RGB(100, 100, 200));
		hOldPen = SelectObject(hdcMem, hPen);
		MoveToEx(hdcMem, x1, y1, 0);
		LineTo(hdcMem, x2, y2);
		SelectObject(hdcMem, hOldPen);
		DeleteObject(hPen);
	}

	BitBlt(hdc,
		rc.left, rc.top,
		rc.right, rc.bottom,
		hdcMem,
		rc.left, rc.top,
		SRCCOPY);

	SelectObject(hdcMem, hbmOld);
	DeleteObject(hbmMem);
	DeleteDC(hdcMem);
	EndPaint(hWnd, &ps);
}


BOOL CALLBACK About(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		EndDialog(hdlg, 0);
		break;
	}
	return FALSE;
}

BOOL CALLBACK Settings(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int
		m_old, n_old, t_old,
		m, n, t;
	static HWND hParent = GetParent(hdlg);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		m_old = M;
		n_old = N;
		t_old = TOWIN;
		SetDlgItemText(hdlg, IDC_EDIT1, to_string(m_old).c_str());
		SetDlgItemText(hdlg, IDC_EDIT2, to_string(n_old).c_str());
		SetDlgItemText(hdlg, IDC_EDIT3, to_string(t_old).c_str());
		if (PVP)
		{
			Button_SetCheck(GetDlgItem(hdlg, IDC_RADIO3), BST_CHECKED);
			Button_Enable(GetDlgItem(hdlg, IDC_RADIO1), FALSE);
			Button_Enable(GetDlgItem(hdlg, IDC_RADIO2), FALSE);
		}
		else
			Button_SetCheck(GetDlgItem(hdlg, IDC_RADIO4), BST_CHECKED);
		if (PLAY_AS == _O_)
			Button_SetCheck(GetDlgItem(hdlg, IDC_RADIO1), BST_CHECKED);
		else if (PLAY_AS == _X_)
			Button_SetCheck(GetDlgItem(hdlg, IDC_RADIO2), BST_CHECKED);
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			M = m;
			N = n;
			TOWIN = t;
			InvalidateRect(hParent, NULL, TRUE);
			EndDialog(hdlg, 0);
			break;
		}
		case IDCANCEL:
		{
			EndDialog(hdlg, 0);
			break;
		}
		case IDC_EDIT1:
		{
			if (HIWORD(wParam) == EN_CHANGE)
			{
				char c[32];
				Edit_GetLine((HWND)lParam, 0, c, 32);
				m = atoi(c);
			}
			break;
		}
		case IDC_EDIT2:
		{
			if (HIWORD(wParam) == EN_CHANGE)
			{
				char c[32];
				Edit_GetLine((HWND)lParam, 0, c, 32);
				n = atoi(c);
			}
			break;
		}
		case IDC_EDIT3:
		{
			if (HIWORD(wParam) == EN_CHANGE)
			{
				char c[32];
				Edit_GetLine((HWND)lParam, 0, c, 32);
				t = atoi(c);
			}
			break;
		}
		case IDC_RADIO1:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				Button_SetCheck(GetDlgItem(hdlg, IDC_RADIO1), BST_CHECKED);

			}
			break;
		case IDC_RADIO2:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				Button_SetCheck(GetDlgItem(hdlg, IDC_RADIO2), BST_CHECKED);

			}
			break;
		case IDC_RADIO3:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				Button_SetCheck(GetDlgItem(hdlg, IDC_RADIO3), BST_CHECKED);
				Button_Enable(GetDlgItem(hdlg, IDC_RADIO1), FALSE);
				Button_Enable(GetDlgItem(hdlg, IDC_RADIO2), FALSE);
			}
			break;
		case IDC_RADIO4:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				Button_SetCheck(GetDlgItem(hdlg, IDC_RADIO4), BST_CHECKED);
				Button_Enable(GetDlgItem(hdlg, IDC_RADIO1), TRUE);
				Button_Enable(GetDlgItem(hdlg, IDC_RADIO2), TRUE);

			}
			break;
		}
		break;
	}
	return FALSE;
}

bool checkWin(int i, int j, int player)
{
	int
		top = i - TOWIN + 1,
		bottom = i + TOWIN - 1,
		left = j - TOWIN + 1,
		right = j + TOWIN - 1;
	int seq = 1;
	for (int k = left; k < right; k++)
	{
		int ind1 = i*N + k, ind2 = i*N + k + 1;
		if ((k >= 0 && k+1 < N) && field[ind1].getState() == player && field[ind1].getState() == field[ind2].getState())
		{
			if (seq == 1)
				seq_begin = &field[ind1];
			seq_end = &field[ind2];
			seq++;
		}
		else
			seq = 1;
		if (seq == TOWIN)
			return true;
	}
	for (int l = top; l < bottom; l++)
	{
		int ind1 = l*N + j, ind2 = (l + 1)*N + j;
		if ((l >= 0 && l+1 < M) && field[ind1].getState() == player && field[ind1].getState() == field[ind2].getState())
		{
			if (seq == 1)
				seq_begin = &field[ind1];
			seq_end = &field[ind2];
			seq++;
		}
		else
			seq = 1;
		if (seq == TOWIN)
			return true;
	}
	for (int k = left, l = top; k < right && l < bottom; k++, l++)
	{
		int ind1 = l*N + k, ind2 = (l + 1)*N + k + 1;
		if ((k >= 0 && k+1 < N) && (l >= 0 && l+1 < M) && field[ind1].getState() == player && field[ind1].getState() == field[ind2].getState())
		{
			if (seq == 1)
				seq_begin = &field[ind1];
			seq_end = &field[ind2];
			seq++;
		}
		else
			seq = 1;
		if (seq == TOWIN)
			return true;
	}
	for (int k = right, l = top; k > left && l < bottom; k--, l++)
	{
		int ind1 = l*N + k, ind2 = (l + 1)*N + k - 1;
		if ((k > 0 && k < N) && (l >= 0 && l+1 < M) && field[ind1].getState() == player && field[ind1].getState() == field[ind2].getState())
		{
			if (seq == 1)
				seq_begin = &field[ind1];
			seq_end = &field[ind2];
			seq++;
		}
		else
			seq = 1;
		if (seq == TOWIN)
			return true;
	}
	seq_begin = NULL;
	seq_end = NULL;
	return false;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HMENU hMenu;
	static HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
	static RECT rc, rw;
	static BOOL	bRun = FALSE;
	static bool player1 = true;
	static int x, y;
	switch (message)
	{
	case WM_CREATE:
	{
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				field.push_back(Cell(i, j));
		break;
	}

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_GAME_NEW:
			field.clear(); 
			seq_begin = NULL;
			seq_end = NULL;
			bRun = TRUE;
			player1 = true;
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					field.push_back(Cell(i, j));
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_INFO_ABOUT:
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUT), hWnd, About);
			break;
		case ID_GAME_SETTINGS:
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_SETTINGS), hWnd, Settings);
			break;

		default:
			break;
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		if (player1 && bRun)
		{
			for (Cell& c : field)
				if (c.hit(rc, x, y, _O_))
				{
					InvalidateRect(hWnd, NULL, TRUE);
					player1 = false;
					if (checkWin(c.get_i(), c.get_j(), _O_))
					{
						InvalidateRect(hWnd, NULL, TRUE);
						MessageBox(hWnd, "Player 1 wins!", "Game Over", MB_OK);
						bRun = FALSE;
					}
					break;
				}
		}
		else if (bRun)
		{
			for (Cell& c : field)
				if (c.hit(rc, x, y, _X_))
				{
					InvalidateRect(hWnd, NULL, TRUE);
					player1 = true;
					if (checkWin(c.get_i(), c.get_j(), _X_))
					{
						InvalidateRect(hWnd, NULL, TRUE);
						MessageBox(hWnd, "Player 2 wins!", "Game Over", MB_OK);
						bRun = FALSE;
					}
					break;
				}
		}
		break;
	}/*
	case WM_LBUTTONUP:
	{
		GetWindowRect(hWnd, &rw);
		SetWindowPos(hWnd, 0, 0, 0,
			min(rw.bottom - GetSystemMetrics(SM_CYMENU), rw.right),
			min(rw.bottom, rw.right + GetSystemMetrics(SM_CYMENU)),
			SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW);
		break;
	}*/
	case WM_RBUTTONDOWN:
	{
		if (!player1 && bRun)
		{
			x = LOWORD(lParam);
			y = HIWORD(lParam);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_ERASEBKGND:
		return (LRESULT)1;

	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 200 * (log(N) + 0.5);
		lpMMI->ptMinTrackSize.y = 200 * (log(M) + 0.5) + GetSystemMetrics(SM_CYMENU);
		break;
	}
	case WM_PAINT:
		GetClientRect(hWnd, &rc);
		Paint(hWnd, rc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
