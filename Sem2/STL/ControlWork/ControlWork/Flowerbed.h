#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

const unsigned MK_NUM = 4;

class Flowerbed
{
	unsigned num;
	string shape;
	vector<string> flowers;
public:
	Flowerbed(unsigned n = 0, string s = "NoShape");
	Flowerbed(const Flowerbed&);
	void displayInfo() const;
	unsigned Num() const;
	string Shape() const;
	vector<string> Flowers() const;

	bool operator < (const Flowerbed&) const;
	bool operator > (const Flowerbed&) const;
	friend istream& operator >> (istream&, Flowerbed&);
	friend ostream& operator << (ostream&, const Flowerbed&);
};
