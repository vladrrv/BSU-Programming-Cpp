#pragma once
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Route
{
	unsigned num;
	string name;
	unsigned busnum;
	string busbrand;
public:
	Route(unsigned n = 0, string nm = "Undefined", unsigned b = 0, string bb = "Undefined");
	Route(const Route&);
	void updateDriver(string);
	void displayInfo() const;
	bool operator < (const Route&) const;
	bool operator > (const Route&) const;
	friend istream& operator >> (istream&, Route&);
	string Name() const;
	unsigned Num() const;
	unsigned BusNum() const;
	string BusBrand() const;
};
