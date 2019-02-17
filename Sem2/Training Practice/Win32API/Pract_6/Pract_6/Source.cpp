#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <windows.h>
#include <windowsx.h> 
#include <commctrl.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <map>
#include <set>
#include "resource.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "Questionnaire";
COLORREF BKG_CLR = RGB(50, 50, 50);

HWND hwndMain;
map<int, int> rb_map, cb_map;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	cb_map.emplace(0, IDC_CHECK1);
	cb_map.emplace(1, IDC_CHECK2);
	cb_map.emplace(2, IDC_CHECK3);
	cb_map.emplace(3, IDC_CHECK4);
	cb_map.emplace(4, IDC_CHECK5);

	rb_map.emplace(0, IDC_RADIO1);
	rb_map.emplace(1, IDC_RADIO2);
	rb_map.emplace(2, IDC_RADIO3);
	rb_map.emplace(3, IDC_RADIO4);
	rb_map.emplace(4, IDC_RADIO5);

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
		WS_EX_STATICEDGE | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		500,
		500,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hwndMain) return FALSE;
	ShowWindow(hwndMain, SW_NORMAL);
	UpdateWindow(hwndMain);
	return TRUE;
}

struct Question
{
	string text;
	vector<string> answers;
	set<int> correct_answers;
};

vector<Question> vct;
map< int, set<int> > QA;

void rd_file()
{
	ifstream infile("questions.txt");
	while (!infile.eof())
	{
		string question_text;
		int t = -1;
		vector<string> temp_ans;
		set<int> temp_cor_ans;
		getline(infile, question_text);
		infile >> t;
		for (int i = 0; i < t; i++)
		{
			string ans;
			infile >> ans;
			temp_ans.push_back(ans);
		}
		infile >> t;
		for (int i = 0; i < t; i++)
		{
			int ans;
			infile >> ans;
			temp_cor_ans.insert(ans);
		}
		infile.ignore(256, '\n');
		infile.ignore(256, '\n');
		vct.push_back(Question{ question_text, temp_ans, temp_cor_ans });
	}
	infile.close();
}

void Paint(HWND hWnd, RECT rc, BOOL bDone)
{
	HDC hdc, hdcMem;
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

	if (bDone)
	{
		float correct = 0;
		for (pair< int, set<int> > p : QA)
		{
			set<int> s;
			set_intersection(vct[p.first].correct_answers.begin(), vct[p.first].correct_answers.end(),
				p.second.begin(), p.second.end(),
				inserter(s, s.begin()));
			correct += (float)s.size() / vct[p.first].correct_answers.size();
		}
		string result = "You have " + to_string((int)correct) + " of " + to_string(vct.size()) + " questions answered correctly.\n" +
			"Your rating: " + to_string((int)(correct / vct.size() * 100)) + "%";
		HFONT hFont = CreateFont(30, 10, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Arial");
		SelectObject(hdcMem, hFont);
		SetTextColor(hdcMem, RGB(200, 200, 200));
		DrawText(hdcMem, result.c_str(), -1, &rc, DT_CENTER);
		DeleteObject(hFont);
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

void show_question(HWND hdlg, int cur_q)
{
	Static_SetText(GetDlgItem(hdlg, IDC_TEXT), vct[cur_q].text.c_str());
	for (int i = 0; i < 5; i++)
	{
		Button_SetCheck(GetDlgItem(hdlg, rb_map[i]), FALSE);
		Button_SetCheck(GetDlgItem(hdlg, cb_map[i]), FALSE);
		ShowWindow(GetDlgItem(hdlg, rb_map[i]), SW_HIDE);
		ShowWindow(GetDlgItem(hdlg, cb_map[i]), SW_HIDE);
	}
	int size = vct[cur_q].answers.size(), size_c = vct[cur_q].correct_answers.size();
	map<int, int> button_map;
	if (size_c == 1)
		button_map = rb_map;
	else
		button_map = cb_map;

	for (int i = 0; i < size; i++)
	{
		HWND hb = GetDlgItem(hdlg, button_map[i]);
		Button_SetText(hb, vct[cur_q].answers[i].c_str());
		ShowWindow(hb, SW_SHOWNOACTIVATE);
	}
	for (int q : QA[cur_q])
		Button_SetCheck(GetDlgItem(hdlg, button_map[q]), TRUE);
}

void get_answer(HWND hdlg, int cur_q)
{
	QA[cur_q].clear();
	for (int i = 0; i < 5; i++)
		if (Button_GetCheck(GetDlgItem(hdlg, cb_map[i])) == BST_CHECKED ||
			Button_GetCheck(GetDlgItem(hdlg, rb_map[i])) == BST_CHECKED)
			QA[cur_q].insert(i);
	if (QA[cur_q].empty())
		QA.erase(cur_q);
}

BOOL CALLBACK QDialog(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int cur_q = 0, pos = 0;
	switch (message)
	{
	case WM_INITDIALOG:
	{
		cur_q = 0;
		show_question(hdlg, cur_q);
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDFINISH:
		{
			get_answer(hdlg, cur_q);
			int a = 0;
			if (QA.size() < vct.size())
				a = MessageBox(hdlg, "Not all questions are answered. Are you sure to finish?", "Unanswered Questions Remain", MB_YESNOCANCEL | MB_ICONEXCLAMATION);
			
			if (a == IDYES || a == 0)
				EndDialog(hdlg, 0);
			break;
		}
		case IDEXIT:
		{
			int a = 0;
			if (QA.size() < vct.size())
				a = MessageBox(hdlg, "Are you sure to exit?", "Confirm Exit", MB_YESNOCANCEL | MB_ICONEXCLAMATION);
			if (a == IDYES || a == 0)
			{
				EndDialog(hdlg, 0);
				PostMessage(GetParent(hdlg), WM_CLOSE, 0, 0);
			}
			break;
		}
		case IDPREV:
		{
			get_answer(hdlg, cur_q--);
			show_question(hdlg, cur_q);
			break;
		}
		case IDNEXT:
		{
			get_answer(hdlg, cur_q++);
			show_question(hdlg, cur_q);
			break;
		}
		}
		if (cur_q > 0)
			Button_Enable(GetDlgItem(hdlg, IDPREV), TRUE);
		else
			Button_Enable(GetDlgItem(hdlg, IDPREV), FALSE);

		if (cur_q < vct.size()-1)
			Button_Enable(GetDlgItem(hdlg, IDNEXT), TRUE);
		else
			Button_Enable(GetDlgItem(hdlg, IDNEXT), FALSE);
		pos = (double)(QA.size()) / vct.size() * 100;
		SendDlgItemMessage(hdlg, IDC_PROGRESS1, PBM_SETPOS, pos, 0);
		break;
	case WM_CLOSE:
	{
		EndDialog(hdlg, 0);
		break;
	}
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HMENU hMenu;
	static HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
	static RECT rc;
	static BOOL	bDone = FALSE;

	switch (message)
	{
	case WM_CREATE:
	{
		rd_file();
		break;
	}

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_TEST_START:
			bDone = FALSE;
			InvalidateRect(hWnd, NULL, TRUE);
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, QDialog);
			bDone = TRUE;
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	case WM_ERASEBKGND:
		return (LRESULT)1;
		
	case WM_PAINT:
		GetClientRect(hWnd, &rc);
		Paint(hWnd, rc, bDone);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
