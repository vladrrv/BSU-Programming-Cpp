#include <iostream>
#include <conio.h>
using namespace std;

int *polynomSum(int *polynom1, int pow1, int *polynom2, int pow2)
{
	int sumPow;
	int smallerPow;
	if (pow1 > pow2)
	{
		sumPow = pow1;
		smallerPow = pow2;
	}
	else
	{
		sumPow = pow2;
		smallerPow = pow1;
	}
	int *sum = new int[sumPow];
	for (int i = 0; i < smallerPow; i++)
	{
		sum[i] = polynom1[i] + polynom2[i];
	}
	for (int i = smallerPow; i < sumPow; i++)
	{
		sum[i] = (sumPow == pow1)? polynom1[i] : polynom2[i];
	}
	
	return sum;
}

int *polynomProd(int *polynom1, int pow1, int *polynom2, int pow2)
{
	int prodPow = pow1 + pow2 - 1;
	int *prod = new int[prodPow];
	for (int i = 0; i < prodPow; i++)
	{
		prod[i] = 0;
	}
	for (int i = 0; i < pow1; i++)
	{
		for (int j = 0; j < pow2; j++)
		{
			prod[i + j] += polynom1[i] * polynom2[j];
		}
	}
	return prod;
}

void assertSum(int *p1, int pow1, int *p2, int pow2, int *res)
{
	int *myRes = polynomSum(p1, pow1, p2, pow2);
	int resPow = (pow1 > pow2) ? pow1 : pow2;
	for (int i = resPow - 1; i >= 0; i--)
	{
		if (myRes[i] == 0)
			resPow--;
		else
			break;
	}
	int isEqual = memcmp(res, myRes, resPow*4);
	if (isEqual == 0)
		cout << "Correct\n\n";
	else
		cout << "Incorrect\n\n";
}
void assertProd(int *p1, int pow1, int *p2, int pow2, int *res)
{
	int *myRes = polynomProd(p1, pow1, p2, pow2);
	int resPow = pow1 + pow2 - 1;
	for (int i = resPow - 1; i >= 0; i--)
	{
		if (myRes[i] == 0)
			resPow--;
		else
			break;
	}
	int isEqual = memcmp(res, myRes, resPow*4);
	if (isEqual == 0)
		cout << "Correct\n\n";
	else
		cout << "Incorrect\n\n";
}
void main()
{
	int p11[] = { -5, 2, -6 },
		p22[] = { 2, -2, 6 },
		r11[] = { -3 };
	assertSum(p11, 3, p22, 3, r11);

	int p1[] = { 1, 2, 3 },
		p2[] = { 2, 4 },
		r1[] = { 3, 6, 3 };
	assertSum(p2, 2, p1, 3, r1);

	int p3[] = { 6, 3, 1, 1 },
		p4[] = { 0, 3, 2 },
		r2[] = { 0, 18, 21, 9, 5, 2 };
	assertProd(p3, 4, p4, 3, r2);

	int p5[] = { 0, 0, 0, 1 },
		p6[] = { 0, 0, 2 },
		r3[] = { 0, 0, 0, 0, 0, 2 };
	assertProd(p5, 4, p6, 3, r3);

	int p7[] = { 3, 0, 0, 0 },
		p8[] = { 3, 2, 0 },
		r4[] = { 9, 6, 0 };
	assertProd(p7, 4, p8, 3, r4);

	int p9[] = { 1, -1 },
		p10[] = { 1, 1 },
		r5[] = { 1, 0, -1 };
	assertProd(p9, 2, p10, 2, r5);

	_getch();
}