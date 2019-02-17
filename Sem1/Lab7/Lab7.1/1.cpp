#include <iostream>
#include <conio.h>
#include "Student.h"
using namespace std;

void main()
{
	int 
		m1[] = { 8, 9, 7, 6 },
		m2[] = { 10, 8, 7, 6, 5 };

	Student *arr[6] = 
	{
		new Student("AAAAA1", "aaaaa1", 1),
		new Student("AAAAA2", "aaaaa2", 2),
		new StAfterS1("BBBBB1", "bbbbb1", 1, m1),
		new StAfterS1("BBBBB2", "bbbbb2", 2, m1),
		new StAfterS2("CCCCC1", "ccccc1", 2, m1, m2),
		new StAfterS2("CCCCC2", "ccccc2", 4, m1, m2)
	};

	arr[0]->showInf();
	cout << endl;
	arr[2]->showInf();
	arr[2]->avrg();
	cout << endl;
	arr[4]->showInf();
	arr[4]->avrg();

	for (int i = 0; i < 6; i++)
	{
		delete arr[i];
	}
	_getch();
}