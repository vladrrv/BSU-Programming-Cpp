#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <windows.h>
#include <windowsx.h> 
#include <commctrl.h>
#include <string>
#include <ctime>
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
LPCSTR szTitle = "Worm";
COLORREF BKG_CLR = RGB(50, 50, 50);

HWND hwndMain;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(0));
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
		150 * (log(N) + 0.5),
		150 * (log(M) + 0.5) + GetSystemMetrics(SM_CYMENU),
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hwndMain) return FALSE;
	ShowWindow(hwndMain, SW_NORMAL);
	UpdateWindow(hwndMain);
	return TRUE;
}


COLORREF SetColor(HWND hWnd)
{
	static COLORREF acrCustClr[16];
	char c[32];
	CHOOSECOLOR cc{ sizeof(CHOOSECOLOR), hWnd, 0, PT_COLOR, acrCustClr, CC_RGBINIT | CC_FULLOPEN, 0, 0, 0 };
	ChooseColor(&cc);
	return cc.rgbResult;
}

vector<Cell> field;

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

	for (Cell& c : field)
		c.draw(rc, hdcMem);
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


BOOL CALLBACK Settings(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int
		i_old, j_old, st_old,
		i, j, st;
	static COLORREF cl;
	static HWND hParent = GetParent(hdlg);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		i = I_START;
		j = J_START;
		st = STEP;
		cl = PT_COLOR;
		SetDlgItemText(hdlg, IDC_EDIT1, to_string(I_START).c_str());
		SetDlgItemText(hdlg, IDC_EDIT2, to_string(J_START).c_str());
		if (STEP == 1)
			Button_SetCheck(GetDlgItem(hdlg, IDC_RADIO1), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hdlg, IDC_RADIO2), BST_CHECKED);

		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			I_START = i;
			J_START = j;
			STEP = st;
			PT_COLOR = cl;
			InvalidateRect(hParent, NULL, TRUE);
			EndDialog(hdlg, 0);
			break;
		}
		case IDCANCEL:
		{
			EndDialog(hdlg, 0);
			break;
		}
		case IDC_SETCOLOR:
		{
			cl = SetColor(hdlg);
			break;
		}
		case IDC_EDIT1:
		{
			if (HIWORD(wParam) == EN_CHANGE)
			{
				char c[32];
				Edit_GetLine((HWND)lParam, 0, c, 32);
				i = atoi(c);
			}
			break;
		}
		case IDC_EDIT2:
		{
			if (HIWORD(wParam) == EN_CHANGE)
			{
				char c[32];
				Edit_GetLine((HWND)lParam, 0, c, 32);
				j = atoi(c);
			}
			break;
		}
		case IDC_RADIO1:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				Button_SetCheck(GetDlgItem(hdlg, IDC_RADIO1), BST_CHECKED);
				st = 1;
			}
			break;
		case IDC_RADIO2:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				Button_SetCheck(GetDlgItem(hdlg, IDC_RADIO2), BST_CHECKED);
				st = 2;
			}
			break;
		}
		break;
	}
	return FALSE;
}

pair<int, int> particle;//worm coords

bool toBorder()
{
	return
		particle.second == 0 ||
		particle.first == 0 ||
		particle.second == N - 1 ||
		particle.first == M - 1;
}
void newGame()
{
	field.clear();
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			field.push_back(Cell(i, j));
	particle.first = I_START;
	particle.second = J_START;
	field[I_START*N + J_START].setState(WORM);

}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HMENU hMenu;
	static HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
	static RECT rc;
	static bool moving = false;
	static int x, y, direction = rand() % 4, int_count = 0, mov_count = 0;
	switch (message)
	{
	case WM_CREATE:
	{
		newGame();
		break;
	}
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			if (direction != 2)
				direction = 0;
			break;
		case VK_UP:
			if (direction != 3)
				direction = 1;
			break;
		case VK_RIGHT:
			if (direction != 0)
				direction = 2;
			break;
		case VK_DOWN:
			if (direction != 1)
				direction = 3;
			break;
		}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_GAME_START:
			moving = false;
			newGame();
			mov_count = 0;
			int_count = 0;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_GAME_SETTINGS:
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_SETTINGS), hWnd, Settings);
			InvalidateRect(hWnd, NULL, TRUE);
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
		if (!moving)
		{
			moving = true;
			SetTimer(hWnd, 1, 10, 0);
			EnableMenuItem(GetMenu(hWnd), ID_GAME_SETTINGS, MF_DISABLED);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_TIMER:
	{
		if (mov_count % STEP == 0)
			direction = rand() % 4;
		if (!toBorder() && mov_count < 300)
		{
			mov_count++;
			int tr_ind = particle.first * N + particle.second;
			field[tr_ind].setState(TRACE);
			switch (direction)
			{
			case 0: // left
				particle.second--;
				break;
			case 1: // up
				particle.first--;
				break;
			case 2: // right
				particle.second++;
				break;
			case 3: // down
				particle.first++;
				break;
			}
			Cell *headptr = &field[particle.first * N + particle.second];
			if (headptr->getState() == EMPTY)
				headptr->setState(WORM);
			else if (headptr->getState() == TRACE)
			{
				int_count++;
				headptr->get_i_c()++;
				headptr->setState(WORM);
			}
		}
		else
		{
			KillTimer(hWnd, 1);
			EnableMenuItem(GetMenu(hWnd), ID_GAME_SETTINGS, MF_ENABLED);
			if (STEP == 2 && moving)
				mov_count /= 2;
			moving = false;
			string stat = "Moves count: " + to_string(mov_count) + "\nIntersections count: " + to_string(int_count);
			MessageBox(hWnd, stat.c_str(), "Statistics", MB_OK);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_ERASEBKGND:
		return (LRESULT)1;

	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 150 * (log(N) + 0.5);
		lpMMI->ptMinTrackSize.y = 150 * (log(M) + 0.5) + GetSystemMetrics(SM_CYMENU);
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
