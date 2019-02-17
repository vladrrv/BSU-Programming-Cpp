#pragma once
#include "Worker.h"

class EmployeeHour : public Worker
{
	double hourly_rate;
public:
	EmployeeHour();
	EmployeeHour(const EmployeeHour&);
	EmployeeHour(unsigned, char*, double);
	double avg_month();
	bool operator > (EmployeeHour&);
	bool operator < (EmployeeHour&);
	EmployeeHour& operator = (const EmployeeHour&);
};
