#include <iostream>
#include <conio.h>
#include "CNumber.h"
using namespace std;

void cmpByMod(const CNumber &z1, const CNumber &z2)
{
	if (z1 > z2)
		cout << "\nFirst operand is bigger\n";
	else if (z1 < z2)
		cout << "\nSecond operand is bigger\n";
	else if (z1 == z2)
		cout << "\nThey are equal\n";
}

void main()
{
	int n;
	cout << "How many complex numbers do you wanna test? ";
	cin >> n;
	CNumber *arr = new CNumber[n];
	cout << "Now enter these numbers one by one (just type real and imaginary parts separated by space):\n";
	double re, im;
	for (int i = 0; i < n; i++)
	{
		cout << "z" << i << ": ";
		cin >> re >> im;
		arr[i] = CNumber(re, im);
	}
	cout << "\nTest'em!";
	int i, j; char op;
	CNumber res;
	while (_getch() != 27)
	{
		cout << "\nFirst operand: z";
		cin >> i;
		cout << "Second operand: z";
		cin >> j;
		if (i >= n || j >= n || i < 0 || j < 0) continue;
		cout << "Operation: ";
		cin >> op;
		switch (op)
		{
		case '+': res = arr[i] + arr[j]; break;
		case '-': res = arr[i] - arr[j]; break;
		case '*': res = arr[i] * arr[j]; break;
		case '/': res = arr[i] / arr[j]; break;
		default: cout << "Incorrect operation!\n"; continue;
		}
		arr[i].printDot();
		cout << " " << op << " ";
		arr[j].printDot();
		cout << " = ";
		res.printDot();
		cout << "\nModular comparsion:";
		cmpByMod(arr[i], arr[j]);
		cout << "--------------------------\n";
	}
}