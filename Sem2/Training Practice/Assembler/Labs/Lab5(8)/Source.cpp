#include <iostream>
#include <iomanip>
#include <conio.h>
using namespace std;

extern "C" int _cdecl task1(char* str, int len);
extern "C" bool _cdecl task2(char* str, int slen, char* word, int wlen);

int main()
{
	//task 1
	char str[] = "here are some words";
	int min_wordlength = task1(str, strlen(str));

	cout << "\nMinimal word length: " << min_wordlength;

	cout << "\n\n--------------------\n\n";
	
	//task 2
	char
		str2[] = "some random words the word is here sww",
		word[] = "fj";
	bool contains_word = task2(str2, strlen(str2), word, strlen(word));
	cout << str2;
	if (contains_word)
		cout << "\n\nString contains the word '" << word << "'";
	else
		cout << "\n\nString does not contain the word '" << word << "'";

	_getch();
}