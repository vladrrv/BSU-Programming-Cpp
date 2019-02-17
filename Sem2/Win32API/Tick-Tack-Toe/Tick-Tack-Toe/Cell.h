#pragma once

int N = 20;
int M = 20;
int TOWIN = 3;
bool PVP = true;

#define _O_ 1
#define _X_ 2
#define _EMPTY_ 0

int PLAY_AS = _O_;

class Cell
{
	int i;
	int j;
	int state;
public:
	Cell(int _i = 0, int _j = 0, int st = _EMPTY_)
	{
		i = _i;
		j = _j;
		state = st;
	}
	int getState()
	{
		return state;
	}
	int get_i()
	{
		return i;
	}
	int get_j()
	{
		return j;
	}
	POINT getCenter(RECT rc)
	{
		float
			w = (float)(rc.right - rc.left) / N,
			h = (float)(rc.bottom - rc.top) / M,
			x = (2*j + 1)*w / 2, y = (2*i + 1)*h / 2;
		return POINT{(int)x, (int)y};
	}
	bool hit(RECT rc, int x, int y, int player)
	{
		float
			w = (float)(rc.right - rc.left) / N,
			h = (float)(rc.bottom - rc.top) / M,
			x1 = j*w, y1 = i*h,
			x2 = (j + 1)*w, y2 = (i + 1)*h;

		if ((state == _EMPTY_) && (x1 < x && x2 > x) && (y1 < y && y2 > y))
		{
			state = player;
			return true;
		}

		return false;
	}
	void draw(RECT rc, HDC hdc)
	{
		if (state != _EMPTY_)
		{
			HPEN hPen;
			HGDIOBJ hOldPen;
			float
				w = (float)(rc.right - rc.left) / N,
				h = (float)(rc.bottom - rc.top) / M,
				dw = w / 5,
				dh = h / 5,
				d = sqrt(dw * dh) / 2,
				x1 = j*w, y1 = i*h,
				x2 = (j + 1)*w, y2 = (i + 1)*h;
			switch (state)
			{
			case _O_:
				hPen = CreatePen(PS_SOLID, d, RGB(200, 200, 200));
				hOldPen = SelectObject(hdc, hPen);
				SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
				Ellipse(hdc, x1 + dw, y1 + dh, x2 - dw, y2 - dh);
				SelectObject(hdc, hOldPen);
				DeleteObject(hPen);
				break;
			case _X_:
				hPen = CreatePen(PS_SOLID, d, RGB(255, 100, 100));
				hOldPen = SelectObject(hdc, hPen);
				MoveToEx(hdc, x1 + dw, y1 + dh, 0);
				LineTo(hdc, x2 - dw, y2 - dh);
				MoveToEx(hdc, x2 - dw, y1 + dh, 0);
				LineTo(hdc, x1 + dw, y2 - dh);
				SelectObject(hdc, hOldPen);
				DeleteObject(hPen);
				break;
			}
		}
	}
};
