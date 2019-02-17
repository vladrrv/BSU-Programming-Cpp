#include "Fisherman.h"
using namespace std;


Fisherman::Fisherman(string n, multiset<string> h)
{
	name = n;
	haul = h;
}

Fisherman::Fisherman(const Fisherman & o) : Fisherman(o.name, o.haul)
{ }

string Fisherman::Name() const
{
	return name;
}
multiset<string> Fisherman::Haul() const
{
	return haul;
}
void Fisherman::displayInfo() const
{
	cout << endl << "|" << setw(15) << right << name << setw(3) << "| ";

	//cout << " |" << setw(5) << right << "|";
}
void Fisherman::displayInfo(ofstream& o) const
{
	o << endl << "|" << setw(15) << right << name << setw(3) << "| ";
}
bool Fisherman::operator < (const Fisherman& o) const
{
	return name < name;
}
bool Fisherman::operator > (const Fisherman& o) const
{
	return name > o.name;
}
bool Fisherman::operator == (const Fisherman& o) const
{
	return name == o.name;
}
istream& operator >> (istream& str, Fisherman& o)
{
	multiset<string> h;
	try
	{
		str >> o.name;
		string b = "", item;
		getline(str, b);
		stringstream buf(b);
		while (buf >> item)
			h.insert(item);
		o.haul = h;
	}
	catch (const exception&)
	{
		cerr << "\nSomething's wrong with input stream!";
	}
	return str;
}
