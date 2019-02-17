#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

void generateRandomWords(int how_many)
{
	ofstream file("input.txt");
	for (int i = 0; i < how_many; i++)
	{
		file << ' ';
		for (int j = 0; j < rand() % 10 + 1; j++)
			file << static_cast<char>('a' + rand() % 26);
	}
}

int main()
{
	srand(time(NULL));
	generateRandomWords(rand() % 90 + 10);
	list<string> lst;
	ifstream infile("input.txt");
	string word;

	while (!infile.eof())
	{
		infile >> word;
		lst.push_back(word);
	}

	lst.sort();
	cout << "\nSorted list:\n";
	for each (string w in lst)
		cout << w << " ";

	char let = 0;
	cout << "\n\nEnter a letter: ";
	cin >> let;
	cout << "\nHere are the words beginning with '" << let << "':\n";
	for each (string w in lst)
		if (w[0] == let)
			cout << w << " ";

	cout << "\n\nEnter a letter: ";
	cin >> let;
	list<string>::iterator p1 = find_if(lst.begin(), lst.end(), [=](string w) { return w[0] == let; });
	list<string>::iterator p2 = find_if(p1, lst.end(), [=](string w) { return w[0] != let; });
	lst.erase(p1, p2);
	cout << "\nList after removing the words beginning with '" << let << "':\n";
	for each (string w in lst)
		cout << w << " ";
	
	infile.close();
	_getch();
}