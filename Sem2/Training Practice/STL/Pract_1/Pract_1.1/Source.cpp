#include <iostream>
#include <conio.h>
#include "vect.h"

int main()
{
	vector<double> v(5);
	vector<double>::iterator p;
	int i = 0;
	for (p = v.begin(); p != v.end(); ++p)
		*p = 1.5 + i++;
	do {
		--p;
		cout << *p << ", ";
	} 
	while (p != v.begin());

	cout << endl;

	vectorex<int>ve(3);
	ve[0] = ve[1] = ve[2] = 123;
	cout << ve[1];
	_getch();
}
