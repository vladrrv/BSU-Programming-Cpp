#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))


template<class R, class T>
R FSums(const T &arg) {
	return arg;
}

template<class R, class T, class ...Args>
R FSums(const T &arg, const Args &...args) {
	return MIN(FSums<R>(args...), arg);
}


int main()
{

	cout << "-------TESTS-----\n";
	{
		short m = -3;
		auto xSum = FSums<double>(1, 4.7, m, 1.5, 10);
		cout << " xMin=" << xSum << endl;
	}
	
	{
		short m = 13;
		int n1 = 17, n2 = 23;
		double x = 12.8;
		auto xSum = FSums<double>(n1, 4.7, m, 1.5, 10, n2, 'a');
		cout << " xMin=" << xSum << endl;
	}
	system("pause");
}