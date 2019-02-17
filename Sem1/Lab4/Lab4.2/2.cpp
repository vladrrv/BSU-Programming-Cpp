#include <iostream>
#include <conio.h>
using namespace std;


int replace(char *str)
{
	char numbuf[256];
	int convnumbuf, res = 0, sign = 1;
	int b = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		int k = 0;
		
		while (isdigit(str[i]))
		{
			numbuf[k++] = str[i++];
			;
		}
		numbuf[k] = 0;
		res += atoi(numbuf)*sign;
		switch (str[i])
		{
		case ('+'):
		{
			sign = 1;
			break;
		}
		case ('-'):
		{
			sign = -1;
			break;
		}

		}
		
	}
	return res;
}

void assert(char *str, int res)
{
	int myRes = replace(str);
	if (myRes == res)
		cout << "\nCorrect\n\n";
	else
		cout << "\nIncorrect\n\n";
	;
}


void main()
{
	char task1[256] = "2+4";
	assert(task1, 6);
	char task2[256] = "21+22+300-61";
	assert(task2, 282);
	char task3[256] = "-5-6+3";
	assert(task3, -8);
	char task4[256] = "2+4-40";
	assert(task4, -34);
	char task5[256] = "+4+5";
	assert(task5, 9);
	_getch();
}