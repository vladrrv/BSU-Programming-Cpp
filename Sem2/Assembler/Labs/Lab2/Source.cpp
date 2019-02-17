#include <iostream>
#include <conio.h>
using namespace std;

int main()
{
	//task 4
	{
		cout << "Enter natural number n: ";
		unsigned short n, sum = 0;
		cin >> n;
		_asm
		{
			mov bx, 10
			mov ax, n
			_loop1:
				mov dx, 0
				div bx
				add sum, dx
				cmp ax,0
				ja _loop1
		}
		cout << "\nDigits sum is: " << sum;
		_getch();
	}
	//task 6
	{
		cout << "Enter natural number n: ";
		unsigned short n, count = 0;
		cin >> n;
		_asm
		{
			mov ax, n
			_loop2:
				inc count
				shr ax, 1
				jnz _loop2
		}
		cout << "\nSignificant digits count: " << count;
		_getch();
	}
}