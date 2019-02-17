#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include "List.h"
#include "resource.h"
#include <windows.h>
#include <windowsx.h>
#include <string>
#include <sstream>
using namespace std;


template<class T> class ListDemo;

template<class T>
class ListController
{
	HWND hdlg;
	List<T>* model;
	ListDemo<T>* view;
public:
	ListController(List<T>* m1, ListDemo<T>* v, HWND h)
	{
		hdlg = h;
		model = m1;
		view = v;
	}
	void cmd(UINT id)
	{
		switch (id)
		{
		case IDC_PUSH:
		{
			char c[32];
			Edit_GetLine(GetDlgItem(hdlg, IDC_IN), 0, c, 32);
			stringstream str(c);
			str >> (*model);
			view->refresh(hdlg);
			break;
		}
		case IDC_POPB:
		{
			try
			{
				view->refresh(hdlg, "Popped: " + to_string(model->pop_back()));
			}
			catch (string exc)
			{
				view->refresh(hdlg, exc);
			}
			break;
		}
		case IDC_POPF:
		{
			try
			{
				view->refresh(hdlg, "Popped: " + to_string(model->pop_front()));
			}
			catch (string exc)
			{
				view->refresh(hdlg, exc);
			}
			break;
		}

		}
	}
};

template<class T>
class ListDemo
{
	List<T>* model;
	ListController<T>* controller;
public:
	ListDemo(HWND h)
	{
		model = new List<T>();
		controller = new ListController<T>(model, this, h);
	}
	~ListDemo()
	{
		delete model;
		delete controller;
	}
	void refresh(HWND hdlg, string text_out = "")
	{
		Edit_SetText(GetDlgItem(hdlg, IDC_DISPLAY), "");
		Edit_SetText(GetDlgItem(hdlg, IDC_OUT), "");
		Edit_SetText(GetDlgItem(hdlg, IDC_MIN), "");
		Edit_SetText(GetDlgItem(hdlg, IDC_MAX), "");
		GetString<T> visitor_str;
		GetMin<T> visitor_min;
		GetMax<T> visitor_max;
		if (model->size() > 0)
		{
			model->accept(visitor_str);
			model->accept(visitor_min);
			model->accept(visitor_max);
			Edit_SetText(GetDlgItem(hdlg, IDC_DISPLAY), visitor_str.value().c_str());
			Edit_SetText(GetDlgItem(hdlg, IDC_MIN), to_string(visitor_min.value()).c_str());
			Edit_SetText(GetDlgItem(hdlg, IDC_MAX), to_string(visitor_max.value()).c_str());
		}
		if (!(text_out.empty()))
			Edit_SetText(GetDlgItem(hdlg, IDC_OUT), text_out.c_str());
	}
	ListController<T>* getController() const
	{
		return controller;
	}
};


/*-----------Edit Control Subclassing-----------*/
WNDPROC oldEditProc;
LRESULT CALLBACK subEditProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
		{
			SendMessage(GetParent(hwnd), WM_COMMAND, (WPARAM)IDC_PUSH, MAKELPARAM(0, 0));
			break;
		}
		}
	default:
		return CallWindowProc(oldEditProc, hwnd, msg, wParam, lParam);
	}
	return 0;
}
/*----------------------------------------------*/

BOOL CALLBACK Demo(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static ListDemo<int> d(hdlg);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		oldEditProc = (WNDPROC)SetWindowLongPtr(GetDlgItem(hdlg, IDC_IN), GWLP_WNDPROC, (LONG_PTR)subEditProc);
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
		{
			EndDialog(hdlg, 0);
			break;
		}
		default:
		{
			d.getController()->cmd(LOWORD(wParam));
			break;
		}
		}
		break;
	}
	return FALSE;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DEMO), 0, Demo);
}