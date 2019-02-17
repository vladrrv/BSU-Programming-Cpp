#include <iostream>
#include <conio.h>
#include "CNumber.h"
using namespace std;

struct List
{
	CNumber value;
	List *next;
};

class CNStack
{
	List *top;
public:
	CNStack() : top(NULL)
	{ }
	void push(CNumber el)
	{
		List *newEl = new List;
		newEl->value = el;
		newEl->next = top;
		top = newEl;
	}
	CNumber pop()
	{
		if (top != NULL)
		{
			CNumber el = top->value;
			top = top->next;
			return el;
		}
		else cout << "Stack is already empty!\n";
	}
};

void main()
{
	CNStack st;
	CNumber z1(2, 5);
	CNumber z2(5, 3);
	z1.printAlg();
	cout << endl;
	st.push(z1);
	st.push(z2);
	st.pop().printAlg();
	cout << endl;
	st.pop().printDot();
	cout << endl;
	st.pop();
	_getch();
}