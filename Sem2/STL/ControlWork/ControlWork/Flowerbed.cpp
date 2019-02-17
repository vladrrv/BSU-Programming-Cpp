#include "Flowerbed.h"

using namespace std;

Flowerbed::Flowerbed(unsigned n, string s)
{
	num = n;
	shape = s;
}
Flowerbed::Flowerbed(const Flowerbed& o)
{
	num = o.num;
	shape = o.shape;
	flowers = o.flowers;
}
unsigned Flowerbed::Num() const
{
	return num;
}
string Flowerbed::Shape() const
{
	return shape;
}
vector<string> Flowerbed::Flowers() const
{
	return flowers;
}
void Flowerbed::displayInfo() const
{
	cout << endl << "|" << setw(3) << right << num << " |" << setw(13) << left << shape << "| " << right;
	for (string f : flowers)
		cout << f << ", ";
}

bool Flowerbed::operator < (const Flowerbed& o) const
{
	return shape < o.shape;
}
bool Flowerbed::operator > (const Flowerbed& o) const
{
	return shape > o.shape;
}

istream& operator >> (istream& str, Flowerbed& o)
{
	try
	{
		str >> o.num >> o.shape;
		
		string b = "", item;
		getline(str, b);
		stringstream buf(b);
		o.flowers.clear();
		while (buf >> item)
			o.flowers.push_back(item);
	}
	catch (const exception&)
	{
		cerr << "\nSomething's wrong with input stream!";
	}
	return str;
}

ostream& operator << (ostream& str, const Flowerbed& o)
{
	str << endl << "|" << setw(3) << right << o.num << " |" << setw(13) << left << o.shape << "| " << right;
	ostream_iterator<string> it(cout, ", ");
	copy(o.flowers.begin(), o.flowers.end(), it);
	return str;
}