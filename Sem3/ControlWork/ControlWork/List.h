#pragma once
#include <iostream>
#include <initializer_list>
#include <windows.h>
#include <windowsx.h>
using namespace std;

template<class T>
struct Node
{
	T data;
	Node<T>* next;
};

template<class T> class List;

template<class T>
class ListIterator
{
	Node<T> *_ptr;

public:
	ListIterator()
	{
		_ptr = NULL;
	}
	ListIterator(Node<T> *p)
	{
		_ptr = p;
	}
	ListIterator(const ListIterator<T>& c)
	{
		_ptr = c._ptr;
	}
	ListIterator<T>& operator ++ ()
	{
		Node<T>* temp = _ptr;
		_ptr = _ptr->next;
		return ListIterator(temp);
	}
	ListIterator<T>& operator ++ (int)
	{
		if (_ptr != 0)
			_ptr = _ptr->next;
		return *this;
	}
	T& operator * () const
	{
		return _ptr->data;
	}
	Node<T>* operator -> () const
	{
		return &(_ptr->data);
	}
	bool operator != (const ListIterator<T>& it)
	{
		return _ptr != it._ptr;
	}

	Node<T> *getPtr()
	{
		return _ptr;
	}
};


template<class T>
class ListVisitor
{
public:
	virtual void visit(List<T>&) = 0;
};
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
template<class T>
class GetMin : public ListVisitor<T>
{
	T val;
public:
	void visit(List<T>& s) override
	{
		if (s.size() > 0)
		{
			val = *(s.begin());
			for (auto el : s)
				val = MIN(el, val);
		}
	}
	T value()
	{
		return val;
	}
};
template<class T>
class GetMax : public ListVisitor<T>
{
	T val;
public:
	void visit(List<T>& s) override
	{
		if (s.size() > 0)
		{
			val = *(s.begin());
			for (auto el : s)
				val = MAX(el, val);
		}
	}
	T value()
	{
		return val;
	}
};
template<class T>
class GetString : public ListVisitor<T>
{
	string val;
public:
	void visit(List<T>& s) override
	{
		for (auto el : s)
			val += (to_string(el) + ", ");
		if (val.size() > 1) val.erase(val.size() - 2);
	}
	string value()
	{
		return val;
	}
};


template<class T>
class List
{
	Node<T> *_top;
	Node<T> *_last;
	size_t _size;
public:
	typedef ListIterator<T> iterator;

	void accept(ListVisitor<T>& v)
	{
		v.visit(*this);
	}

	List() :  _size(0)
	{
		_top = 0;
		_last = 0;
	}
	List(const List<T>& s)
	{
		copy_internals(s);
	}
	List(List<T>&& s)
	{
		copy_internals(s);
		s.clear();
	}
	List(initializer_list<T> l) :  _size(0)
	{
		for (const T& el : l)
			push_front(el);
	}
	~List()
	{
		clear();
	}
	iterator begin() const
	{
		return iterator(_top);
	}
	iterator end() const
	{
		return iterator(0);
	}
	void clear()
	{
		for (size_t i = 0; i < _size; i++)
		{
			pop_front();
		}
	}
	size_t size() const
	{
		return _size;
	}
	iterator push_front(const T& item)
	{
		Node<T> *temp = new Node<T>;
		temp->data = item;
		temp->next = 0;
		if (_size > 0)
			_last->next = temp;
		else
			_top = temp;
		_last = temp;
		_size++;
		return iterator(_last);
	}
	T pop_front()
	{
		if (_size != 0)
		{
			T el = _top->data;
			_size--;
			Node<T> *temp = 0;
			temp = _top->next;
			delete _top;
			_top = temp;
			if (_size == 0)
			{
				_top = 0;
				_last = 0;
			}
			return el;
		}
		else
			throw string("Empty List!");
		return T();
	}
	T pop_back()
	{
		if (_size != 0)
		{
			T el = _last->data;
			iterator it = begin();
			for (size_t i = 0; i < _size-2; i++)
			{
				it++;
			}
			Node<T> *temp = it.getPtr();
			temp->next = 0;
			if (_last != 0)
			{
				delete _last;
				_size--;
				_last = temp;
			}
			if (_size == 0)
			{
				_top = 0;
				_last = 0;
			}
			return el;
		}
		else
			throw string("Empty List!");
		return T();
	}
	List<T>& operator = (const List<T>& s)
	{
		if (&s != this)
		{
			copy_internals(s);
		}
		return *this;
	}
	List<T>& operator = (List<T>&& s)
	{
		if (&s != this)
		{
			copy_internals(s);
			s.clear();
		}
		return *this;
	}
	bool operator == (const List<T>& s) const
	{
		return (!memcmp(_top, s._top, sizeof(T) * _size));
	}
	bool operator != (const List<T>& s) const
	{
		return !(*this == s);
	}
private:
	void copy_internals(const List<T>& s)
	{
		clear();
		for (auto el : s)
			push_front(el);
	}
};


template<class T>
istream& operator >> (istream& is, List<T>& s)
{
	T el;
	is >> el;
	s.push_front(el);
	return is;
}
template<class T>
ostream& operator << (ostream& os, const List<T>& s)
{
	for (auto el : s)
		os << el << ", ";
	return os;
}