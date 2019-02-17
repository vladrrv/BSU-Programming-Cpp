#include <iostream>
#include <conio.h>
using namespace std;
int main()
{
	unsigned int mask = 0, pairCount = 0;
	char str[17];
	bool debug = true;
	unsigned int testN = 1723;
	
	for (unsigned int i = 0; i < 65535; i++)
	{
		mask++;
		bool buf[16];
		_int64 a = 1, b = 1;
		for (int j = 0; j < 15; j++)
		{
			int tmask = mask >> j;
			buf[j] = (tmask & 1);
			if (buf[j])
			{
				a *= (j + 1);
			}
			else
			{
				b *= (j + 1);
			}
			
		}
		//_ultoa_s(mask, str, 2);
		//cout << "-------------" << endl;
		//cout << i+1 << " " << str << " a = " << a << " b = " << b << endl;
		//cout << "-------------" << endl;
		if (a < b)
		{
			pairCount++;
			if (debug)
			{
				cout << " a = " << a << " b = " << b << " a * b = " << a * b << endl;
				cout << " pairCount = " << pairCount << endl;
			}
		}
		/*if (i == testN)
		{
			for (int j = 0; j < 16; j++)
			{
				cout << j << " " << buf[j] << endl;

			}
			_getch();
		}
		*/
	}
	cout << "Pairs: " << pairCount << endl;
	_getch();
}