#include <iostream>
#include <string>
//#include <functional>
using namespace std;


int main()
{
	auto composeFxGx = [](auto f1, auto f2)
	{
		return [=](auto x) { return f1(f2(x)); };
	};
	auto f = [](double x)->double { return sin(x); };
	auto g = [](double x)->double { return x*x; };
	auto hd = composeFxGx(f, g);


	cout << "\n" << hd(1.353314) << "\n";

	system("pause");
}