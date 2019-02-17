#include <iostream>
#include <fstream>
#include <conio.h>
#include "IntSet.h"
using namespace std;

void main()
{
	ifstream infile;
	ofstream outfile;
	infile.open("input.txt");
	outfile.open("output.txt");
	int testNum;
	infile >> testNum;
	for (int i = 0; i < testNum; i++)
	{
		IntSet a, b;
		int size1, size2;
		infile >> size1 >> size2;
		for (int j = 0; j < size1; j++)
		{
			int n;
			infile >> n;
			a.put(n);
		}
		char action;
		infile >> action;
		for (int j = 0; j < size2; j++)
		{
			int n;
			infile >> n;
			b.put(n);
		}
		IntSet res;
		switch (action)
		{
		case '&': 
			outfile << "{ ";
			a.print(outfile);
			outfile << "} & { ";
			b.print(outfile);
			outfile << "} = { ";
			res = a.intersect(b);
			res.print();
			res.print(outfile);
			outfile << "}\n";
			break;
		case 'b':
			outfile << "{ ";
			a.print(outfile);
			if (a.belongsTo(b))
				outfile << "} belongs to { ";
			else
				outfile << "} doesn't belong to { ";
			b.print(outfile);
			outfile << "}\n";
			cout << boolalpha << a.belongsTo(b);
			break;
		default:
			break;
		}
		cout << endl;
	}
	infile.close();
	outfile.close();
	_getch();
}