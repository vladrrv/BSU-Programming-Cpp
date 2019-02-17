#include <conio.h>
#include <iostream>
#include <string>
#include <ctime>
#include "SingleLList.h"
using namespace std;

void generateRandomContent(SingleLList<int>& c, unsigned how_many)
{
	for (auto i = 0; i < how_many; i++)
		c.push_back(rand() % 100);
}

int main()
{
	srand(time(NULL));
	SingleLList<int> arr;
	SingleLList<string> arrstr;
	generateRandomContent(arr, 16);
	arr.display();
	cout << "\n\nPop first 3 elements:\n";
	cout << arr.pop_back() << endl;
	cout << arr.pop_back() << endl;
	cout << arr.pop_back() << endl;
	arr.delete_pos(1);
	cout << *arr.end();
	cout << "\nShow another element using iterator:\n";
	SingleLList<int>::_iter it = arr.begin();
	cout << *(++it) << endl;
	arr.sort();
	cout << "\nSorted";
	arr.display();

	arrstr.push_back(string("here"));
	arrstr.push_back(string("words"));
	arrstr.push_back(string("some"));
	arrstr.display();
	arrstr.delete_pos(1);
	arrstr.display();
	arrstr.reverse();
	arrstr.display();
	_getch();
}
