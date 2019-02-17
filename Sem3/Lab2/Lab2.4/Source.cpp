#include <iostream>
#include <string>
using namespace std;


template<class ...Args>
string ToString(string divider, Args&&... args)
{
	string s;

	auto bar = [&](auto x)
	{
		string t = to_string(x);
		if (typeid(x) == typeid(double) || typeid(x) == typeid(float))
			t.erase(t.find_last_not_of('0') + 1, string::npos);
		s += t + divider;
	};
	int dummy[] = { 0, (bar(args), 0) ... };
	s.erase(s.size() - 2);
	return s;
}


int main()
{
	cout << "-------TESTS-----\n";
	int n = 17;
	double x = 6.75;
	string s = ToString("; ", 250, 3.7, n, x);
	cout << s << endl;
	system("pause");
}