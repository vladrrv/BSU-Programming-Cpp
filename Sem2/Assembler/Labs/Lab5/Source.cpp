#include <iostream>
#include <iomanip>
#include <conio.h>
using namespace std;

extern "C" int _cdecl task1(int* arr, int sz);
extern "C" int _cdecl task2(int* arr, int sz);
extern "C" int _cdecl task3(int* arr, int sz);
extern "C" int _cdecl task4(int* arr, int sz);
extern "C" int _cdecl task5(int* arr, int sz);

int main()
{
	int a1[] = { 0,7,1,5,4,6,8 };
	int sz_1 = 7, index;

	index = task1(a1, sz_1);
	for (int i = 0; i < sz_1; i++)
		cout << a1[i] << " ";
	if (index >= 0)
		cout << "\nElement at index: " << index;
	else
		cout << "\nNo such element";


	cout << "\n\n--------------------\n";
	int a2[] = { 0,7,1,5,4,6,8 };
	int sz_2 = 7;
	index = task2(a2, sz_2);
	for (int i = 0; i < sz_2; i++)
		cout << a2[i] << " ";
	if (index >= 0)
		cout << "\nElement at index: " << index;
	else
		cout << "\nNo such element";


	cout << "\n\n--------------------\n";
	int a3[] = { 0,7,1,5,4,6,8 };
	int sz_3 = 7;
	index = task3(a3, sz_3);
	double sum = 0;
	for (int i = 0; i < sz_3; i++)
	{
		cout << a3[i] << " ";
		sum += a3[i];
	}
	if (index >= 0)
		cout << "\nAverage: " << (sum / sz_3) << ". Closest element at index: " << index;
	else
		cout << "\nNo such element";


	cout << "\n\n--------------------\n";
	int a4[] = { 0,7,1,5,4,6,8 };
	int sz_4 = 7;
	index = task4(a4, sz_4);
	for (int i = 0; i < sz_4; i++)
		cout << a4[i] << " ";
	if (index >= 0)
		cout << "\nMost frequent element at index: " << index;
	else
		cout << "\nNo such element";


	cout << "\n\n--------------------\n";
	int a5[] = { 120,741,101,50,43,61,11 };
	int sz_5 = 7;
	index = task5(a5, sz_5);
	for (int i = 0; i < sz_5; i++)
		cout << a5[i] << " ";
	if (index >= 0)
		cout << "\nElement with min. digit sum at index: " << index;
	else
		cout << "\nNo such element";

	_getch();
}