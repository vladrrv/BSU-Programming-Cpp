#include <iostream>
#include <conio.h>
using namespace std;

class A
{
protected:
	unsigned value;
public:
	virtual void set(unsigned) = 0;
	void print()
	{
		cout << endl << value;
	}
	unsigned get()
	{
		return value;
	}
};

class Left : public A
{
public:
	Left()
	{
		value = 0;
	}
	Left(unsigned n)
	{
		value = n;
	}
	void set(unsigned n) override
	{
		if (n > 0 && n < 11)
			value = n;
		else
			cout << "Incorrect value!\n";
	}

};
class Right : public A
{
public:
	Right()
	{
		value = 0;
	}
	Right(unsigned n)
	{
		value = n;
	}
	void set(unsigned n) override
	{
		if (n > 0 && n < 11)
			value = n;
		else
			cout << "Incorrect value!\n";
	}
};

A** randPtrArr(unsigned size)
{
	A** arr = new A*[size];
	for (int i = 0; i < size; i++)
	{
		if (rand() % 1)
			arr[i] = new Left(rand() % 10 + 1);
		else
			arr[i] = new Right(rand() % 10 + 1);
	}
	return arr;
}

void main()
{
	A** arr = randPtrArr(10);
	for (int i = 0; i < 10; i++)
		arr[i]->print();
	int k = 0;
	for (int i = 0; i < 10; i++)
		for (int j = i + 1; j < 10; j++)
			if (arr[i]->get() == arr[j]->get())
				k++;
	cout << "\nK = " << k;
	_getch();
}