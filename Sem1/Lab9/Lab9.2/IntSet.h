#include "IntStorage.h"
class IntSet
{
	IntStorage pos;
	IntStorage neg;
public:
	IntSet();
	IntSet(int arr[], int count);
	void put(int);
	bool find(int) const;
	void print() const;
	void print(std::ofstream &) const;
	IntSet intersect(const IntSet &) const;
	bool belongsTo(const IntSet &) const;
	IntSet &IntSet::operator = (const IntSet &);
};

