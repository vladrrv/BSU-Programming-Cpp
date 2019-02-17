//#undef UNICODE 
#include <windows.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "�������� ���� Windows";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	/* ���� �������� hPrevInstance � Win32 ������ ����� NULL ���������� ��������� ��� �������� */
	if (!hPrevInstance)
	{  /* �������������� ���������� - �������������� ������ ������ ���� � ������������ ��� */
		if (!InitApplication(hInstance))
			return (FALSE);
	}
	/* ��������� �������� ����� ���������� - ������� ������� ���� ���������� */
	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);

	/* ���� ��������� ��������� */
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
	// ��������� ��������� ������ ���� WNDCLASS 
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE - 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	// ������������ ����� ���� 
	return RegisterClass(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd = CreateWindow(
		szClassName,         // ��������� �� ������ ������������������� ����� ������ 
		szTitle,             // ��������� �� ������ ��������� ���� 
		WS_OVERLAPPEDWINDOW, // ����� ���� 
		CW_USEDEFAULT,       // �������������� ���������� ���� 
		CW_USEDEFAULT,       // ������������ ���������� ���� 
		CW_USEDEFAULT,       // ������ ���� 
		CW_USEDEFAULT,       // ������ ���� 
		NULL,                // ���������� ������������� ���� 
		NULL,                // ���������� ���� ���� 
		hInstance,           // ���������� ���������� ���������� 
		NULL);               // ��������� �� �������������� ������ ���� 
	if (!hWnd) return FALSE;
	ShowWindow(hWnd, SW_MAXIMIZE);
	UpdateWindow(hWnd);
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	static RECT rect;
	switch (message)
	{
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		Rectangle(hDC, 10, 10, rect.right - rect.left - 10, rect.bottom - rect.top - 10);
		Ellipse(hDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top);
		TextOut(hDC, 250, 200, "��������� ��������� WM_PAINT", 28);
		
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}