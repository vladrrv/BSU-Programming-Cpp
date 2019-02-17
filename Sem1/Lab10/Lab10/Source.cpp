#include "MyVector.h"
#include <conio.h>
#include <iostream>
#include <string>
using namespace std;

void main()
{
	cout << "------------Int vector--------------";
	MyVector<int> test0(5, 0), test1(3, 14);
	cout << "\nVector0: " << test0;
	cout << "\nVector1: " << test1;
	test0 = test1;
	cout << "\nVector0, equalized to vector1: " << test0;

	cout << "\n\n------------Double vector--------------";
	double arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	MyVector<double> test(arr, arr + 7);
	cout << "\nSource vector: " << test;
	test.at(2) += 8.5;
	test[1] = 10.3;
	cout << "\nModified 1st and 2nd elements: " << test;
	cout << "\nPopped last element: " << test.pop_back();
	test.push_back(1.5);
	cout << "\nAdded 1.5 to end: " << test;

	cout << "\n\n-------------Char vector-------------";
	MyVector<char> ch_test;
	if (ch_test.empty())
		cout << "\nChar vector is empty!";
	else
		cout << "\nChar vector isn't empty!";
	for (int i = 0; i < 10; i++)
		ch_test.push_back('q');
	cout << "\nAdded 10 'q's: " << ch_test;
	ch_test.insert('u', 1);
	*(ch_test.begin() + 5) = 'A';
	cout << "\nInserted 'u' and changed 5th element to 'A': " << ch_test;

	cout << "\n\n-------------Char* vector-------------";
	MyVector<char*> ch_arr;
	for (int i = 0; i < 5; i++)
		ch_arr.push_back("hi");
	cout << "\nAdded 5 'hi's: " << ch_arr;
	ch_arr.insert("hello", 3);
	*(ch_arr.end() - 1) = "oo";
	cout << "\nInserted 'hello' and changed last element to 'oo': " << ch_arr;

	//Not working properly (problems with memory cleansing)
	/* 
	cout << "\n--------------------------";
	string s_arr[] = { "this", "is", "a", "string" };
	MyVector<string> str_test(s_arr, s_arr + 4);
	cout << "\nString vector: " << str_test;
	str_test.clear();
	str_test.push_back(string("New string"));
	cout << "\nString vector: " << str_test;
	*/
	_getch();
}