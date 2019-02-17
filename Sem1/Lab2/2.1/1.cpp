#include <cmath>
#include <conio.h>
#include <iostream>
using namespace std;
double specSin(double x, double e)
{
	double sum = x, t = x, n = 1;
	while (abs(t) > e)
	{
		t *= (-1) * x * x / ((2 * n + 1) * (2 * n));
		n++;
		sum += t;
	}
	return sum;
}

void assert(double x, double e)
{
	cout << "Value of sin(" << x << ") using math library: " << sin(x) << endl;
	cout << "Value of sin(" << x << ") using our algoritm: " << specSin(x, e) << " (accuracy " << e << ")" << endl;
	if (sin(x) - specSin(x, e) < e)
		cout << "Correct" << endl << endl;
	else
		cout << "Incorrect" << endl << endl;
}

void main()
{
	assert(0.49, 0.1);
	assert(3.14, 0.01);
	assert(1.5, 0.001);
	assert(10.29, 0.0001);
	_getch();
}