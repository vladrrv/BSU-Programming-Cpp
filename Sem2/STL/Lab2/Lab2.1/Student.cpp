#include <numeric>
#include "Student.h"
using namespace std;

Student::Student(string nm, unsigned gr, vector<unsigned> m)
{
	name = nm;
	group = gr;
	marks = m;
}
Student::Student(const Student& o)
{
	name = o.name;
	group = o.group;
	marks = o.marks;
}
void Student::displayInfo() const
{
	cout << endl << "| " << setw(15) << left << name << "|" << setw(8) << right << group << " |";
	for each (unsigned m in marks)
		cout << setw(3) << right << m;
	cout << setw(2) << right << "|";
}
bool Student::operator < (const Student& o) const
{
	return markSum() < o.markSum();
}
bool Student::operator > (const Student& o) const
{
	return markSum() > o.markSum();
}
unsigned Student::markSum() const
{
	return accumulate(marks.begin(), marks.end(), 0);
}
string Student::Name() const
{
	return name;
}
vector<unsigned> Student::Marks() const
{
	return marks;
}
unsigned Student::lowestMark() const
{
	unsigned minMark = 10;
	for each (unsigned m in marks)
		if (m < minMark)
			minMark = m;
	return minMark;
}
unsigned Student::Group() const
{
	return group;
}

istream& operator >> (istream& str, Student& o)
{
	string name = "";
	unsigned group = 0;
	vector<unsigned> marks;
	unsigned m;
	try
	{
		str >> name >> group;
		marks.clear();
		for (unsigned i = 0; i < MK_NUM; i++)
		{
			str >> m;
			marks.push_back(m);
		}
		o = Student(name, group, marks);
	}
	catch (const exception&)
	{
		cerr << "\nSomething's wrong with input stream!";
	}
	return str;
}