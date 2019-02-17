#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include "Student.h"
using namespace std;

const unsigned MAX_NAMES_RAND = 88799; // DO NOT CHANGE!
const unsigned NAMES_RAND = 1500;      // 0 < NAMES_RAND <= MAX_NAMES_RAND
const unsigned STUD_NUM = 25;
const unsigned GROUP_NUM = 12;

/*--------------------------------------------------------------*/
/*                     Random Data Generator                    */	
/*--------------------------------------------------------------*/
vector<string> NAMES;
void createNamesVector()
{
	ifstream db("Database_of_Last_Names.txt");
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
void generateRandomStudents(unsigned how_many)
{
	createNamesVector();
	ofstream file("input.txt");
	for (unsigned i = 0; i < how_many; i++)
	{
		file << endl << NAMES[rand() % NAMES_RAND] << ' ' << (rand() % GROUP_NUM + 1);
		for (auto j = 0; j < MK_NUM; j++)
			file << ' ' << rand() % 9 + 2;
	}
	file.close();
}
/*--------------------------------------------------------------*/


void printVct(const vector<Student>& vct, bool(*crit)(const Student&) = [](const Student&)->bool {return true; })
{
	cout << "\n+----------------+---------+-------------+";
	cout << "\n|      Name      | GroupNo |    Marks    |";
	cout << "\n+----------------+---------+-------------+";
	for_each(vct.begin(), vct.end(), [crit](const Student& s)
	{
		if (crit(s)) s.displayInfo();
	});
	cout << "\n+----------------+---------+-------------+\n";
}
int main()
{
	srand(time(NULL));
	generateRandomStudents(STUD_NUM);
	ifstream infile("input.txt");
	vector<Student> vct;
	Student temp;
	while (!infile.eof())
	{
		infile >> temp;
		vct.push_back(temp);
	}
	infile.close();

	printVct(vct);
	sort(vct.begin(), vct.end());
	cout << "\n\nSorted by marks:";
	printVct(vct);

	cout << "\n\nEnter name to delete: ";
	string nameDelete = "";
	cin >> nameDelete;
	auto itdel = find_if(vct.begin(), vct.end(), [nameDelete](Student o) {return o.Name() == nameDelete; });
	if (itdel != vct.end()) vct.erase(itdel);
	else cerr << "\nStudent not found!";
	printVct(vct);

	map<string, Student> stmap;
	for each (Student s in vct)
		stmap[s.Name()] = s;
	cout << "\nMap:\n\n";
	for each (pair<string, Student> p in stmap)
		cout << p.first << endl;

	cout << "\n\nStudents who didn't pass session:";
	printVct(vct, [](const Student& s) {return s.lowestMark() < 4; });

	cout << "\n\nEnter group number: ";
	unsigned gr = 0;
	cin >> gr;

	vector<Student> defgroup(vct.size());
	auto it = copy_if(vct.begin(), vct.end(), defgroup.begin(), [gr](Student o) {return o.Group() == gr; });
	if (it != defgroup.begin())
	{
		defgroup.resize(distance(defgroup.begin(), it));
		cout << "\nBest student in group " << gr << ": ";
		cout << "\n+----------------+---------+-------------+";
		max_element(defgroup.begin(), defgroup.end())->displayInfo();
		cout << "\n+----------------+---------+-------------+\n";
	}
	else cerr << "No students from this group!";

	_getch();
}