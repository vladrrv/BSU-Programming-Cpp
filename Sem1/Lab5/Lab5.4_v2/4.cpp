#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;

struct Tree
{
	int value;
	int index;
	Tree *right;
	Tree *left;
};

void main()
{
	int n = 0, m = 0, req[65535];
	ifstream infile;
	ofstream outfile;
	infile.open("input.txt");
	outfile.open("output.txt");
	infile >> n >> m;

	for (int i = 0; i < m; ++i)
		infile >> req[i];

	int *list = new int[n];

	for (int i = 1; i <= n; i++)
		list[i] = i;
	int i = 0, o = 0;
	for (int l = 0; l < m; l++)
	{
		outfile << list[req[l]] << " ";
		for (i = 0; (i < n && list[req[l]] > 1) && o < list[req[l]]; i++)
			if (list[i] < list[req[l]])
			{
				list[i]++;
				o++;
			}
		list[req[l]] = 1; o = 0;
	}
	infile.close();
	outfile.close();
	_getch();
}