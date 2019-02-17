#include <iostream>
#include <conio.h>
using namespace std;

int priority(char op) 
{
	return
		(op == '+' || op == '-') ? 1 :
		(op == '*' || op == '/') ? 2 :
		0;
}

double process_op(double y, double x, char op)
{
	switch (op) 
	{
	case '+': return x + y;
	case '-': return x - y;
	case '*': return x * y;
	case '/': return x / y;
	}
}

double calc(char *str, int &i)
{
	char ops[256], numbuf[256];
	double nums[256];
	int a = -1, p = -1;
	for (i; i <= strlen(str); i++)
	{
		int b = 0;
		for (b = 0; isdigit(str[i]); b++)
			numbuf[b] = str[i++];
		numbuf[b] = 0;
		if (b > 0)
			nums[++p] = atoi(numbuf);
		//else
			switch (str[i])
			{
			case '(': nums[++p] = calc(str, ++i); break;
			case ')': if (a < 0) { i++; return nums[p]; }
			}
		if (a >= 0 && priority(ops[a]) >= priority(str[i]))
		{
			nums[p] = process_op(nums[p--], nums[p], ops[a--]);
			i--;
		}
		else
			ops[++a] = str[i];
	}
	cout << nums[0];
	return nums[p];
}

void assert(char *str, double r)
{
	int i = 0;
	if (calc(str, i) == r)
		cout << "\nCorrect\n\n";
	else
		cout << "\nIncorrect\n\n";
}

void main()
{
	char t0[] = "7+10";
	assert(t0, 17);
	char t1[] = "1+(2)*3+4/1-65+64/2*2";
	assert(t1, 10);
	char t2[] = "5*(12-3/2+1/2)-8*3";
	assert(t2, 31);
	char t3[] = "(89-(5+(13*1-5)-4))/4";
	assert(t3, 20);
	char t4[] = "5*(7/(16*1-9+7/10-1/2-1/(2+3))+1)*(10-11)";
	assert(t4, -10);
	_getch();
}