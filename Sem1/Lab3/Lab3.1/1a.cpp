/*#include <iostream>
#include <conio.h>
using namespace std;

struct matrix
{
	int height;
	int width;
	int **body;
	matrix(int *m, int h, int w)
	{
		width = w;
		height = h;
		body = new int*[height];
		for (int i = 0; i < height; i++)
		{
			body[i] = new int[width];
			for (int j = 0; j < width; j++)
			{
				body[i][j] = m[i * width + j];
			}
		}
	}

	matrix* operator * (matrix &m2)
	{
		matrix m1 = *this;
		matrix *prod;
		int *pr_body = new int[m1.height * m2.width];
		for (int i = 0; i < m1.height; i++)
		{
			for (int j = 0; j < m2.width; j++)
			{
				int s = 0;
				for (int k = 0; k < m1.width; k++)
				{
					s += m1.body[i][k] * m2.body[k][j];
				}
				pr_body[i * m2.width + j] = s;
				cout << "pr_body[" << i + 1 << "][" << j + 1 << "] = " << pr_body[i * m2.width + j] << endl;
			}
		}
		prod = new matrix(pr_body, m1.height, m2.width);
		return prod;
	}

	bool operator == (matrix &m2)
	{
		matrix m1 = *this;
		int h = m2.height, w = m2.width;
		if (m1.height != h || m1.width != w)
		{
			cout << "\nsize_error\n";
			return false;
		}
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if (m1.body[i][j] != m2.body[i][j])
				{
					cout << "\nelement_error\n";
					return false;
				}
			}
		}
		return true;
	}
};

void assert(int *a1, int h1, int w1, int *a2, int h2, int w2, int *res)
{
	matrix *m1, *m2, *result, *correct_res;
	m1 = new matrix(a1, h1, w1);
	m2 = new matrix(a2, h2, w2);
	correct_res = new matrix(res, h1, w2);
	result = (*m1) * (*m2);
	if (*result == *correct_res)
	{
		cout << "Correct\n\n";
	}
	else
	{
		cout << "Incorrect\n\n";
	}
}

void main()
{
	int	t1[4][2] =
	{
		{ 1, 2 },
		{ 3, 4 },
		{ 5, 6 },
		{ 7, 8 }
	}, h1 = 4, w1 = 2;
	int	t2[2][3] =
	{
		{ 5, 4, 3 },
		{ 2, 1, 0 }
	}, h2 = 2, w2 = 3;
	int	p[4][3] =
	{
		{ 9, 6, 3 },
		{ 23, 16, 9 },
		{ 37, 26, 15 },
		{ 51, 36, 21 }
	};
	assert(*t1, h1, w1, *t2, h2, w2, *p);
	//--------------------------------------------
	int	t3[5][3] =
	{
		{ 1,  2,  3 },
		{ 4,  5,  6 },
		{ 7,  8,  9 },
		{ 10, 11, 12 },
		{ 13, 14, 15 }
	}, h3 = 5, w3 = 3;
	int	t4[3][6] =
	{
		{ 17, 16, 15, 14, 13, 12 },
		{ 11, 10,  9,  8,  7,  6 },
		{ 5,  4,  3,  2,  1,  0 },
	}, h4 = 3, w4 = 6;
	int	p2[5][6] =
	{
		{ 54,  48,  42,  36,  30,  24 },
		{ 153, 138, 123, 108,  93,  78 },
		{ 252, 228, 204, 180, 156, 132 },
		{ 351, 318, 285, 252, 219, 186 },
		{ 450, 408, 366, 324, 282, 240 },
	};
	assert(*t3, h3, w3, *t4, h4, w4, *p2);
	_getch();
}*/