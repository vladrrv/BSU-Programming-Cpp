#include <iostream>
#include <conio.h>
using namespace std;

int *matrixMultiplication(int *m1, int r1, int c1, int *m2, int r2, int c2)
{
	int *prod = new int[r1*c2];
	for (int i = 0; i < r1; i++)
	{
		for (int j = 0; j < c2; j++)
		{
			int s = 0;
			for (int k = 0; k < c1; k++)
			{
				int *ptr1 = m1 + c1 * i + k;
				int *ptr2 = m2 + c2 * k + j;
				s += (*ptr1) * (*ptr2);
			}
			prod[i * c2 + j] = s;
		}
	}
	return prod;
}

void assert(int *matrix1, int row1, int col1, int *matrix2, int row2, int col2, int *correct_res)
{
	int *myRes = matrixMultiplication(matrix1, row1, col1, matrix2, row2, col2);
	int isEqual = memcmp(correct_res, myRes, row1*col2*4);
	if (isEqual == 0)
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