#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <set>
using namespace std;

class Fisherman
{
	string name;
	multiset<string> haul;
public:
	Fisherman(string n = "Noname", multiset<string> c = multiset<string>());
	Fisherman(const Fisherman &);
	string Name() const;
	multiset<string> Haul() const;
	void displayInfo() const;
	void displayInfo(ofstream&) const;
	bool operator < (const Fisherman& o) const;
	bool operator > (const Fisherman& o) const;
	bool operator == (const Fisherman& o) const;
	friend istream& operator >> (istream&, Fisherman&);
};