#include <iostream>
#include <conio.h>
using namespace std;

struct Stack
{
	char value;
	Stack *next;
};

void push(Stack *&top, char val)
{
	Stack *newEl = new Stack;
	newEl->value = val;
	newEl->next = top;
	top = newEl;
}

char pop(Stack *&top)
{
	if (top != NULL)
	{
		char val = top->value;
		top = top->next;
		return val;
	}
	else
		return 0;
}

bool check(char *str)
{
	Stack *top = new Stack;
	top = NULL;
	for (int i = 0; i < strlen(str); i++)
	{
		switch (str[i])
		{
		case ('('): push(top, str[i]); break;
		case (')'): if (pop(top) != '(') return false;
					else break;
		case ('['): push(top, str[i]); break;
		case (']'): if (pop(top) != '[') return false;
					else break;
		case ('{'): push(top, str[i]); break;
		case ('}'): if (pop(top) != '{') return false;
					else break;
		}
	}
	if (top == NULL)
		return true;
	else
		return false;
}

void assert(char *str, bool f)
{
	if (check(str) == f)
		cout << "\nCorrect\n\n";
	else
		cout << "\nIncorrect\n\n";
}

void main()
{
	char t1[] = "(2+[4])";
	assert(t1, true);
	char t2[] = "(bla{}blabla)bla(bla[bla]bla)";
	assert(t2, true);
	char t3[] = "{-(+5)[-6]+3}-1";
	assert(t3, true);
	char t4[] = "((x){[y]-40";
	assert(t4, false);
	char t5[] = "1+{(4(}[]))+5";
	assert(t5, false);
	_getch();
}