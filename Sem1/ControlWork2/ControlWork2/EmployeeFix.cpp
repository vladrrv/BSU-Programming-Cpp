#include "EmployeeFix.h"
#include <iostream>
using namespace std;

EmployeeFix::EmployeeFix() : fix_salary(0)
{
	id = 0;
	strcpy_s(name, "NoName");
}
EmployeeFix::EmployeeFix(const EmployeeFix& o) : Worker(o)
{
	fix_salary = o.fix_salary;
}
EmployeeFix::EmployeeFix(unsigned _id, char* _name, double sal = 0)
{
	id = _id;
	strcpy_s(name, _name);
	fix_salary = sal;
}
double EmployeeFix::avg_month()
{
	return fix_salary;
}
bool EmployeeFix::operator > (EmployeeFix& o)
{
	return avg_month() > o.avg_month();
}
bool EmployeeFix::operator < (EmployeeFix& o)
{
	return avg_month() < o.avg_month();
}
EmployeeFix& EmployeeFix::operator = (const EmployeeFix& o)
{
	strcpy_s(name, o.name);
	id = o.id;
	fix_salary = o.fix_salary;
	return *this;
}

