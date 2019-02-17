//#define _SCL_SECURE_NO_WARNINGS
#include <iostream>
#include <iterator>
#include <string>
#include "Flowerbed.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
string find_flower;
string new_flower;
int find_num;

void func(Flowerbed &pa)
{
	vector<string> my_vect = pa.get_flowers();
	vector<string>::iterator viter2;
	for (viter2 = my_vect.begin(); viter2 != my_vect.end(); viter2++)
		if (*viter2 == find_flower)
		{
			*viter2 = new_flower;
		}
	Flowerbed c2(pa.get_num(), pa.get_shape(), my_vect);
	c2.info(cout);
}

void cur_flowers(Flowerbed &pa)
{
	vector<string> my_flowers;
	vector<string>::iterator viter2;
	if (pa.get_num() == find_num)
	{
		my_flowers = pa.get_flowers();
		cout << "\n\nFlowers of " << find_num << " flowerbed are: ";
		for (viter2 = my_flowers.begin(); viter2 != my_flowers.end(); viter2++)
			cout << *viter2 << " ";
	}
}


int main()
{
	ifstream infile;
	ofstream outfile;
	infile.open("input.txt");
	outfile.open("output.txt");
	vector<Flowerbed>::iterator viter;
	cout << endl;
	outfile << endl;
	vector<Flowerbed> c1;
	istream_iterator<Flowerbed> eos;
	for (istream_iterator<Flowerbed> iit(infile); iit != eos; iit++)
		c1.push_back(*iit);

	cout << "Data in vector: \n";
	outfile << "Data in vector: \n";

	ostream_iterator<Flowerbed> osit(cout);
	copy(c1.begin(), c1.end(), osit);
	ostream_iterator<Flowerbed> ofsit(outfile);
	copy(c1.begin(), c1.end(), ofsit);
	/*for (viter = c1.begin(); viter != c1.end(); viter++)
	{
		viter->info(outfile);
		viter->info(cout);
	}*/
	sort(c1.begin(), c1.end());
	cout << "\nSorted by shape: \n";
	outfile << "\nSorted by shape: \n";
	for (viter = c1.begin(); viter != c1.end(); viter++)
	{
		viter->info(outfile);
		viter->info(cout);
	}
	set<string> shapes_of_flowerbeds;
	set<string>::iterator siter;
	for (viter = c1.begin(); viter != c1.end(); viter++)
		shapes_of_flowerbeds.insert(viter->get_shape());
	cout << "\nShapes of flowerbeds: (task 4.1)\n";
	outfile << "\nShapes of flowerbeds: (task 4.1)\n";
	ostream_iterator<string> oit();
	for (siter = shapes_of_flowerbeds.begin(); siter != shapes_of_flowerbeds.end(); siter++)
	{
		cout << *siter << " ";
		outfile << *siter << " ";
	}
	cout << "\n\nSize of all shapes (task 6.1): \n" << shapes_of_flowerbeds.size() << endl;
	outfile << "\n\nSize of all shapes (task 6.1): \n" << shapes_of_flowerbeds.size() << endl;
	cout << "\n\nNumber of flowerbed: (task 4.2)\n";
	outfile << "\n\nNumber of flowerbed: (task 4.2)\n";
	cin >> find_num;
	for_each(c1.begin(), c1.end(), cur_flowers);
	vector<string> c2;
	set<string> this_flowers;
	set<string> current;
	set<string> current2;
	set<string> common_flowers;
	set<string> all_flowers;
	for (viter = c1.begin(); viter != c1.end(); viter++)
	{
		c2 = viter->get_flowers();
		this_flowers.insert(c2.begin(), c2.end());
		if (viter == c1.begin())
		{
			current = this_flowers;
			common_flowers = this_flowers;
			current2 = this_flowers;
			all_flowers = this_flowers;
		}
		else
		{
			if (viter != (c1.end() - 1))
			{
				common_flowers.clear();
				all_flowers.clear();
			}
			set_intersection(current.begin(), current.end(),
				this_flowers.begin(), this_flowers.end(),
				inserter(common_flowers, common_flowers.begin()));
			set_union(current2.begin(), current2.end(),
				this_flowers.begin(), this_flowers.end(),
				inserter(all_flowers, all_flowers.begin()));

			current = common_flowers;
			current2 = all_flowers;
			this_flowers.clear();
		}
	}
	outfile << "\n\nCommon flowers (task 5.5):\n";
	cout << "\n\nCommon flowers (task 5.5):\n";
	for (siter = common_flowers.begin(); siter != common_flowers.end(); siter++)
	{
		outfile << *siter << " ";
		cout << *siter << " ";
	}
	outfile << "\n\nAll flowers (task 4.4):\n";
	cout << "\n\nAll flowers (task 4.4):\n";
	for (siter = all_flowers.begin(); siter != all_flowers.end(); siter++)
	{
		outfile << *siter << " ";
		cout << *siter << " ";
	}
	cout << "\n\nSize of all flowers (task 6.2): \n" << all_flowers.size() << endl;
	outfile << "\n\nSize of all flowers (task 6.2): \n" << all_flowers.size() << endl;
	outfile << "\n\nMaximum of flowers on flowerbed (task 5.1):\n";
	cout << "\n\nMaximum of flowers on flowerbed (task 5.1):\n";
	map< int, vector <string> > nset;
	map< int, vector <string> >::iterator niter;
	viter = c1.begin();
	while (viter != c1.end())
	{
		nset.insert(pair<int, vector <string> >(viter->get_num(), viter->get_flowers()));
		viter++;
	}
	map<int, int> bmap;
	int am_fl;
	for (niter = nset.begin(); niter != nset.end(); niter++)
	{
		am_fl = (niter->second).size();
		bmap.insert(pair<int, int >(am_fl, niter->first));
	}
	map<int, int>::iterator ibmap;
	ibmap = max_element(bmap.begin(), bmap.end());
	cout << ibmap->second << endl;
	outfile << "\n\nNumber of flowerbeds with one flower: (task 5.3):\n";
	cout << "\n\nNumber of flowerbeds with one flower: (task 5.3):\n";
	for (viter = c1.begin(); viter != c1.end(); viter++)
	{
		if ((viter->get_flowers()).size() == 1)
			cout << viter->get_num() << " ";
	}
	outfile << "\n\nFlower to find (task 6.3):\n";
	cout << "\n\nFlower to be replaced (task 6.3):\n";
	cin >> find_flower;
	cout << "\n\nNew flower: \n";
	outfile << "\n\nNew flower: \n";
	cin >> new_flower;
	for_each(c1.begin(), c1.end(), func);
	infile.close();
	outfile.close();

	return 0;
}