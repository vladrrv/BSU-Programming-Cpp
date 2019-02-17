//#undef UNICODE 
#include <windows.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "Создание окна Windows";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	/* хотя параметр hPrevInstance в Win32 всегда равно NULL продолжаем проверять его значение */
	if (!hPrevInstance)
	{  /* инициализируем приложение - подготавливаем данные класса окна и регистрируем его */
		if (!InitApplication(hInstance))
			return (FALSE);
	}
	/* завершаем создание копии приложения - создаем главное окно приложения */
	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);

	/* Цикл обработки сообщений */
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
	// Заполняем структуру класса окна WNDCLASS 
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
	// Регистрируем класс окна 
	return RegisterClass(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd = CreateWindow(
		szClassName,         // указатель на строку зарегистрированного имени класса 
		szTitle,             // указатель на строку заголовка окна 
		WS_OVERLAPPEDWINDOW, // стиль окна 
		CW_USEDEFAULT,       // горизонтальная координата окна 
		CW_USEDEFAULT,       // вертикальная координата окна 
		CW_USEDEFAULT,       // ширина окна 
		CW_USEDEFAULT,       // высота окна 
		NULL,                // дескриптор родительского окна 
		NULL,                // дескриптор меню окна 
		hInstance,           // дескриптор экземпляра приложения 
		NULL);               // указатель на дополнительные данные окна 
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
		TextOut(hDC, 250, 200, "Обработка сообщения WM_PAINT", 28);
		
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