#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iterator>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include "Fisherman.h"
using namespace std;

/*--------------------------------------------------------------*/
/*                        DO NOT CHANGE!                        */
/* These constants are set according to the sizes of databases  */
/*--------------------------------------------------------------*/
const unsigned MAX_FISH_RAND = 38;  //Total species in database  /
const unsigned MAX_NAMES_RAND = 88799;//Total names in database  /
/*--------------------------------------------------------------*/

/*-------------------------------------*/
/*          Editable constants         */
/*-------------------------------------*/
const unsigned FISH_RAND = 30;
const unsigned NUM_FISHERMEN = 4;
const unsigned NAMES_RAND = NUM_FISHERMEN;

/*--------------------------------------------------------------*/
/*                     Random Data Generator                    */
/*--------------------------------------------------------------*/
vector<string> NAMES;
vector<string> FISHES;
void createNamesVector()
{
	ifstream db("Last_Names_DB.txt");
	string buf;
	db.seekg(ios::beg);
	for (unsigned i = 0; i < NAMES_RAND; i++)
	{
		unsigned pos = rand()*rand() % (MAX_NAMES_RAND / NAMES_RAND);
		for (unsigned j = 0; j < pos; j++)
			db.ignore(numeric_limits<streamsize>::max(), '\n');
		db >> buf;
		NAMES.push_back(buf);
		for (unsigned j = 0; j < MAX_NAMES_RAND / NAMES_RAND - pos; j++)
			db.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	db.close();
}
void createFishVector()
{
	ifstream db("Fish_Species_DB.txt");
	string buf;
	db.seekg(ios::beg);
	for (unsigned i = 0; i < FISH_RAND; i++)
	{
		unsigned pos = rand()*rand() % (MAX_FISH_RAND / FISH_RAND);
		for (unsigned j = 0; j < pos; j++)
			db.ignore(numeric_limits<streamsize>::max(), '\n');
		db >> buf;
		FISHES.push_back(buf);
		for (unsigned j = 0; j < MAX_FISH_RAND / FISH_RAND - pos; j++)
			db.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	db.close();
}

void generateRandomFishermen(unsigned how_many)
{
	createNamesVector();
	createFishVector();
	ofstream file("input.txt");
	for (auto f : FISHES)
		file << endl << f;
	file << endl << "---";
	unsigned count;
	for (unsigned i = 0; i < how_many; i++)
	{
		file << endl << NAMES.back(); NAMES.pop_back();
		count = rand() % 10 + 1;
		for (unsigned j = 0; j < count; j++)
			file << ' ' << FISHES[rand() % FISH_RAND];
	}
	file.close();
}

int main()
{
	srand(time(NULL));
	//generateRandomFishermen(NUM_FISHERMEN);
	set<string> available_fish;
	ifstream infile("input.txt");
	Fisherman temp;
	multiset<Fisherman> fset;
	string fish = "";
	infile >> fish;
	while (fish != "---")
	{
		available_fish.insert(fish);
		infile >> fish;
	}
	while (!infile.eof())
	{
		infile >> temp;
		fset.insert(temp);
	}
	set<string> difspecies;
	set<string> catched_fish;
	multiset<string> h;
	set<string> temphaul;
	set<string> each_fish(available_fish.begin(), available_fish.end());
	ofstream outfile("output.txt");
	for (auto f : fset)
	{
		set<string> t;
		h = f.Haul();
		temphaul = set<string>(h.begin(), h.end());
		difspecies.insert(temphaul.begin(), temphaul.end());
		set_union(temphaul.begin(), temphaul.end(), catched_fish.begin(), catched_fish.end(), inserter(catched_fish, catched_fish.begin()));
		if (!each_fish.empty())
			set_intersection(each_fish.begin(), each_fish.end(), temphaul.begin(), temphaul.end(), inserter(t, t.begin()));
		each_fish = t;
		f.displayInfo(outfile);
		for (auto s : difspecies)
			outfile << s << ", ";
		difspecies.clear();
	}
	
	//outfile << "\n+------------------------->";
	//outfile << "\nAvailable Fish:\n";
	//for (auto s : available_fish)
	//	outfile << s << ", ";
	outfile << "\n+------------------------->";
	outfile << "\nCommon Fish:\n";
	for (auto s : each_fish)
		outfile << s << ", ";

	outfile << "\n+------------------------->";
	outfile << "\nCatched Fish:\n";
	for (string s : catched_fish)
		outfile << s << ", ";

	set<string> noncatched_fish;
	outfile << "\n+------------------------->";
	outfile << "\nNon-Catched Fish:\n";
	set_difference(available_fish.begin(), available_fish.end(), catched_fish.begin(), catched_fish.end(), inserter(noncatched_fish, noncatched_fish.begin()));
	for (auto s : noncatched_fish)
		outfile << s << ", ";

	_getch();
}