#include <iostream>
#include <conio.h>
using namespace std;

double *max3(double b[], int len)
{
	double nums[3] = { b[0], b[1], b[2] };
	double product = nums[0] * nums[1] * nums[2];
	for (int i = 0; i < (len - 2); i++)
	{
		for (int j = i + 1; j < (len - 1); j++)
		{
			for (int k = j + 1; k < len; k++)
			{
				if (b[i] * b[j] * b[k] > product)
				{
					nums[0] = b[i];
					nums[1] = b[j];
					nums[2] = b[k];
					product = nums[0] * nums[1] * nums[2];
				}
			}
		}
	}
	return nums;
}

void assert(double *seq, int seq_len, double *res_nums)
{
	if (memcmp(max3(seq, seq_len), res_nums, 24) == 0)
		cout << "Correct\n\n";
	else
		cout << "Incorrect\n\n";
}

void main()
{
	double sequence1[] = { 0, 1, 2, 3, 4, 1, 2 };
	double ans1[] = { 2, 3, 4 };
	assert(sequence1, 7, ans1);

	double sequence2[] = { 7, 46, 8, 4, 1 };
	double ans2[] = { 7, 46, 8 };
	assert(sequence2, 5, ans2);

	double sequence3[] = { -1, 0, 15, -58, -5, -9, 10 };
	double ans3[] = { 15, -58, -9 };
	assert(sequence3, 7, ans3);

	double sequence4[] = { -11, -2, -15, -58, -5, -9, 0 };
	double ans4[] = { -11, -2, 0 };
	assert(sequence4, 7, ans4);

	double sequence5[] = { -1, -5, -15, -48, -5, -5 };
	double ans5[] = { -1, -5, -5 };
	assert(sequence5, 6, ans5);

	_getch();
}