#include <iostream>
#include "Str.h"
using namespace std;

Str::Str()
{
	len = 1;
	value = new char(0);
}
Str::Str(const Str &s)
{
	len = s.len;
	value = new char[len];
	strcpy_s(value, len, s.value);
}
Str::Str(const char *s)
{
	len = strlen(s) + 1;
	value = new char[len];
	strcpy_s(value, len, s);
}
void Str::clear()
{
	len = 1;
	value = new char(0);
}
void Str::print() const
{
	cout << endl << "\"" << value << "\"";
}
void Str::operator = (const Str &s)
{
	len = s.len;
	value = new char[len];
	strcpy_s(value, len, s.value);
}
void Str::operator += (const Str &s)
{
	len += s.len - 1;
	char *temp = new char[len];
	strcpy_s(temp, len, value);
	strcat_s(temp, len, s.value);
	value = new char[len];
	strcpy_s(value, len, temp);
	delete[] temp;
}
bool Str::operator == (const Str &s) const
{
	return !strcmp(value, s.value);
}
bool Str::operator != (const Str &s) const
{
	return strcmp(value, s.value);
}
bool Str::operator > (const Str &s) const
{
	return len > s.len;
}
bool Str::operator < (const Str &s) const
{
	return len < s.len;
}
Str::~Str()
{
	delete[] value;
}

StrDigits::StrDigits() : Str()
{ }
StrDigits::StrDigits(const StrDigits &s) : Str(s)
{ }
StrDigits::StrDigits(const char *s) : Str(s)
{
	for (int i = 0; i < len - 1; i++)
		if (!isdigit(value[i]))
		{
			cout << "\nYou created StrDigits-object with non-numeric characters!";
			clear();
			cout << "\nThe value is cleared to avoid exceptions!";
			break;
		}
}
StrDigits::StrDigits(int n)
{
	char s[9];
	_itoa_s(n, s, 8, 10);
	len = strlen(s) + 1;
	value = new char[len];
	strcpy_s(value, len, s);
}
unsigned int StrDigits::getIntValue() const
{
	return atoi(value);
}
void StrDigits::operator += (const StrDigits &s)
{
	int
		sum = getIntValue() + s.getIntValue(),
		t = sum;
	len = 1;
	while (t > 0)
	{
		t /= 10;
		len++;
	}
	value = new char[len];
	_itoa_s(sum, value, len, 10);
}
bool StrDigits::operator > (const StrDigits &s) const
{
	return atoi(value) > atoi(s.value);
}
bool StrDigits::operator < (const StrDigits &s) const
{ 
	return atoi(value) < atoi(s.value);
}

