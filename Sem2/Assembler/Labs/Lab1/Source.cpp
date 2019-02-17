#include <iostream>
#include <conio.h>
using namespace std;

int main()
{
	//task 2
	{
		cout << "Task 2\nEnter a: ";
		int a, res = 0, check = 1;
		cin >> a;
		cout << a << "^5 + " << a <<  "^3 + " << a << " = ";
		_asm
		{
			mov edx, 0
			mov eax, a
			mov ebx, a
			add res, ebx
			mov cl, 2
			_loop2:
				imul eax, ebx
				jo _break
				dec cl
				jnz _loop2
			add res, eax

			mov cl, 2
			_loop1:
				imul eax, ebx
				jo _break
				dec cl
				jnz _loop1
			add res, eax

			jmp my_exit
			_break:
				mov check, 0
			my_exit:
		}
		if (check == 1)
			cout << res;
		else
			cout << "... ";

		_getch();
	}
	//task 4
	{
		cout << "\n\nTask 4\nEnter a: ";
		short a, n = 0;
		cin >> a;

		_asm
		{
			mov cx, 0
			mov ax, a
			mov bx, a
			_loop3:
				inc n
				imul ax, bx
				jno _loop3
		}
		cout << "Maximum n that " << a << "^n is evaluated correctly is: " << n;
		_getch();
	}
}