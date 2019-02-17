#include "EmployeeHour.h"
#include <iostream>
using namespace std;

EmployeeHour::EmployeeHour() : hourly_rate(0)
{
	id = 0;
	strcpy_s(name, "NoName");
}
EmployeeHour::EmployeeHour(const EmployeeHour& o) : Worker(o)
{
	hourly_rate = o.hourly_rate;
}
EmployeeHour::EmployeeHour(unsigned _id, char* _name, double rate = 0)
{
	id = _id;
	strcpy_s(name, _name);
	hourly_rate = rate;
}
double EmployeeHour::avg_month()
{
	return 20.8 * 8 * hourly_rate;
}
bool EmployeeHour::operator > (EmployeeHour& o)
{
	return avg_month() > o.avg_month();
}
bool EmployeeHour::operator < (EmployeeHour& o)
{
	return avg_month() < o.avg_month();
}
EmployeeHour& EmployeeHour::operator = (const EmployeeHour& o)
{
	strcpy_s(name, o.name);
	id = o.id;
	hourly_rate = o.hourly_rate;
	return *this;
}
