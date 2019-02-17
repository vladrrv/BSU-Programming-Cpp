#include <iostream>
#include <conio.h>
#include "IntStorage.h"
using namespace std;

void main()
{
	IntStorage a(513);
	a.store(0);
	a.store(10);
	a.store(514);
	a.print();
	a.remove(33);
	a.remove(0);
	a.print();
	_getch();
}