#pragma once
#include <fstream>
class Worker
{
protected:
	char name[256];
	unsigned id;
public:
	Worker();
	Worker(const Worker&);
	virtual double avg_month() = 0;
	Worker& operator = (const Worker&);
	void printName();
	void printID();
	void printName(std::ofstream&);
	void printID(std::ofstream&);
	void printAll();
	void printAll(std::ofstream&);
	~Worker();
};

