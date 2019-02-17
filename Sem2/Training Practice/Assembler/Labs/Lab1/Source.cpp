#include <iostream>
#include <conio.h>
using namespace std;

int main()
{
	{
		//cout << "Enter a, b: ";
		short m = 3, n = 5;
		//cin >> a >> b;
		cout << "\nm = " << m << ", n = " << n;
		_asm
		{
			mov ax, m
			mov bx, n
			mov m, bx
			mov n, ax
		}
		cout << "\nm = " << m << ", n = " << n;

		_getch();
	}
	{
		short a = -13, b = -12, x, r;

		cout << "\n\n" << a << "x" << ((b > 0) ? " + " : (b < 0) ? " - " : "") << abs(b) << " = 0";
		_asm
		{
			mov dx, 0
			mov bx, a
			mov ax, b
			mov cx, 0
			sub cx, ax
			mov ax, cx
			cwd
			idiv bx
			mov r, dx
			mov x, ax
		}
		cout << "\nx = " << ((float)x + (float)r / a);
		_getch();
	}
	{
		short s = 3, x = 2, z = 4, quotient, remainder, dividend, divisor;
		cout << "\n\ns = " << s << "\nx = " << x << "\nz = " << z;
		cout << "\n" << s << "*(" << x << " - " << s << "*" << z << ")/(" << s << " + " << x << "*" << z << ") = ";
		_asm
		{
			mov ax, s
			imul ax, z
			mov bx, x
			sub bx, ax
			imul bx, s
			mov dividend, bx

			mov ax, x
			imul ax, z
			mov bx, s
			add bx, ax
			mov divisor, bx

			mov dx, 0
			mov ax, dividend
			cwd
			idiv bx
			mov remainder, dx
			mov quotient, ax
		}
		cout << ((float)quotient + (float)remainder / divisor); 
	}
	_getch();
}