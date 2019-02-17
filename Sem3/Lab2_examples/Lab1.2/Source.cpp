#include <iostream>
#include <string>
//#include <functional>
using namespace std;

int main()
{
	auto CompXY = [](auto f, auto g1, auto g2)
	{
		return [=](auto x, auto y) { return f(g1(x), g2(y)); };
	};

/////////////////////////////////TESTS/////////////////////////////////////
	{
		auto h = CompXY([](int x, int y)-> int {return x < y; },
			[](int x)-> int { return x*x; },
			[](int y)-> int { return y*y*y; }
		);
		bool b = h(6, 3);
		cout << "b=" << boolalpha << b << endl;
	}
//-------------------------------------------------------------------
	{
		auto f = [](double x, double y)->bool {return x >= y; };
		auto g1 = [](double x)->double { return exp(x*x); };
		auto g2 = [](double y)->double { return exp(log(y*y)*y); };
		auto h = CompXY(f, g1, g2);
		bool b = h(6.5, 5.6);
		cout << "b=" << boolalpha << b << endl; 
	}
//-------------------------------------------------------------------

	system("pause");
}