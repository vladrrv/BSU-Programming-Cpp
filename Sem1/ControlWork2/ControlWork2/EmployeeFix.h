#pragma once
#include "Worker.h"

class EmployeeFix : public Worker
{
	double fix_salary;
public:
	EmployeeFix();
	EmployeeFix(const EmployeeFix&);
	EmployeeFix(unsigned, char*, double);
	double avg_month();
	bool operator > (EmployeeFix&);
	bool operator < (EmployeeFix&);
	EmployeeFix& operator = (const EmployeeFix&);
};
