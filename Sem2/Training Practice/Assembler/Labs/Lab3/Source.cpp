#include <iostream>
#include <iomanip>
#include <conio.h>
using namespace std;

const int N = 4;
void print_matrix(int (*a)[N])
{
	for (int i = 0; i < N; i++)
	{
		cout << endl;
		for (int j = 0; j < N; j++)
			cout << "+---";
		cout << "+\n|";
		for (int j = 0; j < N; j++)
			cout << setw(3) << a[i][j] << "|";
	}
	cout << endl;
	for (int j = 0; j < N; j++)
		cout << "+---";
	cout << "+";
}

int main()
{
	//task 1
	{
		int a[N][N] = 
		{
			{  1,  2,  3,  4},
			{  5,  6,  7,  8},
			{  9, 10, 11, 12},
			{ 13, 14, 15, 16}
		};
		cout << "\nSource matrix:";
		print_matrix(a);
		int i;
		cin >> i;
		_asm
		{
			mov edi, i
			mov esi, i
			imul esi, N
			mov ecx, N
		_loop1 :
			mov eax, a[esi*4]
			mov ebx, a[edi*4]

			mov a[esi*4], ebx
			mov a[edi*4], eax

			inc esi
			add edi, N
			loop _loop1
		}
		cout << "\nResult matrix:";
		print_matrix(a);
		_getch();
	}

	//task 2
	{
		int seq[] = { 1,4,3,3,4,1 }, len = 6, pal = 1;
		_asm
		{
			mov ecx, len
			shr ecx, 1
			cmp ecx, 0
			je _end
			mov esi, 0
			mov edi, len
			dec edi

		_loop2 :
			mov eax, seq[esi*4]
			cmp eax, seq[edi*4]
			jne _break
			inc esi
			dec edi
			loop _loop2
			jmp _end
		_break :
			mov pal, 0
		_end :
		}
		if (pal == 1)
			cout << "\n\nPalindrome";
		else
			cout << "\n\nNot a palindrome";

		_getch();
	}

	//task 3
	{
		int arr[] = { 5,0,4,0,5,0 }, len = 6, unq = 1, most_freq = 0, mf_val;
		_asm
		{
			mov edx, len
			dec edx
			jz _one_el_arr
		_loop4 :

			mov ecx, edx
			mov esi, 0
			mov edi, 1

		_loop3 :

			mov eax, arr[esi*4]
			mov ebx, arr[edi*4]
			cmp eax, ebx
			jg _swap
			_cont :
			inc esi
			inc edi

			dec ecx
			cmp ecx, 0
			jg _loop3

		dec edx
		cmp edx, 0
		jg _loop4

			jmp _sort_end
		_swap :
			mov arr[esi*4], ebx
			mov arr[edi*4], eax
			jmp _cont

		_sort_end :
			mov edx, 1
			mov esi, 0
			mov edi, 1
			mov ecx, len
			dec ecx
		_unique :
			mov eax, arr[esi*4]
			cmp eax, arr[edi*4]
			je _freq
			inc unq
			mov edx, 1
			_ret1 :
			cmp edx, most_freq
			jg _setmax
			_ret2 :
			inc edi
			inc esi
			dec ecx
			cmp ecx, 0
			jg _unique
			jmp _end2
		_freq :
			inc edx
			jmp _ret1

		_setmax :
			mov most_freq, edx
			mov mf_val, eax
			jmp _ret2


		_one_el_arr :
			mov unq, 1
			mov most_freq, 1
			mov eax, arr[0]
			mov mf_val, eax

		_end2 :

		}
		cout << "\n\nNumber of different elements: " << unq;
		cout << "\nMost frequent value: " << mf_val << ", appears " << most_freq << " times";

		_getch();
	}
}