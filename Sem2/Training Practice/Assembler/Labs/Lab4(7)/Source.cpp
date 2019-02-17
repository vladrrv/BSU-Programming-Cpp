#include <iostream>
#include <iomanip>
#include <conio.h>
using namespace std;

struct task2_res
{
	unsigned char start_index;
	unsigned char length;
};
extern "C" int _cdecl task1(int n, unsigned pow);
extern "C" task2_res _cdecl task2(char* seq, int len);

int main()
{
	int n = -2, pow = 9;
	cout << "\n(" << n << ")^" << pow << " = " << task1(n, pow);


	cout << "\n\n--------------------\n";
	char seq[] = "1fgggjkzs13aaaabcgdag";
	task2_res result = task2(seq, strlen(seq));
	cout << seq << " ";

	cout << "\nStart index: " << (int)result.start_index << ", length: " << (int)result.length;
		

	_getch();
}