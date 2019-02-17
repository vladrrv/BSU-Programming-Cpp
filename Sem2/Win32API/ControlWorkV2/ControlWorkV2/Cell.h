#pragma once

int N = 10;
int M = 10;
int LEN = 4;
#define RES 1
#define RAB 2
#define EMPTY 0

class Cell
{
	int i;
	int j;
	int state;
public:
	Cell(int _i = 0, int _j = 0, int st = rand()%4)
	{
		i = _i;
		j = _j;
		state = (st!=0)?RES:EMPTY;
	}
	int getState()
	{
		return state;
	}
	void setState(int st)
	{
		state = st;
	}
	int get_i()
	{
		return i;
	}
	int get_j()
	{
		return j;
	}
	RECT getRect(RECT rc)
	{
		float
			w = (float)(rc.right - rc.left) / N,
			h = (float)(rc.bottom - rc.top) / M,
			x = (j + 1)*w, y = (i + 1)*h;
		return RECT{ (int)(j*w), (int)(i*h), (int)((j + 1)*w), (int)((i + 1)*h) };
	}
	void draw(RECT rc, HDC hdc) 
	{
		if (state != EMPTY)
		{
			RECT r = getRect(rc);
			HBRUSH hbr = CreateSolidBrush(RGB(100, 200, 100));
			HPEN hpen = CreatePen(PS_SOLID, 4, RGB(200, 100, 100));
			HGDIOBJ hbr_old, hpen_old;
			hpen_old = SelectObject(hdc, hpen);
			hbr_old = SelectObject(hdc, hbr);
			FillRect(hdc, &r, hbr);
			SelectObject(hdc, hbr_old);
			DeleteObject(hbr);
			if (state == RAB)
			{
				SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
				Ellipse(hdc, r.left, r.top, r.right, r.bottom);
			}
			SelectObject(hdc, hpen_old);
			DeleteObject(hpen);
		}
	}
};
