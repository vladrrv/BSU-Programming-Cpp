#include <iostream>
#include <conio.h>
#include "Str.h"
using namespace std;

template <class T>
void quickSort(T **list, int left, int right)
{
	T pivot = *list[(left + right) / 2];
	int 
		left_arrow = left, 
		right_arrow = right;
	do
	{
		while (*list[right_arrow] > pivot)
			right_arrow--;
		while (*list[left_arrow] < pivot)
			left_arrow++;
		if (left_arrow <= right_arrow)
		{
			swap(list[left_arrow], list[right_arrow]);
			left_arrow++;
			right_arrow--;
		}
	} while (right_arrow >= left_arrow);
	if (left < right_arrow)
		quickSort(list, left, right_arrow);
	if (left_arrow < right)
		quickSort(list, left_arrow, right);
}

void main()
{
	const unsigned int ARR_SIZE = 10;
	Str *arr[ARR_SIZE] =
	{
		new StrDigits("123456"),
		new Str("hat's written "),
		new Str("rything"),
		new Str("here then eve"),
		new StrDigits(4533091),
		new StrDigits(4536),
		new Str("'s ok"),
		new Str("."),
		new StrDigits("523094"),
		new Str("If you understand w")
	};
	Str *arr_str[ARR_SIZE];
	StrDigits *arr_strdig[ARR_SIZE];
	for (int i = 0; i < ARR_SIZE; i++)
	{
		arr_str[i] = new Str;
		arr_strdig[i] = new StrDigits;
	}
	int
		str_count = 0,
		strdig_count = 0;

	cout << "This's mixed array of objects of both classes - Str & StrDigits: ";
	for (int i = 0; i < ARR_SIZE; i++)
	{
		if (!strcmp(typeid(*arr[i]).name(), "class Str"))
			arr_str[str_count++] = new Str(*arr[i]);
		else
			arr_strdig[strdig_count++] = new StrDigits(*dynamic_cast<StrDigits*>(arr[i]));
		arr[i]->print();
	}

	cout << "\n\nHere's array of 'Str' class objects, sorted by length: ";
	quickSort(arr_str, 0, str_count - 1);
	Str concat;
	for (int i = 0; i < str_count; i++)
	{
		arr_str[i]->print();
		concat += *arr_str[str_count - 1 - i];
	}
	cout << "\nLet's concatenate them in reverse order: ";
	concat.print();

	cout << "\n\nHere's array of 'StrDigits' class objects, sorted by numeric value: ";
	quickSort(arr_strdig, 0, strdig_count - 1);
	StrDigits s(0);
	for (int i = 0; i < strdig_count; i++)
	{
		arr_strdig[i]->print();
		s += *arr_strdig[i];
	}
	cout << "\nAnd their sum is: ";
	s.print();

	for (int i = 0; i < ARR_SIZE; i++)
	{
		delete arr[i];
		delete arr_str[i];
		delete arr_strdig[i];
	}
	_getch();
}