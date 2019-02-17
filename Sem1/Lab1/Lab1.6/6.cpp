#include <iostream>
using namespace std;
#include <math.h>
#include <conio.h>

int primeDivs(bool arr[])
{
	int div[16];
	for (int i = 0; i < 16; i++)
	{
		div[i] = 0;
	}
	for (int n = 2; n < 16; n++)
	{
		if (arr[n])
		{
			int i = n;
			for (int j = 2; j <= i; j++)
			{
				while (i % j == 0)
				{
					div[j]++;
					i /= j;
				}
			}
		}
	}
	return div[16];
}




int main()
{
	unsigned int  numOfPairs = 0;
	bool a[16], b[16];
	for (int i = 0; i < 16; i++)
	{
		a[i] = false;
	}

	for (int numOfA = 1; numOfA < 12; numOfA++)
	{
		for (int i = 1; i <= numOfA; i++)
		{
			for (int j = 2; j < 16; j++)
			{
				a[j+i] = true;

				a[j+i] = false;
			}
			
		}
		
		//if ((A <= B))
		//	numOfPairs++;

	}

	cout << "Number of pairs: " << numOfPairs << endl;

	_getch();
	return 0;
}


