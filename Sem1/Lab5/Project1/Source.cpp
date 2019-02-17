#include <iostream>
#include <conio.h>

using namespace std;

struct Stack
{
	char data[256];
	Stack *next;
};

void push(Stack *&top, char *dat)
{
	Stack *new_data = new Stack;
	memcpy(new_data->data, dat, strlen(dat) + 1);
	new_data->next = top;
	top = new_data;
}

char *pop(Stack *&top)
{
	if (top != NULL)
	{
		char dat[256];
		memcpy(dat, top->data, strlen(top->data) + 1);
		top = top->next;
		return dat;
	}
	else
		return NULL;
}

int formula(char *str)
{
	Stack *top = NULL;
	Stack *top2 = NULL;
	char letter[256], number[256];
	for (int i = 0; i < strlen(str); i++)
	{
		int a = 0, b = 0;
		for (a = 0; isalpha(str[i]); a++)
			letter[a] = str[i++];
		letter[a] = 0;
		if (a > 0)
			push(top, letter);
		for (b = 0; isdigit(str[i]); b++)
			number[b] = str[i++];
		number[b] = 0;
		if (b > 0)
			push(top, number);
	}
	char x[256], y[256];
	while (top != NULL)
	{
		if (strcmp(top->data, "min") == 0)
		{
			strcpy_s(x, 256, pop(top2));
			strcpy_s(y, 256, pop(top2));
			push(top2, (atoi(x) < atoi(y)) ? x : y);
			pop(top);
		}
		else if (strcmp(top->data, "max") == 0)
		{
			strcpy_s(x, 256, pop(top2));
			strcpy_s(y, 256, pop(top2));
			push(top2, (atoi(x) > atoi(y)) ? x : y);
			pop(top);
		}
		else
			push(top2, pop(top));;
	}
	return atoi(pop(top2));
}

void assertion(char *str, int cor)
{
	if (formula(str) == cor)
		cout << "OK" << endl;
	else
		cout << "FAIL" << endl;
}

int main()
{
	char str1[] = "8";
	assertion(str1, 8);
	char str2[] = "max(4,min(3,5))";
	assertion(str2, 4);
	char str3[] = "min(min(3,5),max(2,max(3,4)))";
	assertion(str3, 3);
	char str4[] = "max(min(max(38,59),12),max(33,32))";
	assertion(str4, 33);
	char str5[] = "min(max(min(43,78),min(3,5)),max(min(322,324),311))";
	assertion(str5, 43);
	_getch();
	return 0;
}
