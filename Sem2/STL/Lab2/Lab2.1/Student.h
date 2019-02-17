#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

const unsigned MK_NUM = 4;

class Student
{
	string name;
	unsigned group;
	vector<unsigned> marks;
public:
	Student(string nm = "Noname", unsigned gr = 0, vector<unsigned> m = vector<unsigned>(MK_NUM, 0));
	Student(const Student&);
	void displayInfo() const;
	bool operator < (const Student&) const;
	bool operator > (const Student&) const;
	friend istream& operator >> (istream&, Student&);
	unsigned markSum() const;
	string Name() const;
	vector<unsigned> Marks() const;
	unsigned Group() const;
	unsigned lowestMark() const;
};