#include <iostream>
#include <conio.h>
using namespace std;

struct polynomial
{
	int power;
	double *coeff;
	polynomial(int p, double *c)
	{
		power = p;
		coeff = new double[p + 1];
		memcpy(coeff, c, 8*(p + 1));
	}
	polynomial* operator + (polynomial &p2)
	{
		polynomial p1 = *this;
		polynomial *sum;
		double *sumCoeff, sumPow = p1.power, smPow = p2.power;
		if (p1.power < p2.power)
			swap(sumPow, smPow);
		sumCoeff = new double[sumPow];
		for (int i = 0; i < smPow; i++)
		{
			sumCoeff[i] = p1.coeff[i] + p2.coeff[i];
		}
		for (int i = smPow; i < sumPow; i++)
		{
			if (p1.power > p2.power)
				sumCoeff[i] = p1.coeff[i];
			else
				sumCoeff[i] = p2.coeff[i];
		}
		for (int i = sumPow - 1; i >= 0; i--)
			if (sumCoeff[i] == 0)
				sumPow--;
			else
				break;
		sum = new polynomial(sumPow, sumCoeff);
		return sum;
	}

	polynomial* operator * (polynomial &p2)
	{
		polynomial p1 = *this;
		polynomial *prod;
		int prodPow = p1.power + p2.power - 1;
		double *prodCoeff = new double[prodPow];
		for (int i = 0; i < prodPow; i++)
		{
			prodCoeff[i] = 0;
		}
		for (int i = 0; i < p1.power; i++)
		{
			for (int j = 0; j < p2.power; j++)
			{
				prodCoeff[i + j] += p1.coeff[i] * p2.coeff[j];
			}
		}
		for (int i = prodPow - 1; i >= 0; i--)
			if (prodCoeff[i] == 0)
				prodPow--;
			else
				break;
		prod = new polynomial(prodPow, prodCoeff);
		return prod;
	}

	bool operator == (polynomial &p2)
	{
		if (memcmp((*this).coeff, p2.coeff, 8*((*this).power)) == 0)
			return true;
		else
			return false;
	}
};

void assertSum(double *p1, int pow1, double *p2, int pow2, double *res)
{
	polynomial *pol1 = new polynomial(pow1, p1);
	polynomial *pol2 = new polynomial(pow2, p2);
	polynomial *myRes = *pol1 + *pol2;
	polynomial *result = new polynomial((pow1>pow2)?pow1:pow2, res);

	if (*myRes == *result)
		cout << "Correct\n\n";
	else
		cout << "Incorrect\n\n";
}
void assertProd(double *p1, int pow1, double *p2, int pow2, double *res)
{
	polynomial *pol1 = new polynomial(pow1, p1);
	polynomial *pol2 = new polynomial(pow2, p2);
	polynomial *myRes = (*pol1) * (*pol2);
	polynomial *result = new polynomial(pow1 + pow2 - 1, res);

	if (*myRes == *result)
		cout << "Correct\n\n";
	else
		cout << "Incorrect\n\n";
}
void main()
{
	double p11[] = { -5, 2, -6, 0 };
	double p22[] = { 2, -2, 6, 0 };
	double r11[] = { -3 };
	assertSum(p11, 3, p22, 3, r11);

	double p1[] = { 1, 2, 3 };
	double p2[] = { 2, 4 };
	double r1[] = { 3, 6, 3 };
	assertSum(p2, 2, p1, 3, r1);

	double p3[] = { 6, 3, 1, 1 };
	double p4[] = { 0, 3, 2 };
	double r2[] = { 0, 18, 21, 9, 5, 2 };
	assertProd(p3, 4, p4, 3, r2);

	double p5[] = { 0, 0, 0, 1 };
	double p6[] = { 0, 0, 2 };
	double r3[] = { 0, 0, 0, 0, 0, 2 };
	assertProd(p5, 4, p6, 3, r3);

	double p7[] = { 3, 0, 0, 0 };
	double p8[] = { 3, 2, 0 };
	double r4[] = { 9, 6 };
	assertProd(p7, 4, p8, 3, r4);

	double p9[] = { 1, -1 };
	double p10[] = { 1, 1 };
	double r5[] = { 1, 0, -1 };
	assertProd(p9, 2, p10, 2, r5);

	_getch();
}