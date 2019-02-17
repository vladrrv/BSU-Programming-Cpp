#pragma once
#include <iostream>
#include <initializer_list>
#include <utility>
#include <windows.h>
#include <windowsx.h>
using namespace std;


template<class T> class KSet;


template<class T>
struct Node
{
	T data;
	Node<T>* root;
	Node<T>* left;
	Node<T>* right;
};

template<class T>
class KSetIterator
{
	Node<T>* current_node;

	Node<T>* next()
	{
		Node<T>* rchild, *r = NULL, *node = current_node;
		if (node != NULL)
			rchild = node->right;
		else
			return NULL;

		while (rchild != NULL)
		{
			r = rchild;
			rchild = rchild->left;
		}
		if (r == NULL)
		{
			while (node != NULL)
			{
				if (node->root != NULL && node == (node->root)->left)
					return node->root;
				else if (node->root == NULL)
					return NULL;
				else
					node = node->root;
			}
		}
		else
			return r;
	}
	Node<T>* prev(Node<T>* nd)
	{
		return 0;
	}
public:
	KSetIterator()
	{
		current_node = NULL;
	}
	KSetIterator(Node<T>* nd)
	{
		current_node = nd;
	}
	KSetIterator(const KSetIterator<T>& c)
	{
		current_node = c.current_node;
	}
	KSetIterator<T>& operator ++ ()
	{
		current_node = next();
		return *this;
	}
	KSetIterator<T>& operator ++ (int)
	{
		current_node = next();
		return *this;
	}
	T& operator * () const
	{
		return current_node->data;
	}
	T* operator -> () const
	{
		return &(current_node->data);
	}
	bool operator == (const KSetIterator<T>& it)
	{
		return current_node == it.current_node;
	}
	bool operator != (const KSetIterator<T>& it)
	{
		return current_node != it.current_node;
	}
};



template<class T>
class KSetVisitor
{
public:
	virtual void visit(KSet<T>&) = 0;
};

template<class T>
class GetSum : public KSetVisitor<T>
{
	T val;
public:
	void visit(KSet<T>& s) override
	{
		val = T();
		for (auto el : s)
			val += el;
	}
	T value()
	{
		return val;
	}
};



//Based on binary search tree
template<class T>
class KSet
{
	Node<T>* top;
	unsigned int _size;
public:
	typedef KSetIterator<T> iterator;

	void accept(KSetVisitor<T>& v)
	{
		v.visit(*this);
	}

	KSet() : top(NULL), _size(0)
	{ }
	KSet(const KSet<T>& s) : top(NULL), _size(0)
	{
		node_copy(s.top);
	}
	KSet(KSet<T>&& s) : top(NULL), _size(0)
	{
		node_copy(s.top);
		if (s.top)
			s.clear();
	}
	KSet(initializer_list<T> l) : top(NULL), _size(0)
	{
		for (const T& el : l)
			insert(el);
	}
	~KSet()
	{
		node_remove(top);
	}
	iterator begin() const
	{
		Node<T>* ptr = top;
		while (ptr && ptr->left)
			ptr = ptr->left;
		return iterator(ptr);
	}
	iterator end() const
	{
		return iterator(NULL);
	}
	void clear()
	{
		node_remove(top);
		top = NULL;
	}
	unsigned int size() const
	{
		return _size;
	}
	pair<iterator, bool> insert(const T& item)
	{
		return node_add(top, item);
	}
	bool find(const T& item) const
	{
		return node_search(top, item);
	}
	void swap(KSet<T>& s)
	{
		if (this != &s)
		{
			KSet<T>* newset = new KSet<T>(*this);
			operator=(s);
			s = *newset;
			delete newset;
		}
	}
	template <class... Args>
	pair<iterator, bool> emplace(Args... args)
	{
		T el{ args... };
		return node_add(top, el);
	}
		
	KSet<T>& operator [] (const KSet<T>& s)
	{
		return operator*(s);
	}
	KSet<T>& operator [] (const T& s)
	{
		return operator*(KSet<T>{s});
	}
	KSet<T>& operator = (const KSet<T>& s)
	{
		if (&s != this)
		{
			clear();
			node_copy(s.top);
		}
		return *this;
	}
	KSet<T>& operator = (KSet<T>&& s)
	{
		if (&s != this)
		{
			clear();
			node_copy(s.top);
			s.clear();
		}
		return *this;
	}
	KSet<T>& operator + (const KSet<T>& s) const
	{
		KSet<T>* newset = new KSet<T>(*this);
		newset->node_copy(s.top);
		return *newset;
	}
	KSet<T>& operator * (const KSet<T>& s) const
	{
		KSet<T>* newset = new KSet<T>();
		for (const T& el : *this)
			if (s.find(el))
				newset->insert(el);
		return *newset;
	}
	KSet<T>& operator / (const KSet<T>& s) const
	{
		KSet<T>* newset = new KSet<T>();
		for (const T& el : *this)
			if (!s.find(el))
				newset->insert(el);
		return *newset;
	}
	KSet<T>& operator - (const KSet<T>& s) const
	{
		KSet<T>* newset = new KSet<T>();
		*newset = operator/(s) + s.operator/(*this);
		return *newset;
	}
	bool operator >= (const KSet<T>& s) const
	{
		for (T el : s)
			if (!find(el))
				return false;
		return true;
	}
	bool operator <= (const KSet<T>& s) const
	{
		for (T el : *this)
			if (!s.find(el))
				return false;
		return true;
	}
	bool operator == (const KSet<T>& s) const
	{
		return (*this >= s && *this <= s);
	}
	bool operator != (const KSet<T>& s) const
	{
		return !(*this == s);
	}
	bool operator > (const KSet<T>& s) const
	{
		return operator>=(s) && operator!=(s);
	}
	bool operator < (const KSet<T>& s) const
	{
		return operator<=(s) && operator!=(s);
	}

private:
	void node_remove(Node<T>* ptr)
	{
		if (ptr)
		{
			node_remove(ptr->left);
			node_remove(ptr->right);
			delete ptr;
			_size--;
		}
	}
	void node_copy(Node<T>* ptr)
	{
		if (ptr)
		{
			insert(ptr->data);
			node_copy(ptr->left);
			node_copy(ptr->right);
		}
	}
	pair<iterator, bool> node_add(Node<T>*& subtop, const T& item)
	{
		if (!subtop)
		{
			Node<T>* new_node = new Node<T>{ item, NULL, NULL, NULL };
			subtop = new_node;
			_size++;
			return pair<iterator, bool>(iterator(new_node), true);
		}
		if (item < subtop->data)
		{
			if (subtop->left == NULL)
			{
				Node<T>* new_node = new Node<T>{ item, subtop, NULL, NULL };
				subtop->left = new_node;
				_size++;
				return pair<iterator, bool>(iterator(new_node), true);
			}
			else
				return node_add(subtop->left, item);
		}
		else if (item > subtop->data)
		{
			if (subtop->right == NULL)
			{
				Node<T>* new_node = new Node<T>{ item, subtop, NULL, NULL };
				subtop->right = new_node;
				_size++;
				return pair<iterator, bool>(iterator(new_node), true);
			}
			else
				return node_add(subtop->right, item);
		}
		else
			return pair<iterator, bool>(iterator(subtop), false);
	}
	bool node_search(Node<T>* subtop, const T& item) const
	{
		if (!subtop)
			return false;

		if (item < subtop->data)
			return node_search(subtop->left, item);		
		else if (item > subtop->data)
			return node_search(subtop->right, item);
		else
			return true;
	}
};



template<class T>
istream& operator >> (istream& is, KSet<T>& s)
{
	T el;
	is >> el;
	s.insert(el);
	return is;
}
template<class T>
ostream& operator << (ostream& os, const KSet<T>& s)
{
	for (const T& el : s)
		os << el << ", ";
	return os;
}