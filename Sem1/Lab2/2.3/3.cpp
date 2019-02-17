#include <math.h>
#include <conio.h>
#include <iostream>
using namespace std;
int zerosInFactorial(int n)
{
	int count = 0;
	for (int i = 5; i <= n; i += 5)
	{
		int temp = i;
		while (temp % 5 == 0)
		{
			count++;
			temp /= 5;
		}
	}
	return count;
}

void assert(int n, int zeroCount)
{
	cout << "Zero count in " << n << "! : " << zerosInFactorial(n) << endl;
	if (zerosInFactorial(n) == zeroCount)
		cout << "Correct\n\n";
	else
		cout << "Incorrect\n\n";
}

void main()
{
	assert(5, 1);
	assert(10, 2);
	assert(15, 3);
	assert(20, 4);
	assert(25, 6);
	_getch();
}