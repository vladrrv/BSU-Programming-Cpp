#include "Route.h"
#include <iostream>
using namespace std;

Route::Route(unsigned n, string nm, unsigned bn, string bb)
{
	num = n;
	name = nm;
	busnum = bn;
	busbrand = bb;
}

Route::Route(const Route& o)
{
	num = o.num;
	name = o.name;
	busnum = o.busnum;
	busbrand = o.busbrand;
}
void Route::updateDriver(string nm)
{
	name = nm;
}
void Route::displayInfo() const
{
	cout << endl << "|" << setw(4) << right << num << "|" << setw(15) << right << name;
	cout << " |" << setw(5) << right << busnum << "| " << setw(12) << left << busbrand << right << "|";
}

bool Route::operator < (const Route& o) const
{
	return num < o.num;
}
bool Route::operator > (const Route& o) const
{
	return num > o.num;
}

string Route::Name() const
{
	return name;
}
unsigned Route::Num() const
{
	return num;
}
unsigned Route::BusNum() const
{
	return busnum;
}
string Route::BusBrand() const
{
	return busbrand;
}

istream& operator >> (istream& str, Route& o)
{
	string name = "";
	unsigned num = 0;
	unsigned busnum = 0;
	string busbrand = "";
	try
	{
		str >> num >> name >> busnum >> busbrand;
		o = Route(num, name, busnum, busbrand);
	}
	catch (const exception&)
	{
		cerr << "\nSomething's wrong with input stream!";
	}
	return str;
}