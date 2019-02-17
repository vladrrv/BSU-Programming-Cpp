#include <iostream>
#include <string>
using namespace std;


template<class T>
auto FSums(const T &arg) {
	return arg;
}

template<class T, class ...Args>
auto FSums(const T &arg, const Args &...args) {
	return FSums(args...) + arg;
}


int main()
{
	cout << "-------TESTS-----\n";
	{
		short m = -3;
		auto xSum = FSums(1, 2, m, 3, 10);
		cout << " xSum=" << xSum << endl;
	}
	
	{
		short m = 13;
		int n1 = 17, n2 = 23;
		double x = 12.8;
		auto xSum = FSums(n1, 4.7, m, 1.5, 10, n2, 'a');
		cout << " xSum=" << xSum << endl;
	}
	system("pause");
}