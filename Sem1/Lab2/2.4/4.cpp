#include <math.h>
#include <conio.h>
#include <iostream>
using namespace std;

void main()
{
	int lastDigit = 1, n;
	cout << "Enter natural number N that is less or equal to 9999" << endl;
	cin >> n;
	if (n <= 9999)
	{
		for (int i = 1; i <= n; i++)
		{
			lastDigit *= i;
			while (lastDigit % 10 == 0)
			{
				lastDigit /= 10;
			}
			if (!((lastDigit * (i + 1)) % 10 == 0))				//(!(lastDigit % 2 == 0 && (i + 1) % 5 == 0))
				lastDigit %= 10;
		}
		lastDigit %= 10;
		cout << "Last non-zero digit of " << n << "! is " << lastDigit << endl;
	}
	else
		cout <<  n << " is greater than 9999!";
	_getch();
}