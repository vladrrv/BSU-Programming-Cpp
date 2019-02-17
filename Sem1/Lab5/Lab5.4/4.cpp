#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;
/*

*/

struct List
{
	int value;
	List *next;
	List *prev;
};

void add(int val, List *&head)
{
	List *newItem = new List;
	newItem->next = NULL;
	newItem->prev = head;
	if (head != NULL)
		head->next = newItem;
	newItem->value = val;
	head = newItem;
}

void move(List *&item, List *&head)
{
	if (item->next != NULL)
		(item->next)->prev = item->prev;
	if (item->prev != NULL)
		(item->prev)->next = item->next;
	add(item->value, head);
	item = head;
}

void main()
{
	List *head = new List;
	List *cur = new List;
	head = NULL;
	int n = 0, m = 0, i = 0;

	int n = 0, m = 0, req[65535];
	ifstream infile;
	ofstream outfile;
	infile.open("input.txt");
	outfile.open("output.txt");

	infile >> n;
	infile >> m;
	for (int i = 0; i < m; ++i)
		infile >> req[i];

	for (int i = n; i > 0; i--)
		add(i, head);
	cur = head;

	for (int l = 0; l < m; l++)
	{
		int k = 1;
		while (cur->value != req[l] && cur->prev != NULL)
		{
			cur = cur->prev;
			k++;
		}
		if (cur->value == req[l])
		{
			//cout << "Found!\n";
			//cout << "Number of viewed records: " << k << endl;
			outfile << k << " ";
			if (k > 1)
				move(cur, head);
		}
		else
		{
			//cout << "Not found!\n";
			cur = head;
		}
	}
	outfile.close();
	_getch();
}