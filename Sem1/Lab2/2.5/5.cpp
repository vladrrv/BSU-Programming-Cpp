#include <conio.h>
#include <iostream>
using namespace std;

int charToNum(char ch)
{
	int charCode = (int)ch;
	if (charCode > 64)
		return charCode - 55;
	else
		return charCode - 48;
}

char numToChar(int d)
{
	if (d > 9)
		return (char)(d + 55);
	else
		return (char)(d + 48);
}

unsigned _int64 convert2Dec(char n[], int m)
{
	unsigned _int64 dec = 0;
	int n_len = strlen(n);
	for (int i = 0; i < n_len; i++)
		n[i] = toupper((unsigned char)n[i]);
	for (int i = 0; i < n_len; i++)
	{
		dec += charToNum(n[n_len - 1 - i]) * (unsigned _int64)pow((double)m, (double)i);
	}
	return dec;
}

char *convert2SpecK(unsigned _int64 d, int k, char *buf)
{
	int i = 0;
	while (d > 0)
	{
		unsigned _int64 q = d / k;
		int r = d % k;
		buf[i] = numToChar(r);
		i++;
		d = q;
	}
	buf[i] = 0;
	return _strrev(buf);
}

void main()
{
	char n[255], buf[255];
	int m, k;
	do {
		cout << "Enter number n: ";
		cin >> n;
        cout << "Initial base of number m: ";
		cin >> m;
		cout << "Target base of number  k: ";
		cin >> k;

		unsigned _int64 d = convert2Dec(n, m);
		cout << "Decimal representation of number: " << d << endl;
		convert2SpecK(d, k, buf);
		cout << "Number in target base: "<< buf << endl;
		cout << "-------------------------------------------" << endl;
	} while (_getch() != 27);
}