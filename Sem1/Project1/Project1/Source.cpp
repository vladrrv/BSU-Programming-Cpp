#include <iostream>
#include <vector>
#include <conio.h>
using namespace std;

//class MyManip
//{
//public:
//	int m;
//	int n;
//	ostream& (*f)(ostream&, int, int);
//	MyManip(ostream& (*F)(ostream&, int, int), int M, int N) : f(F), m(M), n(N)
//	{ }
//};
//
//ostream& operator << (ostream& o, MyManip mm)
//{
//	return mm.f(o, mm.m, mm.n);
//}
//
//ostream& format(ostream& o, int m, int n)
//{
//	o.width(m);
//	o.fill('e');
//	o.precision(n);
//	return o;
//}
//MyManip fMM(int m, int n)
//{
//	return MyManip(format, m, n);
//}
//// Consider an actual class.
//class Obj {
//	static int i, j;
//
//public:
//	void f() const { cout << i++ << endl; }
//	void g() const { cout << j++ << endl; }
//};
//
//// Static member definitions:
//int Obj::i = 10;
//int Obj::j = 12;
//
//// Implement a container for the above class
//class ObjContainer {
//	vector<Obj*> a;
//public:
//	void add(Obj* obj) {
//		a.push_back(obj);  // call vector's standard method.
//	}
//	friend class SmartPointer;
//};
//
//// implement smart pointer to access member of Obj class.
//class SmartPointer {
//	ObjContainer oc;
//	int index;
//public:
//	SmartPointer(ObjContainer& objc) {
//		oc = objc;
//		index = 0;
//	}
//
//	// Return value indicates end of list:
//	bool operator++() // Prefix version 
//	{
//		if (index >= oc.a.size()) return false;
//		if (oc.a[++index] == 0) return false;
//		return true;
//	}
//
//	bool operator++(int) // Postfix version 
//	{
//		return operator++();
//	}
//
//	// overload operator->
//	Obj* operator->() const {
//		if (!oc.a[index]) {
//			cout << "Zero value";
//			return (Obj*)0;
//		}
//		return oc.a[index];
//	}
//};
//
//
//
//void main() {
//	const int sz = 10;
//	Obj o[sz];
//	ObjContainer oc;
//	for (int i = 0; i < sz; i++) {
//		oc.add(&o[i]);
//	}
//
//	SmartPointer sp(oc); // Create an iterator
//	do {
//		sp->f(); // smart pointer call
//		sp->g();
//	} while (sp++);
//	cout << fMM(10,5) << 5.0123456789;
//	_getch();
//}

class Base
{
	virtual void m()
	{

	}
};
class Derv : public Base
{
	void m()
	{

	}
};



template<const class T>
T min(T a, T b)
{
	return (a > b) ? b : a;
}

template<class U, class V>
void a(U x, V y)
{
	cout << x << " " << y;
}
void main() 
{
	a<double, double>(52, 42);
	const int a = 0, b = 2;
	min(a, b);
	Base* obj = new Derv;
	

	_getch();
}