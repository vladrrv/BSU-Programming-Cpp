#include <iostream>
#include <conio.h>
using namespace std;
int romSym2Num(char r_sym)
{
	switch (int(r_sym))
	{
	case (73):
		return 1;
	case (86):
		return 5;
	case (88):
		return 10;
	case (76):
		return 50;
	case (67):
		return 100;
	case (68):
		return 500;
	case (77):
		return 1000;
	}
}

bool check(char *r)
{
	int M_count = 0, D_count = 0, C_count = 0, L_count = 0, X_count = 0, V_count = 0, I_count = 0;
	if (strlen(r) > 2)
		for (int i = 1; i < strlen(r) - 1; i++)
		{
			int n0 = romSym2Num(r[i - 1]), n1 = romSym2Num(r[i]), n2 = romSym2Num(r[i + 1]);
			if ((n2 >= n1 && n0 >= n1) || (n0 >= n1 && n1 >= n2) || (n1 >= n0 && n1 >= n2))
			{
				int dif = n1 - n0;
				if (!(dif == 900 || dif == 90 || dif == 9 || dif == 400 || dif == 40 || dif == 4) && (n1 == n0 && n1 < n2))
					return false;
			}
			else
				return false;
		}
	else
		if (strlen(r) == 2)
		{
			int n1 = romSym2Num(r[0]), n2 = romSym2Num(r[1]);
			int dif = n2 - n1;
			if ((n2 > n1) && !(dif == 900 || dif == 90 || dif == 9 || dif == 400 || dif == 40 || dif == 4))
				return false;
		}

	for (int i = 0; i < strlen(r); i++)
	{
		switch (int(r[i]))
		{
		case (73):
		{
			I_count++;
			break;
		}
		case (86):
		{
			V_count++;
			break;
		}
		case (88):
		{
			X_count++;
			break;
		}
		case (76):
		{
			L_count++;
			break;
		}
		case (67):
		{
			C_count++;
			break;
		}
		case (68):
		{
			D_count++;
			break;
		}
		case (77):
		{
			M_count++;
			break;
		}
		default:
			return false;
		}
	}
	if (M_count <= 4 && D_count < 2 && C_count < 4 && L_count < 2 && X_count < 4 && V_count < 2 && I_count < 4)
		return true;
	else
		return false;
}

int convertRom2Dec(char *r_num)
{
	int num = 0;
	for (int i = 0; i < strlen(r_num); i++)
	{
		int d1 = romSym2Num(r_num[i]) , d2 = romSym2Num(r_num[i + 1]);
		if (d2 > d1)
			d1 *= -1;
		num += d1;
	}
	return num;
}

void main()
{
	while (true)
	{
		char str[256];
		cout << "Enter roman number: ";
		cin >> str;
		for (int i = 0; i < strlen(str); i++)
			str[i] = toupper(str[i]);
		if (check(str))
			cout << "Decimal representation: " << convertRom2Dec(str) << "\n\n-------------------------\n";
		else
			cout << "Incorrect input!" << "\n\n-------------------------\n";
		if (_getch() == 27) break;
	}
}