#include <iostream>
#include <tuple>
#include <string>
using namespace std;


template<class ...Args>
tuple<int, double> FSum2(Args&&... args)
{
	double sum_d = 0;
	int sum_i = 0;

	auto bar = [&](auto x)
	{
		if (typeid(x) == typeid(double) || typeid(x) == typeid(float))
			sum_d += x;
		else
			sum_i += x;
	};
	int dummy[] = { 0, (bar(args), 0) ... };

	return tuple<int, double>(sum_i, sum_d);
}

/*---------------------------------------------------------------------*/
/*                       Another implementation                        */
/*---------------------------------------------------------------------*/
template<class T>
void sum(int& sum_i, double& sum_d, T x)
{
	if (typeid(x) == typeid(double) || typeid(x) == typeid(float))
		sum_d += x;
	else
		sum_i += x;
}

template<class T, class ...Args>
void sum(int& sum_i, double& sum_d, T x, Args... args)
{
	if (typeid(x) == typeid(double) || typeid(x) == typeid(float))
		sum_d += x;
	else
		sum_i += x;
	sum(sum_i, sum_d, args...);
}

template<class ...Args>
tuple<int, double> FSum(Args... args)
{
	double sum_d = 0;
	int sum_i = 0;
	sum(sum_i, sum_d, args...);
	return tuple<int, double>(sum_i, sum_d);
}
/*---------------------------------------------------------------------*/


int main()
{
	cout << "-------TESTS-----\n";
	{ 
		short sm = 33;

		tuple<int,double> sx2 = FSum2(10.6, 2, 4.7, sm);

		cout << "sx2=";
		cout << " " << get<int>(sx2);
		cout << " " << get<double>(sx2);
		cout << endl;
	}
	system("pause");
}