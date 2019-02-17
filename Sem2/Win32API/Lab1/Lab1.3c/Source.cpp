//#undef UNICODE 
#include <windows.h> 
#include <fstream> 
#include <vector> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "TIMETABLE";

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
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE - 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	return RegisterClass(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd = CreateWindow(
		szClassName,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hWnd) return FALSE;
	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);
	return TRUE;
}
struct tile
{
	int pos;
	int s;
	char name[256];
	char room[32];
};
void addTile(HWND hWnd, HDC hdc, tile t)
{
	RECT rect, tilerect;
	HPEN hPen;
	HBRUSH hBrush;
	HFONT hFont;
	HGDIOBJ hOldPen, hOldBrush, hOldFont;
	int
		clrR = 0,
		clrG = 0,
		clrB = 0;
	LPSTR subjtypename = "DEFAULT";
	GetClientRect(hWnd, &rect);
	float
		width = rect.right - rect.left,
		height = rect.bottom - rect.top,
		extraw =  width / 32,
		extrah = height / 16,
		hgint = (height - extrah) / 3,
		wdint = (width - extraw * 2) / 8,
		x1 = (t.pos % 4)*wdint + (t.pos / 12)*wdint * 4 + (t.pos / 12 + 1)*extraw,
		y1 = (t.pos / 4)*hgint - (t.pos / 12)*hgint * 3 + extrah,
		x2 = x1 + wdint,
		y2 = y1 + hgint;
	tilerect = { (int)x1,(int)y1,(int)x2,(int)y2 };

	switch (t.s)
	{
	case 0:
		subjtypename = "(Lecture)";
		clrR = 250;
		clrG = 250;
		clrB = 200;
		break;
	case 1:
		subjtypename = "(Practics)";
		clrR = 150;
		clrG = 200;
		clrB = 200;
		break;
	case 2:
		subjtypename = "";
		clrR = 200;
		clrG = 250;
		clrB = 100;
		break;
	}

	hFont = CreateFont(hgint / 8, wdint / 20, 0, 0, FW_DEMIBOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");
	hOldFont = SelectObject(hdc, hFont);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, RGB(clrR, clrG, clrB));
	Rectangle(hdc, x1, y1, x2, y2);

	SetBkMode(hdc, TRANSPARENT);

	DrawText(hdc, t.name, -1, &tilerect, DT_SINGLELINE | DT_TOP | DT_CENTER);

	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);

	hFont = CreateFont(hgint / 8, wdint / 20, 0, 0, FW_LIGHT, 1, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");
	hOldFont = SelectObject(hdc, hFont);

	DrawText(hdc, subjtypename, -1, &tilerect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	DrawText(hdc, t.room, -1, &tilerect, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);

	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);
}
std::vector<tile> vct;
void rdfile()
{
	std::ifstream infile("input.txt");
	while (!infile.eof())
	{
		int num = 0;
		int s = 0;
		char str[256], r[256];
		infile >> num >> s >> str >> r;
		tile t{ num, s, "", "" };
		strcpy_s(t.name, str);
		strcpy_s(t.room, r);
		vct.push_back(t);
	}
	infile.close();
}
void displayDrawings(HWND hWnd)
{
	HDC hdc;
	RECT rect, dayrect;
	PAINTSTRUCT ps;
	LOGFONT lFont;
	HFONT hFont;
	HPEN hPen;
	HBRUSH hBrush;
	HGDIOBJ hOldPen, hOldBrush, hOldFont;
	hdc = BeginPaint(hWnd, &ps);

	GetClientRect(hWnd, &rect);
	float
		width = rect.right - rect.left,
		height = rect.bottom - rect.top,
		extraw = width / 32,
		extrah = height / 16,
		hgint = (height - extrah) / 3,
		wdint = (width - extraw * 2) / 8;

	SetBkMode(hdc, TRANSPARENT);
	hFont = CreateFont(2 * extraw / 3, height / 50, 4500, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");
	hOldFont = SelectObject(hdc, hFont);
	dayrect = { 10, (int)extrah, (int)extraw, (int)extrah + (int)hgint };
	DrawText(hdc, "Monday", -1, &dayrect, DT_SINGLELINE | DT_BOTTOM);
	dayrect.bottom += hgint;
	dayrect.top += hgint;
	DrawText(hdc, "Tuesday", -1, &dayrect, DT_SINGLELINE | DT_BOTTOM);
	dayrect.bottom += hgint;
	dayrect.top += hgint;
	DrawText(hdc, "Wednesday", -1, &dayrect, DT_SINGLELINE | DT_BOTTOM);
	dayrect.left += width / 2;
	dayrect.right += width / 2;
	DrawText(hdc, "Saturday", -1, &dayrect, DT_SINGLELINE | DT_BOTTOM);
	dayrect.bottom -= hgint;
	dayrect.top -= hgint;
	DrawText(hdc, "Friday", -1, &dayrect, DT_SINGLELINE | DT_BOTTOM);
	dayrect.bottom -= hgint;
	dayrect.top -= hgint;
	DrawText(hdc, "Thursday", -1, &dayrect, DT_SINGLELINE | DT_BOTTOM);
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);

	hFont = CreateFont(extrah / 2, wdint / 20, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");
	hOldFont = SelectObject(hdc, hFont);
	dayrect = { (int)extraw, 0, (int)extraw + (int)wdint, (int)extrah };
	DrawText(hdc, "8:15 - 9:35", -1, &dayrect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	dayrect.left += wdint;
	dayrect.right += wdint;
	DrawText(hdc, "9:45 - 11:05", -1, &dayrect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	dayrect.left += wdint;
	dayrect.right += wdint;
	DrawText(hdc, "11:15 - 12:35", -1, &dayrect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	dayrect.left += wdint;
	dayrect.right += wdint;
	DrawText(hdc, "13:00 - 14:20", -1, &dayrect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	dayrect.left += wdint+extraw;
	dayrect.right += wdint+extraw;
	DrawText(hdc, "8:15 - 9:35", -1, &dayrect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	dayrect.left += wdint;
	dayrect.right += wdint;
	DrawText(hdc, "9:45 - 11:05", -1, &dayrect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	dayrect.left += wdint;
	dayrect.right += wdint;
	DrawText(hdc, "11:15 - 12:35", -1, &dayrect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	dayrect.left += wdint;
	dayrect.right += wdint;
	DrawText(hdc, "13:00 - 14:20", -1, &dayrect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);

	for (tile t : vct)
		addTile(hWnd, hdc, t);

	hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 100));
	hOldPen = SelectObject(hdc, hPen);
	SelectObject(hdc, GetStockObject(DC_BRUSH));

	MoveToEx(hdc, width / 2, 0, NULL);
	LineTo(hdc, width / 2, height);
	MoveToEx(hdc, 0, extrah, NULL);
	LineTo(hdc, width, extrah);
	MoveToEx(hdc, 0, extrah + (height - extrah)/ 3, NULL);
	LineTo(hdc, width, extrah + (height - extrah) / 3);
	MoveToEx(hdc, 0, extrah + 2* (height - extrah) / 3, NULL);
	LineTo(hdc, width, extrah + 2* (height - extrah) / 3);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);

	hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 100));
	hOldPen = SelectObject(hdc, hPen);
	MoveToEx(hdc, extraw, 0, NULL);
	LineTo(hdc, extraw, height);
	MoveToEx(hdc, extraw + width / 2, 0, NULL);
	LineTo(hdc, extraw + width / 2, height);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);

	EndPaint(hWnd, &ps);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_CREATE:
		rdfile();
		break;
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 1000;
		lpMMI->ptMinTrackSize.y = 500;
	}
	case WM_PAINT:
		displayDrawings(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}