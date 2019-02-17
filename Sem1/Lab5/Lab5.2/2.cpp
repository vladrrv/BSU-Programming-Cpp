#include <iostream>
#include <conio.h>
using namespace std;

struct Stack
{
	char value[256];
	Stack *next;
};

void push(Stack *&top, char *val)
{
	Stack *newEl = new Stack;
	memcpy(newEl->value, val, strlen(val)+1);
	newEl->next = top;
	top = newEl;
}

char *pop(Stack *&top)
{
	if (top != NULL)
	{
		char val[256];
		memcpy(val, top->value, strlen(top->value)+1);
		top = top->next;
		return val;
	}
	else
		return NULL;
}

int calc(char *str)
{
	Stack *top = NULL;
	Stack *top2 = NULL;
	char buf[256], numbuf[256];
	for (int i = 0; i < strlen(str); i++)
	{
		int a = 0, b = 0; 
		for (a = 0; isalpha(str[i]); a++)
			buf[a] = str[i++];
		buf[a] = 0;
		if (a > 0)
			push(top, buf);
		for (b = 0; isdigit(str[i]); b++)
			numbuf[b] = str[i++];
		numbuf[b] = 0;
		if (b > 0)
			push(top, numbuf);
	}
	
	char x[256], y[256];
	while (top != NULL)
	{
		if (strcmp(top->value, "min") == 0)
		{
			memcpy(x, pop(top2), 256);
			memcpy(y, pop(top2), 256);
			push(top2, (atoi(x) < atoi(y)) ? x : y);
			pop(top);
		}
		else if (strcmp(top->value, "max") == 0)
		{
			memcpy(x, pop(top2), 256);
			memcpy(y, pop(top2), 256);
			push(top2, (atoi(x) > atoi(y)) ? x : y);
			pop(top);
		}
		else
			push(top2, pop(top));
	}
	
	return atoi(pop(top2));
} 

void assert(char *str, int r)
{
	if (calc(str) == r)
		cout << "\nCorrect\n\n";
	else
		cout << "\nIncorrect\n\n";
}

void main()
{
	char t1[] = "min(2,5)";
	assert(t1, 2);
	char t2[] = "max(min(10,6),4)";
	assert(t2, 6);
	char t3[] = "88";
	assert(t3, 88);
	char t4[] = "max(min(max(100,65),103),max(40,32))";
	assert(t4, 100);
	char t5[] = "min(max(min(33,55),min(40,86)),max(min(89,101),max(88,86)))";
	assert(t5, 40);
	_getch();
}