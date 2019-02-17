#include "Student.h"
#include <iostream>
using namespace std;

Student::Student() : firstname("Noname"), lastname("Noname"), group(0)
{ }
Student::Student(const Student &st)
{
	strcpy_s(firstname, strlen(st.firstname) + 1, st.firstname);
	strcpy_s(lastname, strlen(st.lastname) + 1, st.lastname);
	group = st.group;
}
Student::Student(char *f, char *l, int gr)
{
	int flen = strlen(f) + 1, llen = strlen(l) + 1;
	firstname = new char[flen];
	lastname = new char[llen];
	strcpy_s(firstname, flen, f);
	strcpy_s(lastname, llen, l);
	group = gr;
}
void Student::showInf() const
{
	cout << "\nFirst name:\t" << firstname;
	cout << "\nLast name:\t" << lastname;
	cout << "\nGroup:\t\t" << group;
}
double Student::avrg() const 
{
	return 0;
}
Student::~Student()
{
	delete[] firstname;
	delete[] lastname;
}

StAfterS1::StAfterS1() : Student()
{ }
StAfterS1::StAfterS1(const StAfterS1 &st) : Student(st)
{
	marks1 = new int[4];
	memcpy(marks1, st.marks1, 16);
}
StAfterS1::StAfterS1(char *f, char *l, int gr, int *m) : Student(f, l, gr)
{
	marks1 = new int[4];
	memcpy(marks1, m, 16);
}
void StAfterS1::showInf() const
{
	__super::showInf();
	cout << "\nMarks, 1st session: ";
	for (int i = 0; i < 4; i++)
		cout << marks1[i] << " ";
}
double StAfterS1::avrg() const
{
	double av1 = (double)(marks1[0] + marks1[1] + marks1[2] + marks1[3]) / 4;
	cout << "\nAverage for 1st session: " << av1;
	return av1;
}
StAfterS1::~StAfterS1()
{
	delete[] marks1;
}

StAfterS2::StAfterS2() : StAfterS1()
{ }
StAfterS2::StAfterS2(const StAfterS2 &st) : StAfterS1(st)
{
	marks2 = new int[5];
	memcpy(marks2, st.marks2, 20);
}
StAfterS2::StAfterS2(char *f, char *l, int gr, int *m1, int *m2) : StAfterS1(f, l, gr, m1)
{
	marks2 = new int[5];
	memcpy(marks2, m2, 20);
}
void StAfterS2::showInf() const
{
	__super::showInf();
	cout << "\nMarks, 2nd session: ";
	for (int i = 0; i < 5; i++)
		cout << marks2[i] << " ";
}
double StAfterS2::avrg() const
{
	double 
		av1 = __super::avrg(),
		av2 = (double)(marks2[0] + marks2[1] + marks2[2] + marks2[3] + marks2[4]) / 5,
		total = (av1 + av2) / 2;
	cout << "\nAverage for 2nd session: " << av2;
	cout << "\nTotal average: " << total;
	return total;
}
StAfterS2::~StAfterS2()
{
	delete[] marks2;
}