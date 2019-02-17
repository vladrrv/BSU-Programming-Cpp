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
LPCSTR szTitle = "Rabbits";
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
		200 * (log(N) + 0.5),
		200 * (log(M) + 0.5) + GetSystemMetrics(SM_CYMENU),
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

vector<pair<int, int>> rabbits;//rabbits coords
bool started = false;

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

BOOL CALLBACK Add(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int
		m_old, n_old, t_old,
		i, j, t;
	static HWND hParent = GetParent(hdlg);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		started = false;
		//SetDlgItemText(hdlg, IDC_EDIT1, to_string(m_old).c_str());
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			rabbits.push_back(pair<int, int>(i, j));
			field[i*N + j].setState(RAB);
			LEN++;
			InvalidateRect(hParent, NULL, TRUE);
			started = true;
			EndDialog(hdlg, 0);
			break;
		}
		case IDCANCEL:
		{
			started = true;
			EndDialog(hdlg, 0);
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

		}
		break;
	}
	return FALSE;
}

void rab_move(int& ind)
{
	int i = rabbits[ind].first, j = rabbits[ind].second;
	if (i > 0 && field[N*(i - 1) + j].getState() == RES)
	{
		field[N*(i - 1) + j].setState(RAB);
		field[N*i + j].setState(EMPTY);
		rabbits[ind] = pair<int, int>(i - 1, j);
	}
	else if (j < N - 1 && field[N*i + j + 1].getState() == RES)
	{
		field[N*i + j + 1].setState(RAB);
		field[N*i + j].setState(EMPTY);
		rabbits[ind] = pair<int, int>(i, j+1);
	}
	else if (i < M - 1 && field[N*(i + 1) + j].getState() == RES)
	{
		field[N*(i + 1) + j].setState(RAB);
		field[N*i + j].setState(EMPTY);
		rabbits[ind] = pair<int, int>(i + 1, j);
	}
	else if (j > 0 && field[N*i + j - 1].getState() == RES)
	{
		field[N*i + j - 1].setState(RAB);
		field[N*i + j].setState(EMPTY);
		rabbits[ind] = pair<int, int>(i, j-1);
	}
	else
	{
		field[N*i + j].setState(EMPTY);
		rabbits.erase(rabbits.begin() + ind);
		ind--;
		LEN--;
	}
}
void new_simul()
{
	field.clear();
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			field.push_back(Cell(i, j));
	LEN = 4;
	int i0 = M / LEN, j0 = N / LEN, d = sqrt(LEN);
	for (int i = 0; i < LEN; i++)
	{
		rabbits.push_back(pair<int, int>(i0, j0));
		field[i0*N + j0].setState(RAB);
		i0 += d;
		j0 += d;
	}
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HMENU hMenu;
	static HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
	static RECT rc;
	static int x, y, direction = rand() % 4, int_count = 0, mov_count = 0;
	switch (message)
	{
	case WM_CREATE:
	{
		new_simul();
	}
	case WM_KEYDOWN:
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_SIMULATION_STARTNEW:
			new_simul();
			started = true;
			SetTimer(hWnd, 1, 1000, 0);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_SIMULATION_ADDRABBIT:
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_ADD), hWnd, Add);
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
		if (!started)
		{
			started = true;
			SetTimer(hWnd, 1, 1000, 0);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_TIMER:
	{
		if (started)
		{
			mov_count++;
			for (int i = 0; i < LEN; i++)
			{
				rab_move(i);
			}
			if (rabbits.empty())
			{
				KillTimer(hWnd, 1);
				started = false;
				InvalidateRect(hWnd, NULL, TRUE);
				MessageBox(hWnd, "All rabbits are dead. Simulation is over!", "Simulation Over", MB_OK);
			}
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
