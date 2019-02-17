#include <iostream>
using namespace std;

template<class T>
class MyVector
{
	typedef T* _iterator;
	T* field;
	unsigned count;
	unsigned maxsize;

public:
	MyVector();
	MyVector(const MyVector<T> &);
	MyVector(unsigned, const T&);
	MyVector(_iterator, _iterator);

	T& at(unsigned) const;
	T& front() const;
	T& back() const;
	_iterator begin() const;
	_iterator end() const;
	bool empty() const;
	unsigned size() const;
	unsigned capacity() const;
	void clear();
	void shrink();
	void insert(T, unsigned);
	void push_back(T);
	T pop_back();

	MyVector<T> &operator = (const MyVector<T>&);
	bool operator == (const MyVector<T>&) const;
	T &operator [] (unsigned) const;
	friend ostream& operator << <> (ostream&, const MyVector<T>&);

	~MyVector();
};

template<class T>
MyVector<T>::MyVector()
{
	count = 0;
	maxsize = 1;
	field = new T;
}

template<class T>
MyVector<T>::MyVector(const MyVector<T> &v)
{
	count = v.count;
	maxsize = v.maxsize;
	field = new T[maxsize];
	memcpy(field, v.field, maxsize * sizeof(T));
}

template<class T>
MyVector<T>::MyVector(unsigned n, const T &val = T())
{
	count = n;
	maxsize = n;
	field = new T[maxsize];
	fill_n(field, maxsize, val);
}

template<class T>
MyVector<T>::MyVector(_iterator start, _iterator end) : MyVector()
{
	if (end - start > 0)
	{
		count = end - start;
		maxsize = count;
		field = new T[maxsize];
		memcpy(field, start, maxsize * sizeof(T));
	}
	else
		cerr << "\nIncorrect iterators passed to constructor!";
}

template<class T>
T& MyVector<T>::at(unsigned pos) const
{
	if (pos >= count)
	{
		cerr << "\nOut of range! Returned reference to last position";
		return field[maxsize - 1];
	}
	return field[pos];
}

template<class T>
T& MyVector<T>::front() const
{
	return field[0];
}

template<class T>
T& MyVector<T>::back() const
{
	return field[count - 1];
}

template<class T>
typename MyVector<T>::_iterator MyVector<T>::begin() const
{
	return &field[0];
}

template<class T>
typename MyVector<T>::_iterator MyVector<T>::end() const
{
	return &field[count];
}

template<class T>
bool MyVector<T>::empty() const
{
	return !count;
}

template<class T>
unsigned MyVector<T>::size() const
{
	return count;
}

template<class T>
unsigned MyVector<T>::capacity() const
{
	return maxsize;
}

template<class T>
void MyVector<T>::clear()
{
	fill_n(field, count, T());
	count = 0;
}

template<class T>
void MyVector<T>::shrink()
{
	T *temp = new T[count];
	memcpy(temp, field, count * sizeof(T));
	maxsize = count;
	field = new T[maxsize];
	memcpy(field, temp, maxsize * sizeof(T));
}

template<class T>
void MyVector<T>::insert(T el, unsigned pos)
{
	T *temp = new T[count];
	memcpy(temp, field, count * sizeof(T));
	if (count == maxsize)
	{
		maxsize *= 2;
		field = new T[maxsize];
		memcpy(field, temp, pos * sizeof(T));
	}
	field[pos] = el;
	memcpy(field + pos + 1, temp + pos, (count - pos) * sizeof(T));
	count++;
}

template<class T>
void MyVector<T>::push_back(T el)
{
	insert(el, count);
}

template<class T>
T MyVector<T>::pop_back()
{
	if (count)
	{
		T el = field[--count];
		field[count] = T();
		return el;
	}
	else
	{
		cerr << "\nEmpty vector! Returned default template value";
		return T();
	}
}

template<class T>
MyVector<T>& MyVector<T>::operator = (const MyVector<T> &v)
{
	count = v.count;
	maxsize = v.maxsize;
	memcpy(field, v.field, maxsize * sizeof(T));
	return *this;
}

template<class T>
bool MyVector<T>::operator == (const MyVector<T> &v) const
{
	if (count == v.count)
		return !memcmp(field, v.field, count * sizeof(T));
	else
		return false;
}

template<class T>
T& MyVector<T>::operator [] (unsigned pos) const
{
	return field[pos];
}

template<class T>
ostream& operator << <> (ostream& o, const MyVector<T>& v)
{
	o << "\n ";
	for (int i = 0; i < v.count; i++)
		o << v.field[i] << " ";
	return o;
}

template<class T>
MyVector<T>::~MyVector()
{
	delete[] field;
}