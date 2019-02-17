#include "Worker.h"
#include <fstream>
#include <iostream>
using namespace std;

Worker::Worker()
{}
Worker::Worker(const Worker& o) : id(o.id)
{
	strcpy_s(name, o.name);
}
Worker& Worker::operator = (const Worker& o)
{
	strcpy_s(name, o.name);
	id = o.id;
	return *this;
}
void Worker::printName()
{
	cout << name;
}
void Worker::printID()
{
	cout << id;
}
void Worker::printName(ofstream& outfile)
{
	outfile << name;
}
void Worker::printID(ofstream& outfile)
{
	outfile << id;
}
void Worker::printAll()
{
	cout << "Name: " << name << "   Id: " << id << "   Average salary: " << avg_month();
}
void Worker::printAll(ofstream& outfile)
{
	outfile << "Name: " << name << "   Id: " << id << "   Average salary: " << avg_month();
}
Worker::~Worker()
{
}

