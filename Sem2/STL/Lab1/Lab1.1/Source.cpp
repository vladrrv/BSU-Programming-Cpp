#include <conio.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	vector<char> vct;
	cout << "Enter how many letters to generate: ";
	int sz;
	cin >> sz;
	srand(time(NULL));
	for (int i = 0; i < sz; i++)
		vct.push_back(rand() % 26 + 'a');

	sort(vct.begin(), vct.end());
	cout << "\nVector straight order:\n" ;
	for (vector<char>::iterator i = vct.begin(); i != vct.end(); i++)
		cout << *i << " ";

	cout << "\nVector reverse order:\n";
	reverse(vct.begin(), vct.end());
	for (vector<char>::iterator i = vct.begin(); i != vct.end(); i++)
		cout << *i << " ";

	_getch();
}