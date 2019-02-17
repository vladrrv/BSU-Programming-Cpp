#include <iostream>
#include <conio.h>
using namespace std;

int repr(int* x, int len)
{
	int res = 0;
	for (int i = 0; i < len; i++)
		res = res * 8 + x[len - i - 1];
	return res;
}
void arr_out(int* arr, int len)
{
	cout << endl;
	for (int i = 0; i < len; i++)
		cout << arr[i] << " ";
}
int main()
{
	//task 10
	{
		int b[] = { 7,1,1,1,1,1 }, a[] = { 0,7,7,7,7,7 }, sum[] = { 0,0,0,0,0,0,0,0,0 }, dif[] = { 0,0,0,0,0,0,0,0,0 };
		int a_len = 6, b_len = 6, len_dif = a_len - b_len;
		cout << oct << "a = " << repr(a, a_len) << ", b = " << repr(b, b_len);
		_asm
		{
			mov edi, 0
			mov ecx, a_len
		_loop1 :
			mov eax, a[edi]
			mov ebx, a[edi]
			cmp ecx, len_dif
			jle _skip
			add eax, b[edi]
			sub ebx, b[edi]
		_skip :
			add dif[edi], ebx
			cmp dif[edi], 0
			jnl _ok1
			add dif[edi], 8
			dec dif[edi+4] 
		_ok1 :
			add sum[edi], eax
			cmp sum[edi], 8
			jl _ok2
			sub sum[edi], 8
			inc sum[edi+4]
		_ok2 :
			add edi, 4
			loop _loop1
		}
		cout << oct << "\na + b = " << repr(sum, 8) << "\na - b = " << repr(dif, 8) << dec;
		_getch();
	}
	//task 12
	{
		int a[] = { 4,5,1,2,8,5 }, b[] = { 1,2,3 }, a_len = 6, b_len = 3;
		cout << "\n\nSource array:";
		arr_out(a, a_len);
		cout << "\nArray to compare:";
		arr_out(b, b_len);
		_asm
		{
			mov edi, 0
		_loop2 :
			mov ecx, b_len
			mov esi, 0
			_cmploop :
				mov edx, a[edi*4]
				cmp edx, b[esi*4]
				jne _nodel
				dec a_len
				mov eax, edi
				_delshift :
					mov ebx, eax
					inc ebx
					mov edx, a[ebx*4]
					mov a[eax*4], edx
					dec edi
					inc eax
					cmp eax, a_len
					jl _delshift
				jmp _break
				_nodel :
					inc esi
				loop _cmploop
			_break:
			inc edi
			cmp a_len, edi
			jg _loop2

		}
		cout << "\nResult:";
		arr_out(a, a_len);
		_getch();
	}
}