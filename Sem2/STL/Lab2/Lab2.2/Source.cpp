#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include "Route.h"
using namespace std;

/*--------------------------------------------------------------*/
/*                        DO NOT CHANGE!                        */
/* These constants are set according to the sizes of databases  */
/*--------------------------------------------------------------*/
const unsigned MAX_BRANDS_RAND = 80; //Total brands in database  /
const unsigned MAX_NAMES_RAND = 88799;//Total names in database  /
/*--------------------------------------------------------------*/

/*-------------------------------------*/
/*          Editable constants         */
/*-------------------------------------*/
const unsigned NAMES_RAND = 10;
const unsigned BRANDS_RAND = 10;
const unsigned NUM_ROUTES = 20;

/*--------------------------------------------------------------*/
/*                     Random Data Generator                    */
/*--------------------------------------------------------------*/
vector<string> NAMES;
vector<string> BRANDS;
void createNamesVector()
{
	ifstream dbnm("Database_of_Last_Names.txt");
	string buf;
	dbnm.seekg(ios::beg);
	for (unsigned i = 0; i < NAMES_RAND; i++)
	{
		unsigned pos = rand()*rand() % (MAX_NAMES_RAND / NAMES_RAND);
		for (unsigned j = 0; j < pos; j++)
			dbnm.ignore(numeric_limits<streamsize>::max(), '\n');
		dbnm >> buf;
		NAMES.push_back(buf);
		for (unsigned j = 0; j < MAX_NAMES_RAND / NAMES_RAND - pos; j++)
			dbnm.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	dbnm.close();
}
void createBrandsVector()
{
	ifstream dbbs("Database_of_Bus_Brands.txt");
	string buf;
	dbbs.seekg(ios::beg);
	for (unsigned i = 0; i < BRANDS_RAND; i++)
	{
		unsigned pos = rand()*rand() % (MAX_BRANDS_RAND / BRANDS_RAND);
		for (unsigned j = 0; j < pos; j++)
			dbbs.ignore(numeric_limits<streamsize>::max(), '\n');
		dbbs >> buf;
		BRANDS.push_back(buf);
		for (unsigned j = 0; j < MAX_BRANDS_RAND / BRANDS_RAND - pos; j++)
			dbbs.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	dbbs.close();
}
void generateRandomRoutes(unsigned how_many)
{
	createNamesVector();
	createBrandsVector();
	ofstream file("input.txt");
	for (unsigned i = 0; i < how_many; i++)
		file << endl << (rand() % 100 + 1) << ' ' << NAMES[rand() % NAMES_RAND]
			<< ' ' << (rand() % 9000 + 1000) << ' ' << BRANDS[rand() % BRANDS_RAND];
	file.close();
}
/*--------------------------------------------------------------*/

void printVct(const vector<Route>& vct)
{
	cout << "\n+----+----------------+-----+-------------+";
	cout << "\n|  # |  Driver's Name |BusNo|  Bus Brand  |";
	cout << "\n+----+----------------+-----+-------------+";
	for each (Route s in vct)
		s.displayInfo();
	cout << "\n+----+----------------+-----+-------------+\n";
}

int main()
{
	srand(time(NULL));
	generateRandomRoutes(NUM_ROUTES); //comment this to disable random data generation
	ifstream infile("input.txt");
	vector<Route> vct;
	Route temp;
	while (!infile.eof())
	{
		infile >> temp;
		vct.push_back(temp);
	}
	infile.close();

	cout << "Raw Data:";
	printVct(vct);

	sort(vct.begin(), vct.end());
	cout << "\nSorted by route number:";
	_getch();
	printVct(vct);
	cout << "\nSet from route numbers:";
	_getch();
	set<unsigned> rset;
	for each (Route s in vct)
		rset.insert(s.Num());
	for each (unsigned p in rset)
		cout << endl << setw(5) << p;

	cout << "\n\nEnter route number (to show buses of this route): ";
	unsigned defroute = 0;
	cin >> defroute;
	auto showbegin = find_if(vct.begin(), vct.end(), [defroute](Route o) {return o.Num() == defroute; });
	auto showend = find_if(showbegin, vct.end(), [defroute](Route o) {return o.Num() != defroute; });
	cout << "\n+-----+-------------+";
	cout << "\n|BusNo|  Bus Brand  |";
	cout << "\n+-----+-------------+";
	for_each(showbegin, showend, [](Route s) {cout << "\n|" << setw(5) << right << s.BusNum() << "| " << setw(12) << left << s.BusBrand() << right << "|"; });
	cout << "\n+-----+-------------+\n";

	cout << "\nDrivers with one bus brand:";
	_getch();
	map<string, set<string> > difbr;
	for each (Route s in vct)
		difbr[s.Name()].insert(s.BusBrand());
	cout << "\n+----------------+-------------+";
	cout << "\n|  Driver's Name |  Bus Brand  |";
	cout << "\n+----------------+-------------+";
	for_each(difbr.begin(), difbr.end(), [](pair<string, set<string> > p) 
	{
		if (p.second.size() == 1)
			cout << endl << "|" << setw(15) << right << p.first << " | " << setw(12) << left << *p.second.begin() << right << "|"; 
	});
	cout << "\n+----------------+-------------+\n";
	

	cout << "\nEnter route to delete: ";
	cin >> defroute;
	auto delbegin = find_if(vct.begin(), vct.end(), [defroute](Route o) {return o.Num() == defroute; });
	auto delend = find_if(delbegin, vct.end(), [defroute](Route o) {return o.Num() != defroute;});
	vct.erase(delbegin, delend);
	printVct(vct);

	cout << "\nEnter driver's name to change and new driver's name: ";
	string driver = "", newdriver = "";
	cin >> driver >> newdriver;
	for_each(vct.begin(), vct.end(), [driver, newdriver](Route& s)
	{
		if (s.Name() == driver)
			s.updateDriver(newdriver);
	});
	printVct(vct);

	cout << "\nEnter driver name to show his routes: ";
	cin >> driver;
	vector<Route> defdrv;
	for_each(vct.begin(), vct.end(), [driver, &defdrv](Route o) {if (o.Name() == driver) defdrv.push_back(o); });
	if (!defdrv.empty())
		printVct(defdrv);
	else cerr << "\nDriver not found!\n";
	set<string> mbr;
	for each (Route s in vct)
		mbr.insert(s.BusBrand());
	cout << "\n\nNumber of different bus brands: " << mbr.size();
	_getch();
}
