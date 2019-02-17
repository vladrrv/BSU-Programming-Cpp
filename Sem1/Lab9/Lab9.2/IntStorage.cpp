#include <iostream>
#include "IntStorage.h"
using namespace std;

IntStorage::IntStorage()
{
	bitsize = 256;
	bytesize = 32;
	field = new char[bytesize];
	fill_n(field, bytesize, 0);
}
IntStorage::IntStorage(unsigned def_size)
{
	bitsize = (def_size % 8 == 0) ? def_size : (def_size / 8 + 1) * 8;
	bytesize = bitsize / 8;
	field = new char[bytesize];
	fill_n(field, bytesize, 0);
}
IntStorage::IntStorage(const IntStorage &f) : IntStorage(f.bitsize)
{
	memcpy(field, f.field, bytesize);
}
unsigned IntStorage::getSize() const
{
	return bitsize;
}
void IntStorage::store(unsigned n)
{
	if (n < bitsize)
		field[n / 8] |= 1 << (n % 8);
	else
	{
		changeSize(n);
		field[n / 8] |= 1 << (n % 8);
	}
}
bool IntStorage::find(unsigned n) const
{
	if (n >= bitsize)
		return false;
	else
		return field[n / 8] & 1 << (n % 8);
}
void IntStorage::remove(unsigned n)
{
	if (find(n))
		field[n / 8] ^= 1 << (n % 8);
	else
		cout << endl << n << " isn't here!";
}
void IntStorage::print() const
{
	for (int i = 0; i < bitsize; i++)
		if (find(i))
			cout << i << " ";
}
void IntStorage::changeSize(unsigned new_size)
{
	if (new_size != bitsize)
	{
		unsigned old_size = bytesize;
		bitsize = (new_size % 8 == 0) ? new_size : (new_size / 8 + 1) * 8;
		bytesize = bitsize / 8;
		char *buf = new char[bytesize];
		fill_n(buf, bytesize, 0);
		memcpy(buf, field, old_size);
		field = new char[bytesize];
		fill_n(field, bytesize, 0);
		memcpy(field, buf, bytesize);
	}
}
IntStorage &IntStorage::operator = (const IntStorage &s)
{
	if (this != &s)
	{
		bitsize = s.bitsize;
		bytesize = bitsize / 8;
		field = new char[bytesize];
		memcpy(field, s.field, bytesize);
	}
	return *this;
}
IntStorage::~IntStorage()
{
	delete[] field;
}