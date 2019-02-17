#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


class Catch
{
	string fisher;
	vector<string> fish;
public:
	Catch()
	{
		fisher = "No_info";
	}
	Catch(const Catch &st)
	{
		fisher = st.fisher;
		fish = st.fish;
	}
	Catch(string f, vector<string> m)
	{
		fisher = f;
		fish = m;
	}
	string get_fisher() const;
	vector<string> get_fish() const;
	void info(ostream&);
};

string Catch::get_fisher() const
{
	return fisher;
}

vector<string> Catch::get_fish() const
{
	return fish;
}

void Catch::info(ostream& o)
{
	o << "Fisher: " << fisher << "\tCatch: ";
	vector<string>::iterator iter;
	for (iter = fish.begin(); iter != fish.end(); iter++)
		o << *iter << " ";
	o << endl;
}
