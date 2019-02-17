#include <conio.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <list>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>
using namespace std;

void generateRandomNums(int how_many)
{
	ofstream file("input.txt");
	for (int i = 0; i < how_many; i++)
		file << ' ' << rand() % 100;
}

int main()
{
	srand(time(NULL));
	generateRandomNums(rand() % 1000);
	ifstream infile("input.txt");
	list<int> lst;
	deque<int> dq;
	vector<int> vct;
	int num;
	while (!infile.eof())
	{
		infile >> num;
		lst.push_back(num);
		dq.push_back(num);
		vct.push_back(num);
	}

	cout << "\n\nEnter a number: ";
	cin >> num;
	int equal2num = count(lst.begin(), lst.end(), num),
		greater = count_if(lst.begin(), lst.end(), [=](int n) { return n > num; }),
		total = lst.size(),
		sum = accumulate(lst.begin(), lst.end(), 0);
	cout << "\nThere are " << equal2num << " numbers in list, equal to " << num
		<< "\nThere are " << greater << " numbers in list, greater than " << num
		<< "\nSum of all numbers: " << sum
		<< "\nTotal numbers: " << total
		<< "\nAverage: " << (double)sum / total;

	cout << "\n\nEnter a number: ";
	cin >> num;
	equal2num = count(dq.begin(), dq.end(), num);
	greater = count_if(dq.begin(), dq.end(), [=](int n) { return n > num; });
	total = dq.size();
	sum = accumulate(dq.begin(), dq.end(), 0);

	cout << "\nThere are " << equal2num << " numbers in deque, equal to " << num
		<< "\nThere are " << greater << " numbers in deque, greater than " << num
		<< "\nSum of all numbers in deque: " << sum
		<< "\nTotal numbers in deque: " << total
		<< "\nAverage in deque: " << (double)sum / total;

	cout << "\n\nEnter a number: ";
	cin >> num;
	equal2num = count(vct.begin(), vct.end(), num);
	greater = count_if(vct.begin(), vct.end(), [=](int n) { return n > num; });
	total = vct.size();
	sum = accumulate(vct.begin(), vct.end(), 0);

	cout << "\nThere are " << equal2num << " numbers in vector, equal to " << num
		<< "\nThere are " << greater << " numbers in vector, greater than " << num
		<< "\nSum of all numbers in vector: " << sum
		<< "\nTotal numbers in vector: " << total
		<< "\nAverage in vector: " << (double)sum / total;

	infile.close();
	_getch();
}