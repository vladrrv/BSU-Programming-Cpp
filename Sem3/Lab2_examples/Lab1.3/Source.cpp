#include <iostream>
#include <string>
using namespace std;

int main()
{
	auto CompXYZ = [](auto f1, auto f2, auto g1, auto g2, auto g3)
	{
		return [=](auto x, auto y) { return f1( f2(g1(x), g2(y)), g1(x), g3(y) ); };
	};

	/////////////////////////////////TESTS/////////////////////////////////////
	auto f1 = [](int x, int y, int z)->int { return x - y + z; };
	auto f2 = [](int x, int y)->int { return (x + y)*x; };
	auto g1 = [](int x)->int { return x*x; };
	auto g2 = [](int x)->int { return x*x*x; };
	auto g3 = [](int x)->int { return x*x - x; };
	auto h = CompXYZ(f1, f2, g1, g2, g3);
	// Çהוסü h(x,y)=(x*x+y*y*y)*x*x - x*x + y*y-y = =
	//
	auto res = h(6, 3);
	cout << "res=" << res << endl;
	//-------------------------------------------------------------------

	system("pause");
}