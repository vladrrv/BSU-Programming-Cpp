/*#include <iostream>
#include <conio.h>
using namespace std;

bool prod(double *ptr[3], double *res)
{
	*res = 1;
	for (int i = 0; i < 3; i++)
	{
		if (ptr[i] == NULL)
		{
			return false;
		}
		else
			*res *= *(ptr[i]);
	}
	return true;
}
void print(double *ptr[3])
{
	for (int i = 0; i < 3; i++)
	{
		cout << ((ptr[i] != NULL) ? (*(ptr[i])) : 0) << "  ";
	}
	cout << endl;
}

double selectMax3(double b[], int len)
{
	double *neg3[3] = { NULL, NULL, NULL };
	double *zero[3] = { NULL, NULL, NULL };
	double *neg2pos1[3] = { NULL, NULL, NULL };
	double *pos3[3] = { NULL, NULL, NULL };

	for (int i = 0; i < len; i++)
	{
		if (b[i] < 0)
		{
			for (int j = 0; j < 3; j++)
				if ((neg3[j] == NULL) || (neg3[j] != NULL && b[i] > *neg3[j]))
				{
					for (int k = 1; k >= j; k--)
					{
						neg3[k + 1] = neg3[k];
					}

					neg3[j] = (b + i);
					break;
				}
			for (int j = 0; j < 2; j++)
				if ((neg2pos1[j] == NULL) || (neg2pos1[j] != NULL && abs(b[i]) > abs(*neg2pos1[j])))
				{
					for (int k = 0; k >= j; k--)
					{
						neg2pos1[k + 1] = neg2pos1[k];
					}
					neg2pos1[j] = (b + i);
					break;
				}
		}
		else
			if (b[i] == 0)
			{
				for (int j = 0; j < 2; j++)
					zero[j] = (b + i);
			}
			else
			{
				if ((neg2pos1[2] == NULL) || (neg2pos1[2] != NULL && b[i] > *neg2pos1[2]))
					neg2pos1[2] = (b + i);

				for (int j = 0; j < 3; j++)
					if ((pos3[j] == NULL) || (pos3[j] != NULL && b[i] > *pos3[j]))
					{
						for (int k = 1; k >= j; k--)
						{
							pos3[k + 1] = pos3[k];
						}
						pos3[j] = (b + i);
						break;
					}
			}
	}
	double prod_neg3, prod_zero, prod_neg2pos1, prod_pos3;
	bool res_neg3 = prod(neg3, &prod_neg3);
	bool res_zero = prod(zero, &prod_zero);
	bool res_neg2pos1 = prod(neg2pos1, &prod_neg2pos1);
	bool res_pos3 = prod(pos3, &prod_pos3);
	if (res_pos3 && res_neg2pos1)
	{
		return ((prod_pos3 >= prod_neg2pos1) ? prod_pos3 : prod_neg2pos1);
	}
	else
	{
		if (res_pos3)
		{
			print(pos3);
			return res_pos3;
		}
		else
			if (prod_neg2pos1)
			{
				print(neg2pos1);
				return prod_neg2pos1;
			}
	}

	if (res_zero)
	{
		print(zero);
		return prod_zero;
	}
	else
	{
		print(neg3);
		return prod_neg3;
	}
}

void main()
{
	double sequence[] = { 0, 1, 2, 3, 4, 1, 2 };
	double ans[] = { 2, 3, 4 };
	double sequence2[] = { 7, 46, 8, 4, 1 };
	double ans2[] = { 7, 46, 8 };
	double sequence3[] = { -1, 0, 15, -58, -5, -9, 10 };
	double ans3[] = { 15, -58, -9 };
	double sequence4[] = { -11, -2, -15, -58, -5, -9, 0 };
	double ans4[] = { 0, -58, -9 };


	selectMax3(sequence, sizeof(sequence) / 8);
	selectMax3(sequence3, sizeof(sequence) / 8);
	selectMax3(sequence4, sizeof(sequence) / 8);

	_getch();
}*/