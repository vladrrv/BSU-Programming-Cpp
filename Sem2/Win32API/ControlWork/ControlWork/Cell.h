#pragma once

int N = 30;
int M = 30;
int I_START = 10;
int J_START = 10;
int STEP = 1;
COLORREF PT_COLOR = RGB(200,200,200);
#define WORM 1
#define TRACE 2
#define EMPTY 0

class Cell
{
	int i;
	int j;
	int state;
	int i_c;
public:
	Cell(int _i = 0, int _j = 0, int st = EMPTY)
	{
		i = _i;
		j = _j;
		state = st;
		i_c = 1;
	}
	int getState()
	{
		return state;
	}
	void setState(int st)
	{
		state = st;
	}
	int& get_i_c()
	{
		return i_c;
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
			HBRUSH hbr;
			HGDIOBJ hbr_old;
			switch (state)
			{
			case WORM:
			{
				hbr = CreateSolidBrush(PT_COLOR);
				hbr_old = SelectObject(hdc, hbr);
				FillRect(hdc, &r, hbr);
				SelectObject(hdc, hbr_old);
				DeleteObject(hbr);
				break; 
			}
			case TRACE:
				hbr = CreateSolidBrush(RGB(90.0 - i_c*4, 90.0 - i_c*4, 90.0 - i_c*4));
				hbr_old = SelectObject(hdc, hbr);
				FillRect(hdc, &r, hbr);
				SelectObject(hdc, hbr_old);
				DeleteObject(hbr);
				break;
			}
		}
	}
};
