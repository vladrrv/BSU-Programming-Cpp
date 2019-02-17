#include <conio.h>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <numeric>
#include "Flowerbed.h"
using namespace std;

// My number in grouplist : 10
// 3) - 4, 6
// 4) - 3, 5
// 5) - 5, 2

/*--------------------------------------------------------------*/
/*                        DO NOT CHANGE!                        */
/* These constants are set according to the sizes of databases  */
/*--------------------------------------------------------------*/
const unsigned MAX_FLOWERS_RAND = 43;//Total species in database /
const unsigned MAX_SHAPES_RAND = 18; //Total  shapes in database /
/*--------------------------------------------------------------*/

/*-------------------------------------*/
/*          Editable constants         */
/*-------------------------------------*/
const unsigned FLOWERS_RAND = 43;
const unsigned SHAPES_RAND = 18;
const unsigned NUM_FLOWERBEDS = 20;

/*--------------------------------------------------------------*/
/*                     Random Data Generator                    */
/*--------------------------------------------------------------*/
vector<string> SHAPES;
vector<string> FLOWERS;
void createShapesVector()
{
	ifstream db("Shapes_DB.txt");
	string buf;
	db.seekg(ios::beg);
	for (unsigned i = 0; i < SHAPES_RAND; i++)
	{
		unsigned pos = rand() % (MAX_SHAPES_RAND / SHAPES_RAND);
		for (unsigned j = 0; j < pos; j++)
			db.ignore(numeric_limits<streamsize>::max(), '\n');
		db >> buf;
		SHAPES.push_back(buf);
		for (unsigned j = 0; j < MAX_SHAPES_RAND / SHAPES_RAND - pos; j++)
			db.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	db.close();
}
void createFlowersVector()
{
	ifstream db("Flowers_DB.txt");
	string buf;
	db.seekg(ios::beg);
	for (unsigned i = 0; i < FLOWERS_RAND; i++)
	{
		unsigned pos = rand() % (MAX_FLOWERS_RAND / FLOWERS_RAND);
		for (unsigned j = 0; j < pos; j++)
			db.ignore(numeric_limits<streamsize>::max(), '\n');
		db >> buf;
		FLOWERS.push_back(buf);
		for (unsigned j = 0; j < MAX_FLOWERS_RAND / FLOWERS_RAND - pos; j++)
			db.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	db.close();
}

void generateRandomFlowerbeds(unsigned how_many)
{
	createShapesVector();
	createFlowersVector();
	ofstream file("input.txt");
	unsigned count;
	for (unsigned i = 0; i < how_many; i++)
	{
		file << endl << i + 1 << ' ' << SHAPES[rand() % SHAPES_RAND];
		count = rand() % 5 + 1;
		for (unsigned j = 0; j < count; j++)
			file << ' ' << FLOWERS[rand() % FLOWERS_RAND];
	}
	file.close();
}
//functor for finding flowerbed with particular flower
struct findflower
{
	string val;
	findflower(string v) : val(v)
	{ }
	bool operator () (const Flowerbed& o)
	{
		vector<string> f = o.Flowers();
		return find_if(f.begin(), f.end(), [=](const string& s) {return s == val; }) != f.end();
	}
};
//function for counting total flowers
unsigned count_total_flws(const unsigned start, const Flowerbed& b)
{
	return b.Flowers().size() + start;
}
//helper function for printing vector
void printVct(const vector<Flowerbed>& container)
{
	cout << "\n+----+-------------+------------------------->";
	cout << "\n|  # |    Shape    |   Flowers";
	cout << "\n+----+-------------+------------------------->";
	ostream_iterator<Flowerbed> it(cout, " ");
	copy(container.begin(), container.end(), it);
	cout << "\n+----+-------------+------------------------->\n";
}
int main()
{
	srand(time(NULL));
	//generateRandomFlowerbeds(NUM_FLOWERBEDS); //Comment/uncomment this line to disable/enable generating random data
	ifstream infile("input.txt");
	Flowerbed temp;
	vector<Flowerbed> vct;
	while (!infile.eof())
	{
		infile >> temp;
		vct.push_back(temp);
	}
	ostream_iterator<string> osit(cout, ", ");
	printVct(vct);
	sort(vct.begin(), vct.end());
	cout << "\nSorted by shape:";
	printVct(vct);
	map<unsigned, Flowerbed> fmp;
	for (const Flowerbed& fb : vct)
		fmp.emplace(fb.Num(), fb);
	set<string> difshapes;
	for (const Flowerbed& fb : vct)
		difshapes.insert(fb.Shape());
	cout << "\n\nDifferent shapes: ";
	copy(difshapes.begin(), difshapes.end(), osit);
	unsigned deff;
	cout << "\n\nEnter flowerbed number to show its flowers: ";
	cin >> deff;
	vector<Flowerbed>::iterator fit = find_if(vct.begin(), vct.end(), [=](const Flowerbed& fb) {return fb.Num() == deff; });
	vector<string> flwrs;
	if (fit != vct.end())
		flwrs = fit->Flowers();
	else
		cerr << "\nNo such flowerbed!";
	set<string> sflwrs(flwrs.begin(), flwrs.end());
	copy(sflwrs.begin(), sflwrs.end(), osit);
	set<string> difflws;
	for (const Flowerbed& fb : vct)
	{
		vector<string> temp = fb.Flowers();
		difflws.insert(temp.begin(), temp.end());
	}
	cout << "\n\nDifferent flowers:\n";
	copy(difflws.begin(), difflws.end(), osit);
	cout << "\n\nMaximum number of flowers is in this flowerbed:";
	max_element(vct.begin(), vct.end(), [](const Flowerbed& a, const Flowerbed& b) {return a.Flowers().size() < b.Flowers().size(); })->displayInfo();
	cout << "\n\nEnter number of flowers: ";
	cin >> deff;

	map<unsigned, unsigned> mspec;
	set<string> sps;
	for (const Flowerbed& fb : vct)
	{
		vector<string> fl = fb.Flowers();
		set<string> difspecies(fl.begin(), fl.end());
		sps.insert(difspecies.begin(), difspecies.end());
		mspec.emplace(fb.Num(), difspecies.size());
	}

	map<unsigned, unsigned>::iterator	
		it = find_if(mspec.begin(), mspec.end(), [](pair<unsigned, unsigned> s) {return s.second == 1; }),
		it2 = find_if(mspec.begin(), mspec.end(), [=](pair<unsigned, unsigned> s) {return s.second == deff; });

	
	if (it2 != mspec.end())
	{
		cout << "\n" << deff << " species of flowers are in this flowerbed: ";
		cout << fmp[it2->first];
	}
	else
		cerr << "\nNo flowerbed found with " << deff << " species of flowers!";
	
	if (it != mspec.end())
	{
		cout << "\n\nOnly one species of flowers is in this flowerbed: ";
		cout << fmp[it->first];
	}
	else
		cerr << "\nNo flowerbed found with only one species of flowers!";
	string fl;
	cout << "\n\nEnter name of a flower: ";
	cin >> fl;
	findflower f(fl);
	vector<Flowerbed> withthisflw;
	vector<Flowerbed>::iterator vit = find_if(vct.begin(), vct.end(), f);
	if (vit != vct.end())
	{
		cout << fl << " found in this flowerbed: ";
		cout << *vit;
	}
	else
		cerr << "\nSuch flower not found!";

	cout << "\n\nTotal flowers: ";
	cout << accumulate(vct.begin(), vct.end(), 0, count_total_flws);
	cout << "\nTotal flower species: " << sps.size();
	_getch();
}

