#include <iostream>
using namespace std;
#include <math.h>
#include <conio.h>

int main()
{
	unsigned int num;
	int digits[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	int length = 9;
	cout << "Enter a natural number: ";
	cin >> num;

	if (num > 0)
	{

		int k = 8;
		for (int i = 1; (i < 10); i++)
		{
			digits[k--] = (num % 10);
			num /= 10;
			if (num == 0)
			{
				length = i;
				break;
			}
		}
/*
		for (int i = 0; (i < 9); i++)
		{
			cout << digits[i];
		}
*/
		int diffDigits = length;
		for (int l = 9 - length; (l < 9); l++)
			for (int i = l + 1; (i < 9); i++)
				if (digits[i] == digits[l])
				{
					diffDigits--;
					break;
				}
		cout << "Totally " << diffDigits << " different digits in the number." << endl;
	}
	else
		cout << "The entered number is not natural!" << endl;


	_getch();
	return 0;
}