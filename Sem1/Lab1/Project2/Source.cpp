#include <iostream>
#include <conio.h>
using namespace std;

_int64 factor(int n)
{
	_int64 f = 1;
	if (n == 1)
		return f;
	else
	{
		f *= n;
		return f*factor(n-1);
	}
}

int getFactNum(int n)
{
	_int64 f = factor(n);
	_int64 b = f, a = 1, r;
	int pairCount = 0;
	while (true)
	{
		a++;
		b = f / a;

		if (b <= a)
			break;
		if (f % a == 0)
			pairCount++;
	}
	return pairCount;
}

int main()
{
	int n = 20;

	cout << "Number of pairs for " << n << "! : " << getFactNum(n) << endl;
	_getch();
	return 0;
}
