#include <iostream>
using namespace std;
#include <math.h>
#include <conio.h>

int main()
{
	unsigned int num;

	cout << "Enter a natural number:" << endl;
	cin >> num;

	if (num > 1)
	{
		bool flag = true;

		for (int i = 2; (i <= sqrt((double)num)); i++)
		{
			if (num % i == 0)
			{
				flag = false;
				break;
			}
		}

		if (flag)
			cout << "The number is prime" << endl;
		else
			cout << "The number is composite" << endl;
	}
	else
		if (num == 1)
			cout << "1 is not a prime number and not composite." << endl;
		else
			cout << "You entered not a natural number! (zero)" << endl;
	_getch();
	return 0;
}