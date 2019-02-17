#include <iostream>
#include <conio.h>
#include <bitset>
using namespace std;

int main()
{
	//task 1
	{
		cout << "Enter a, b (short int): ";
		short a, b, x = 0;
		cin >> a >> b;
		_asm
		{
			mov ax, a
			mov bx, b
			cmp ax, bx
			jl _val1
			je _val2
			jg _val3

			_val1 :
				mov bx, a
				mov ax, b
				inc bx
				mov dx, 0
				cwd
				idiv bx
				mov x, ax
				jmp _myexit

			_val2 :
				mov x, 4
				jmp _myexit

			_val3 :
				mov ax, a
				mov bx, b
				imul ax, a
				imul ax, a
				sub ax, 5
				mov dx, 0
				cwd
				idiv bx
				mov x, ax

			_myexit:
		}

		cout << "x = " << x;
		if (_getch() == 27) return 0;
	}
	//task 1'
	{
		cout << "\n\nEnter a, b (int): ";
		int a, b, x = 0;
		cin >> a >> b;
		_asm
		{
			mov eax, a
			mov ebx, b
			cmp eax, ebx
			jl _val1_
			je _val2_
			jg _val3_

			_val1_ :
				mov ebx, a
				mov eax, b
				inc ebx
				mov edx, 0
				cwd
				idiv ebx
				mov x, eax
				jmp _myexit_

			_val2_ :
				mov x, 4
				jmp _myexit_

			_val3_ :
				mov eax, a
				mov ebx, b
				imul eax, a
				imul eax, a
				sub eax, 5
				mov edx, 0
				cwd
				idiv ebx
				mov x, eax

			_myexit_:
		}

		cout << "x = " << x;
		if (_getch() == 27) return 0;
	}
	//task 2
	{
		cout << "\n\nEnter natural number n: ";
		unsigned short n, count = 0;
		cin >> n;
		_asm
		{
			mov bx, 10
			mov ax, n
			_loop1 :
				inc count
				mov dx, 0
				div bx
				cmp ax, 0
				jg _loop1
		}
		cout << "Digits count: " << count;
		if (_getch() == 27) return 0;
	}
	//task 3
	{
		cout << "\n\nEnter natural number n: ";
		unsigned short n, count = 0, even = 1;
		cin >> n;
		cout << "Binary representation of n: " << bitset<16>(n) ;
		_asm
		{
			mov ax, n
			_loop2 :
				shr ax, 1
				jnc _no_inc
				inc count
				_no_inc :
				cmp ax, 0
				jne _loop2
			test count, 1
			jz _myexit2
			mov even, 0
			_myexit2:
		}
		if (even == 1)
			cout << "\nEven";
		else
			cout << "\nOdd";
		cout << "\n'1's count: " << count;
		if (_getch() == 27) return 0;
	}
}