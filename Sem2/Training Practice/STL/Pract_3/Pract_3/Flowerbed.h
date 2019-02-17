#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;


class Flowerbed
{
	int num;
	string shape;
	vector<string> flowers;
public:
	Flowerbed()
	{
		num = 0;
		shape = "No_info";
	}
	Flowerbed(const Flowerbed &st)
	{
		num = st.num;
		shape = st.shape;
		flowers = st.flowers;
	}
	Flowerbed(int n, string f, vector<string> m)
	{
		num = n;
		shape = f;
		flowers = m;
	}
	int get_num() const;
	string get_shape() const;
	vector<string> get_flowers() const;
	void info(ostream&);
	friend bool operator<(const Flowerbed&, const Flowerbed&);
	bool operator==(const Flowerbed&);
	friend istream& operator >> (istream&, Flowerbed&);
	friend ostream& operator << (ostream&, const Flowerbed&);

};

int Flowerbed::get_num() const
{
	return num;
}

string Flowerbed::get_shape() const
{
	return shape;
}

vector<string> Flowerbed::get_flowers() const
{
	return flowers;
}

void Flowerbed::info(ostream& o)
{
	o << "Number: " << num << "\tShape: " << shape << "\tFlowers: ";
	vector<string>::iterator iter;
	for (iter = flowers.begin(); iter != flowers.end(); iter++)
		o << *iter << " ";
	o << endl;
}

bool operator<(const Flowerbed& s1, const Flowerbed& s2)
{
	return s1.get_shape() < s2.get_shape();
};

bool Flowerbed::operator==(const Flowerbed& s1)
{
	return get_shape() == s1.get_shape();
};

istream& operator >> (istream& str, Flowerbed& o)
{
	str >> o.num >> o.shape;
	string b = "";
	getline(str, b);
	stringstream buf(b);
	o.flowers.clear();
	istream_iterator<string> eos;
	for (istream_iterator<string> iit(buf); iit != eos; iit++)
		o.flowers.push_back(*iit);
	return str;
}

ostream& operator << (ostream& str, const Flowerbed& o)
{
	str << endl << "|" << setw(3) << right << o.num << " |" << setw(13) << left << o.shape << "| " << right;
	ostream_iterator<string> it(str, ", ");
	copy(o.flowers.begin(), o.flowers.end(), it);
	return str;
}