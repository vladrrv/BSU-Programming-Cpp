#include <iostream>
#include <conio.h>
using namespace std;

struct matrix
{
	char name[25];
	int rows;
	int cols;
	int *body;

	matrix(char *nm, int *m, int num_rows, int num_cols)
	{
		strcpy_s(name, nm);
		rows = num_rows;
		cols = num_cols;
		int bufSize = rows * cols * 4;
		body = new int[rows * cols];
		memcpy(body, m, bufSize);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				int *ptr = body + cols * i + j;
				cout << " " << name <<"[" << i+1 << "," << j+1 << "] = " << *ptr;
			}
			cout << endl;
		}
		cout << endl;
	}

	matrix* operator * (matrix &m2)
	{
		matrix m1 = *this;
		matrix *prod;
		int *pr_body = new int[m1.rows * m2.cols];
		for (int i = 0; i < m1.rows; i++)
		{
			for (int j = 0; j < m2.cols; j++)
			{
				_int64 s = 0;
				for (int k = 0; k < m1.cols; k++)
				{
					int *ptr1 = m1.body + m1.cols * i + k;
					int *ptr2 = m2.body + m2.cols * k + j;
					s += (*ptr1) * (*ptr2);
				}
				pr_body[i * m2.cols + j] = s;
			}
		}
		prod = new matrix("prod", pr_body, m1.rows, m2.cols);
		return prod;
	}

	bool operator == (matrix &m2)
	{
		if ((*this).rows != m2.rows || (*this).cols != m2.cols)
		{
			cout << "\nsize_error\n";
			return false;
		}
		int res = memcmp((*this).body, m2.body, m2.rows * m2.cols * 4);
		return (res == 0);
	}
};

void assert(int *a1, int h1, int w1, int *a2, int h2, int w2, int *res)
{
	matrix *m1, *m2, *result, *correct_res;
	m1 = new matrix("m1", a1, h1, w1);
	m2 = new matrix("m2", a2, h2, w2);
	correct_res = new matrix("tg", res, h1, w2);
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
	int	t0[] =
	{
		 1, 2,
		 3, 4,
		 5, 6,
		 7, 8
	}, r0 = 4, c0 = 2;
	int	t2[] =
	{
		 5, 4, 3 ,
		 2, 1, 0 
	}, r2 = 2, c2 = 3;
	int	p[] =
	{
		  9, 6, 3 ,
		 23, 16, 9 ,
		 37, 26, 15 ,
		 51, 36, 21 
	};
	assert(t0, r0, c0, t2, r2, c2, p);
	//--------------------------------------------
	int	t3[] =
	{
		  1,  2,  3 ,
		  4,  5,  6 ,
		  7,  8,  9 ,
		 10, 11, 12 ,
		 13, 14, 15 
	}, r3 = 5, c3 = 3;
	int	t4[] =
	{
		 17, 16, 15, 14, 13, 12 ,
		 11, 10,  9,  8,  7,  6 ,
		  5,  4,  3,  2,  1,  0 ,
	}, r4 = 3, c4 = 6;
	int	p2[] =
	{
		  54,  48,  42,  36,  30,  24 ,
		 153, 138, 123, 108,  93,  78 ,
		 252, 228, 204, 180, 156, 132 ,
		 351, 318, 285, 252, 219, 186 ,
		 450, 408, 366, 324, 282, 240 ,
	};
	assert(t3, r3, c3, t4, r4, c4, p2);
	_getch();
}