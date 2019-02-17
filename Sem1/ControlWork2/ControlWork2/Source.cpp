#include "Worker.h"
#include "EmployeeHour.h"
#include "EmployeeFix.h"
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

template <class T>
void quickSort(T *list, int left, int right)
{
	T pivot = list[(left + right) / 2];
	int
		left_arrow = left,
		right_arrow = right;
	do
	{
		while (list[right_arrow] > pivot)
			right_arrow--;
		while (list[left_arrow] < pivot)
			left_arrow++;
		if (left_arrow <= right_arrow)
		{
			swap(list[left_arrow], list[right_arrow]);
			left_arrow++;
			right_arrow--;
		}
	} while (right_arrow >= left_arrow);
	if (left < right_arrow)
		quickSort(list, left, right_arrow);
	if (left_arrow < right)
		quickSort(list, left_arrow, right);
}

template<class T>
class Employee
{
	T person[256];
	int count;
public:
	Employee()
	{
		count = 0;
	}
	void add(const T& a)
	{
		person[count++] = a;
	}

	void remove()
	{
		person[count--] = 0;
	}
	void showInf(int i)
	{
		person[i].printAll();
	}
};

void main()
{
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	int num = 0;
	infile >> num;
	EmployeeFix *group = new EmployeeFix[num];

	int id = 0;
	double salary = 0;
	char name[256] = "";
	for (int i = 0; i < num; i++)
	{
		infile >> id;
		infile >> name;
		infile >> salary;
		group[i] = EmployeeFix(id, name, salary);
	}

	quickSort(group, 0, 9);
	for (int i = 0; i < 5; i++)
	{
		cout << endl;
		outfile << endl;
		group[i].printName();
		group[i].printName(outfile);
	}
	for (int i = 0; i < 3; i++)
	{
		cout << endl;
		outfile << endl;
		group[9 - i].printID();
		group[9 - i].printID(outfile);
	}
	//////////////////
	Employee<EmployeeFix> x;
	Employee<EmployeeHour> y;
	x.add(EmployeeFix(12, "Carl", 5600));
	x.add(EmployeeFix(10, "Max", 4600));
	y.add(EmployeeHour(12, "John", 1600));
	y.showInf(0);
	_getch();
}
	