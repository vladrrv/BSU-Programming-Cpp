#define _USE_MATH_DEFINES
#include <math.h>
#include <conio.h>
#include <iostream>
using namespace std;

double specPi(double e)
{
	double sum = 0, t = 1;
	int n = 1;
	while (abs(t) > e/10)
	{
		t = 4*((n % 2 == 0) ? (-1.0) : 1.0) / (2 * (n - 1) + 1);
		n++;
		sum += t;
	}
	return sum;
}

void assert(double e)
{
	cout << "Value of pi with accuracy of " << e << " : " << specPi(e) << endl;
	if (M_PI - specPi(e) < e)
		cout << "Correct\n\n";
	else
		cout << "Incorrect\n\n" << endl << endl;
}

void main()
{
	printf("Value of pi from math library: %.10lf \n", M_PI);
	cout << "-------------------------------" << endl;
	assert(0.1);
	assert(0.01);
	assert(0.001);
	assert(0.0001);
	assert(0.00001);
	_getch();
}