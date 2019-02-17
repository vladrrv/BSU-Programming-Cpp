#include <iostream>
#include <fstream>
#include "IntSet.h"
using namespace std;

IntSet::IntSet()
{ }
IntSet::IntSet(int arr[], int count)
{
	for (int i = 0; i < count; i++)
		if (arr[i] >= 0)
			pos.store(arr[i]);
		else
			neg.store(abs(arr[i]));
}
void IntSet::put(int n)
{
	if (n >= 0)
		pos.store(n);
	else
		neg.store(abs(n));
}
bool IntSet::find(int n) const
{
	if (n >= 0)
		return pos.find(n);
	else
		return neg.find(abs(n));
}
void IntSet::print() const
{
	for (int i = neg.getSize() - 1; i > 0; i--)
		if (neg.find(i))
			cout << "-" << i << " ";
	for (int i = 0; i < pos.getSize(); i++)
		if (pos.find(i))
			cout << i << " ";
}
void IntSet::print(ofstream &outfile) const
{
	for (int i = neg.getSize() - 1; i > 0; i--)
		if (neg.find(i))
			outfile << "-" << i << " ";
	for (int i = 0; i < pos.getSize(); i++)
		if (pos.find(i))
			outfile << i << " ";
}
IntSet IntSet::intersect(const IntSet &s) const
{
	IntSet common;
	for (int i = 1 - neg.getSize(); i < int(pos.getSize()); i++)
		if (find(i) && s.find(i))
			common.put(i);
	return common;
}
bool IntSet::belongsTo(const IntSet &s) const
{
	for (int i = 1 - neg.getSize(); i < int(pos.getSize()); i++)
		if (find(i) && !s.find(i))
			return false;
	return true;
}
IntSet &IntSet::operator = (const IntSet &s)
{
	if (this != &s)
	{
		pos = s.pos;
		neg = s.neg;
	}
	return *this;
}