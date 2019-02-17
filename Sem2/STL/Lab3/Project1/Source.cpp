#include <iostream>
#include "Catch.h"
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
	ifstream infile;
	ofstream outfile;
	infile.open("input.txt");
	outfile.open("output.txt");
	set<string> fish_in_lake;
	set<string> catched_fish;
	set<string>::iterator siter;
	string temp = "";
	infile >> temp;
	while (temp != "///")
	{
		fish_in_lake.insert(temp);
		infile >> temp;
	}
	for (siter = fish_in_lake.begin(); siter != fish_in_lake.end(); siter++)
	{
		outfile << *siter << " ";
		cout << *siter << " ";
	}
	vector<string> temp_v;
	vector<Catch>::iterator viter;
	cout << endl;
	outfile << endl;
	string temp_f = "", temp_c = "";
	vector<Catch> c1;
	while (!infile.eof())
	{
		infile >> temp_f;
		string b = "";
		getline(infile, b);
		stringstream buf(b);
		while (buf >> temp_c)
			temp_v.push_back(temp_c);
		c1.push_back(Catch(temp_f, temp_v));;
		temp_v.clear();
	}
	for (viter = c1.begin(); viter != c1.end(); viter++)
	{
		viter->info(outfile);
		viter->info(cout);
	}
	vector<string> c2;
	set<string> fishers_fish;
	set<string> current1;
	set<string> current2;
	set<string> common_fish;
	for (viter = c1.begin(); viter != c1.end(); viter++)
	{
		c2 = viter->get_fish();
		fishers_fish.insert(c2.begin(), c2.end());
		if (viter == c1.begin())
		{
			current1 = fishers_fish;
			common_fish = fishers_fish;
			current2 = fishers_fish;
			catched_fish = fishers_fish;
		}
		else
		{
			if (viter != (c1.end() - 1))
			{
				common_fish.clear();
				catched_fish.clear();
			}
			set_intersection(current1.begin(), current1.end(),
				fishers_fish.begin(), fishers_fish.end(),
				inserter(common_fish, common_fish.begin()));
			set_union(current2.begin(), current2.end(),
				fishers_fish.begin(), fishers_fish.end(),
				inserter(catched_fish, catched_fish.begin()));
			current1 = common_fish;
			current2 = catched_fish;
			fishers_fish.clear();
		}
	}
	outfile << "\nCatched fish:\n";
	cout << "\nCatched fish:\n";
	for (siter = catched_fish.begin(); siter != catched_fish.end(); siter++)
	{
		outfile << *siter << " ";
		cout << *siter << " ";
	}
	set<string> not_catched;
	set_difference(fish_in_lake.begin(), fish_in_lake.end(),
		catched_fish.begin(), catched_fish.end(),
		inserter(not_catched, not_catched.begin()));
	outfile << "\nNot catched fish:\n";
	cout << "\nNot catched fish:\n";
	for (siter = not_catched.begin(); siter != not_catched.end(); siter++)
	{
		outfile << *siter << " ";
		cout << *siter << " ";
	}
	outfile << "\nCathed by all fishers:\n";
	cout << "\nCathed by all fishers:\n";
	for (siter = common_fish.begin(); siter != common_fish.end(); siter++)
	{
		outfile << *siter << " ";
		cout << *siter << " ";
	}
	infile.close();
	outfile.close();
	return 0;
}