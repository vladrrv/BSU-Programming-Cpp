#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include "KSet.h"
#include "resource.h"
#include <windows.h>
#include <windowsx.h>
#include <string>
#include <sstream>
using namespace std;

template<class T> class KSetDemo;

template<class T>
class KSetController
{
	HWND hdlg;
	KSet<T>* model_1;
	KSet<T>* model_2;
	KSet<T>* model_out;
	KSetDemo<T>* view;
public:
	KSetController(KSet<T>* m1, KSet<T>* m2, KSet<T>* mo, KSetDemo<T>* v, HWND h)
	{
		hdlg = h;
		model_1 = m1;
		model_2 = m2;
		model_out = mo;
		view = v;
	}
	void cmd(UINT id)
	{
		switch (id)
		{
		case IDC_ADD1:
		{
			char c[32];
			Edit_GetLine(GetDlgItem(hdlg, IDC_EDIT1), 0, c, 32);
			Edit_SetText(GetDlgItem(hdlg, IDC_EDIT1), "");
			stringstream str(c);
			str >> (*model_1);
			view->refresh(hdlg);
			break;
		}
		case IDC_ADD2:
		{
			char c[32];
			Edit_GetLine(GetDlgItem(hdlg, IDC_EDIT2), 0, c, 32);
			Edit_SetText(GetDlgItem(hdlg, IDC_EDIT2), "");
			stringstream str(c);
			str >> (*model_2);
			view->refresh(hdlg);
			break;
		}
		case IDC_BUTTON3:
		{
			*model_out = (*model_1) + (*model_2);
			view->refresh(hdlg);
			break;
		}
		case IDC_BUTTON4:
		{
			*model_out = (*model_1) * (*model_2);
			view->refresh(hdlg);
			break;
		}
		case IDC_BUTTON5:
		{
			*model_out = (*model_1) / (*model_2);
			view->refresh(hdlg);
			break;
		}
		case IDC_BUTTON6:
		{
			*model_out = (*model_1) - (*model_2);
			view->refresh(hdlg);
			break;
		}
		case IDC_BUTTON7:
		{
			string text_out = ((*model_1) < (*model_2) ? "Set 1 is strictly included in Set 2" : "Set 1 is not strictly included in Set 2");
			view->refresh(hdlg, text_out);
			break;
		}
		case IDC_BUTTON8:
		{
			string text_out = ((*model_1) <= (*model_2) ? "Set 1 is included in Set 2" : "Set 1 is not included in Set 2");
			view->refresh(hdlg, text_out);
			break;
		}
		case IDC_BUTTON9:
		{
			model_1->swap(*model_2);
			model_out->clear();
			view->refresh(hdlg);
			break;
		}
		case IDC_SUM1:
		{
			GetSum<T> visitor;
			model_1->accept(visitor);
			string text_out = "Sum of all elements from set 1:\r\n" + to_string(visitor.value());
			view->refresh(hdlg, text_out);
			break;
		}
		case IDC_SUM2:
		{
			GetSum<T> visitor;
			model_2->accept(visitor);
			string text_out = "Sum of all elements from set 2:\r\n" + to_string(visitor.value());
			view->refresh(hdlg, text_out);
			break;
		}
		case IDC_CLEAR1:
		{
			model_1->clear();
			model_out->clear();
			view->refresh(hdlg);
			break;
		}
		case IDC_CLEAR2:
		{
			model_2->clear();
			model_out->clear();
			view->refresh(hdlg);
			break;
		}
		}
	}
};

template<class T>
class KSetDemo
{
	KSet<T>* model_1;
	KSet<T>* model_2;
	KSet<T>* model_out;
	KSetController<T>* controller;
	
	string s1;
	string s2;
	string so;
public:
	KSetDemo(HWND h)
	{
		model_1 = new KSet<T>();
		model_2 = new KSet<T>();
		model_out = new KSet<T>();
		controller = new KSetController<T>(model_1, model_2, model_out, this, h);
	}
	~KSetDemo()
	{
		delete model_1;
		delete model_2;
		delete model_out;
		delete controller;
	}
	void refresh(HWND hdlg, string text_out = "")
	{
		Edit_SetText(GetDlgItem(hdlg, IDC_EDIT11), "");
		Edit_SetText(GetDlgItem(hdlg, IDC_EDIT22), "");
		Edit_SetText(GetDlgItem(hdlg, IDC_EDIT0), "");
		s1 = " ", s2 = " ", so = " ";
		for (auto el : *model_1)
			s1 += (to_string(el) + ", ");
		if (s1.size() > 1) s1.erase(s1.size() - 2);
		for (auto el : *model_2)
			s2 += (to_string(el) + ", ");
		if (s2.size() > 1) s2.erase(s2.size() - 2);
		for (auto el : *model_out)
			so += (to_string(el) + ", ");
		if (so.size() > 1) so.erase(so.size() - 2);
		Edit_SetText(GetDlgItem(hdlg, IDC_EDIT11), s1.c_str());
		Edit_SetText(GetDlgItem(hdlg, IDC_EDIT22), s2.c_str());
		if (text_out.empty())
			Edit_SetText(GetDlgItem(hdlg, IDC_EDIT0), so.c_str());
		else
			Edit_SetText(GetDlgItem(hdlg, IDC_EDIT0), text_out.c_str());

	}
	KSetController<T>* getController() const
	{
		return controller;
	}
};

/*-----------Edit Control Subclassing-----------*/
WNDPROC oldEditProc1;
WNDPROC oldEditProc2;
LRESULT CALLBACK subEditProc1(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
		{
			SendMessage(GetParent(hwnd), WM_COMMAND, (WPARAM)IDC_ADD1, MAKELPARAM(0, 0));
			break;
		}
		}
	default:
		return CallWindowProc(oldEditProc1, hwnd, msg, wParam, lParam);
	}
	return 0;
}
LRESULT CALLBACK subEditProc2(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
		{
			SendMessage(GetParent(hwnd), WM_COMMAND, (WPARAM)IDC_ADD2, MAKELPARAM(0, 0));
			break;
		}
		}
	default:
		return CallWindowProc(oldEditProc2, hwnd, msg, wParam, lParam);
	}
	return 0;
}
/*----------------------------------------------*/

BOOL CALLBACK Demo(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static KSetDemo<int> d(hdlg);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		oldEditProc1 = (WNDPROC)SetWindowLongPtr(GetDlgItem(hdlg, IDC_EDIT1), GWLP_WNDPROC, (LONG_PTR)subEditProc1);
		oldEditProc2 = (WNDPROC)SetWindowLongPtr(GetDlgItem(hdlg, IDC_EDIT2), GWLP_WNDPROC, (LONG_PTR)subEditProc2);
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