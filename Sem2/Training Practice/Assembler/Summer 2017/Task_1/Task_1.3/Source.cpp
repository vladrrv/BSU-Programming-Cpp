#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <windows.h>
#include <windowsx.h>
#include "resource.h"

extern "C" void _stdcall IntToHex(unsigned n, char* hex);

INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wparam))
		{
		case IDCLOSE:
		{
			EndDialog(hdlg, 0);
			break;
		}
		case IDC_CONVERT:
		{
			char input[256], hex[256];
			Edit_GetText(GetDlgItem(hdlg, IDC_EDIT1), input, 256);
			IntToHex(atoi(input), hex);
			Edit_SetText(GetDlgItem(hdlg, IDC_EDIT2), hex);
			break;
		}
		}
		break;
	}
	case WM_CLOSE:
		EndDialog(hdlg, 0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);

	return 0;
}