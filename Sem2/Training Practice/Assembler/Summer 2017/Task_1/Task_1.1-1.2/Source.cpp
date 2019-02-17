#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <windows.h>
#include <windowsx.h>
#include "resource.h"

extern "C" char** _stdcall parse(char* str, int len, char** words);

INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wparam))
		{
		case IDOK:
		{
			EndDialog(hdlg, 1);
			break;
		}
		case IDCANCEL:
		{
			EndDialog(hdlg, 0);
			break;
		}
		case IDC_CHOOSE:
		{

			OPENFILENAME ofn;
			char szFile[260], buf[260];
			char *words[130] = {};

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hdlg;
			ofn.lpstrFile = szFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			
			if (GetOpenFileName(&ofn) == TRUE)
				ListBox_AddItemData(GetDlgItem(hdlg, IDC_LIST1), ofn.lpstrFile);

			strcpy_s(buf, ofn.lpstrFile);
			parse(buf, strlen(buf), words);

			for (int i = 0; words[i] != NULL; i++)
				ListBox_AddItemData(GetDlgItem(hdlg, IDC_LIST1), words[i]);

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
	bool ok = DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	if (ok)
		MessageBox(0, "You've pressed 'OK' button", "OK", MB_OK);
	else
		MessageBox(0, "You've pressed 'Cancel' button", "Cancel", MB_OK);
	return 0;
}