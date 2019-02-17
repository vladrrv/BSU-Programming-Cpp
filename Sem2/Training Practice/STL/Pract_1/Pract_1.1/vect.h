#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

template <class T> 
class vector
{
protected:
	T* p;                      //base pointer
	int size;                  //number of elements
public:
	typedef T* iterator;
	explicit vector(int n = 100); //create a size n array
	vector(const vector<T>& v); //copy vector
	vector(const T* a, int n); //copy an array
	~vector() { delete[]p; }
	iterator begin() { return p; }
	iterator end() { return p + size; }
	vector<T>& operator=(const vector<T>& v);

};

template <class T>
vector<T>::vector(int n) : size(n)
{
	assert(n > 0);       
	p = new T[size];       
	assert(p != 0);
}
template <class T>
vector<T>::vector(const T* a, int n)
{
	assert(n > 0);       
	size = n;       
	p = new T[size];
	assert(p != 0);
	for (int i = 0; i < size; ++i)  
		p[i] = a[i];
}
template <class T>
vector<T>::vector(const vector<T>& v)
{
	size = v.size;   
	p = new T[size];   
	assert(p != 0);
	for (int i = 0; i < size; ++i)
		p[i] = v.p[i];
}
template <class T>
vector<T>& vector<T>::operator=(const vector<T>& v)
{
	assert(v.size == size);
	for (int i = 0; i < size; ++i)
		p[i] = v.p[i];
	return *this;
}


template <class T> 
class vectorex : public vector<T>
{
public:
	vectorex(int n = 10) : vector<T>::vector(n)
	{ }
	T& operator[](int i)
	{
		assert(i >= 0 && i < size); 
		return (p[i]);
	}
};
