#include <iostream>
#include <conio.h>
using namespace std;

char digConv(int dig)
{
	if (dig < 10)
		return 48 + dig;
	else
		return 55 + dig;
}

char *dec2Hex(int num)
{
	char conv[256]; int i = 0;
	while (num > 0)
	{
		conv[i++] = digConv(num % 16);
		num /= 16;
	}
	conv[i] = 0;
	char s[256] = "0x";
	_strrev(conv);
	strcat_s(s, 256, conv);
	return s;
}

char *replace(char *str, char *buf)
{
	char numbuf[256], *convnumbuf;
	int b = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		int j = i, k = 0;

		while (isdigit(str[i]))
		{
			numbuf[k++] = str[i++];
		}
		numbuf[k] = 0;
		if (k == 0)
			buf[b++] = str[i];
		else
		{
			convnumbuf = dec2Hex(atoi(numbuf));
			memcpy(buf + b, convnumbuf, strlen(convnumbuf));
			b += strlen(convnumbuf);
			i--;
		}
	}
	buf[b] = 0;
	for (int i = 0; i < strlen(buf); i++)
		cout << buf[i];
	return buf;
}

void assert(char *str, char *res)
{
	char myRes[256];
	replace(str, myRes);
	if (memcmp(myRes, res, strlen(myRes)) == 0)
		cout << "\nCorrect\n\n";
	else
		cout << "\nIncorrect\n\n";
	;
}
void main()
{
	char str[] = "aaaa45bbbb";
	char ans[] = "aaaa0x2Dbbbb";
	assert(str, ans);
	char str1[] = "random number 1234 ...";
	char ans1[] = "random number 0x4D2 ...";
	assert(str1, ans1);
	char str2[] = "1000 is a thousand, and 1000000 is a million";
	char ans2[] = "0x3E8 is a thousand, and 0xF4240 is a million";
	assert(str2, ans2);
	char str3[] = "10527453";
	char ans3[] = "0xA0A2DD";
	assert(str3, ans3);
	_getch();
}