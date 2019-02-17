#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include "Route.h"
using namespace std;

int main()
{
	ifstream infile;
	infile.open("input.txt");
	string na = "", mo = "";
	int nu = 0, bu = 0;
	vector<Route> ivector;
	vector<Route>::iterator iter;
	while (!infile.eof())
	{
		infile >> nu >> na >> bu >> mo;
		ivector.push_back(Route(nu, na, bu, mo));
	}
	iter = ivector.begin();
	for (; iter != ivector.end(); iter++)
	{
		iter->info();
	}
	cout << "\nSorted by bus number:\n\n";
	sort(ivector.begin(), ivector.end());
	for (iter = ivector.begin(); iter != ivector.end(); iter++)
	{
		iter->info();
	}
	cout << "\nIn map (key - driver): \n\n";
	multimap<string, Route> imap;
	multimap<string, Route>::iterator miter;
	iter = ivector.begin();
	while (iter != ivector.end())
	{
		imap.insert(pair<string, Route>(iter->driver(), (*iter)));
		iter++;
	}
	map<string, Route>::iterator maxiter = imap.begin();
	for (miter = imap.begin(); miter != imap.end(); miter++)
	{
		cout << miter->first << endl;
	}
	multimap<int, string> newmap;
	multimap<int, string>::iterator newiter;
	iter = ivector.begin();
	while (iter != ivector.end())
	{
		newmap.insert(pair<int, string>(iter->getroute(), iter->driver()));
		iter++;
	}
	cout << "\nNumber of route: ";
	int nr;
	cin >> nr;
	cout << "\nList of drivers: \n";
	pair<multimap<int, string>::iterator, multimap<int, string>::iterator> iterpair = newmap.equal_range(nr);
	for (newiter = iterpair.first; newiter != iterpair.second; newiter++)
	{
		cout << newiter->second << endl;
	}
	cout << "\n\nDifferent routes: \n";
	set<int> iset;
	set<int>::iterator siter;
	iter = ivector.begin();
	while (iter != ivector.end())
	{
		iset.insert(iter->getroute());
		iter++;
	}
	for (siter = iset.begin(); siter != iset.end(); siter++)
	{
		cout << *siter << endl;
	}
	cout << "\nNumber of different bus models: \n";
	set<string> mset;
	set<string>::iterator msiter;
	iter = ivector.begin();
	while (iter != ivector.end())
	{
		mset.insert(iter->getmodel());
		iter++;
	}
	cout << mset.size() << endl;
	string fname;
	cout << "\nChange bus to: ";
	
	cin >> nr;
	cout << "for driver: ";
	cin >> fname;
	for (miter = imap.begin(); miter != imap.end(); miter++)
	{
		if (miter->first == fname)
		{
			miter->second.changebus(nr);
		}
	}
	cout << "\nNew info: \n\n";
	for (miter = imap.begin(); miter != imap.end(); miter++)
	{
		miter->second.info();
	}
	multiset<int> nset;
	iter = ivector.begin();
	while (iter != ivector.end())
	{
		nset.insert(iter->getroute());
		iter++;
	}
	cout << "\n\nMaximum of buses on route: ";
	map<int, int> bmap;
	int buses;
	for (siter = iset.begin(); siter != iset.end(); siter++)
	{
		buses = nset.count(*siter);
		bmap.insert(pair<int, int>(buses, (*siter)));
	}
	map<int, int>::iterator ibmap;
	ibmap = max_element(bmap.begin(), bmap.end());
	cout << ibmap->second << endl;
	cout << "\nErase driver: \n\n";
	cin >> fname;
	/*for (miter = imap.begin(); miter != imap.end(); miter++)
	{
		if (miter->first == fname)
		{
			imap.erase(miter);
			miter--;
		}
	}*/
	remove_if(imap.begin(), imap.end(), [=](pair<string, Route> &p) { return p.first == fname; });
	cout << "\nAfter erase: \n\n";
	for (miter = imap.begin(); miter != imap.end(); miter++)
	{
		miter->second.info();
	}
	infile.close();
	system("pause");
	return 0;

}

