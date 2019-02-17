#pragma once

/*////////////////////////////////////////////////////////
  
					List structure:

+------+    +------+    +------+    +------+    
| tail | -> |      | -> |      | -> |      | -> NULL
+------+    +------+    +------+    +------+    
   ^begin								^end

////////////////////////////////////////////////////////*/


/*	+------------+
	| Node Class |
	+------------+
*/
template<typename T>
struct Node
{
	T info;
	Node *next;
};


/*	+----------------+
	| Iterator Class |
	+----------------+
*/
template<class T>
class iter_list
{
	Node<T>* ptr;
public:

	iter_list(Node<T>* p = NULL)
	{
		ptr = p;
	}
	iter_list<T>& operator = (const iter_list& i)
	{
		ptr = i.ptr;
		return this;
	}
	iter_list<T>& operator ++ (int)
	{
		iter_list<T>* p = new iter_list<T>(this->ptr);
		if (ptr != NULL)
			ptr = ptr->next;
		return *p;
	}
	iter_list<T>& operator ++ ()
	{
		if (ptr != NULL)
			ptr = ptr->next;
		return *this;
	}
	T& operator * (void)
	{
		if (ptr != NULL)
			return ptr->info;
		else
			cerr << "NULL iterator";
	}
};

/*	+-------------------------------+
	| "One-Dimensional Array" Class |
	+-------------------------------+
*/
template<typename T>
class SingleLList
{
	Node<T>* tail;
	unsigned size;
public:
	typedef iter_list<T> _iter;
	SingleLList()
	{
		tail = NULL;
		size = 0;
	}
	SingleLList(const SingleLList<T>& o) : SingleLList()
	{
		*this = o;
	}
	Node<T>* create_Node(T);
	void push_back(T);
	void insert_pos(T, unsigned);
	void push_front(T);
	T pop_back();
	T& get_first() const;
	T& get_pos(unsigned) const;
	unsigned get_size() const;
	void delete_pos(unsigned);
	void sort();
	void search(T) const;
	void update(T, unsigned);
	void reverse();
	void display();
	void erase();
	_iter begin();
	_iter end();
	SingleLList<T>& operator = (const SingleLList<T>&);
	~SingleLList()
	{
		erase();
	}
};

template<typename T>
Node<T> *SingleLList<T>::create_Node(T value)
{
	Node<T> *temp, *s;
	temp = new(Node<T>);
	if (temp == NULL)
	{
		cout << "Memory not allocated " << endl;
		return 0;
	}
	else
	{
		temp->info = value;
		temp->next = NULL;
		return temp;
	}
}
template<typename T>
void SingleLList<T>::push_back(T value)
{
	size++;
	Node<T> *temp, *p;
	temp = create_Node(value);
	if (tail == NULL)
	{
		tail = temp;
		tail->next = NULL;
	}
	else
	{
		p = tail;
		tail = temp;
		tail->next = p;
	}
}
template<typename T>
void SingleLList<T>::push_front(T value)
{
	size++;
	Node<T> *temp, *s;
	temp = create_Node(value);
	s = tail;
	while (s->next != NULL)
		s = s->next;
	temp->next = NULL;
	s->next = temp;

}
template<typename T>
T SingleLList<T>::pop_back()
{
	T val = get_first();
	delete_pos(1);
	return val;
}
template<typename T>
T& SingleLList<T>::get_first() const
{
	return get_pos(1);
}
template<typename T>
T& SingleLList<T>::get_pos(unsigned pos) const
{
	T* def = new T();
	if (tail == NULL)
	{
		cout << "\nList is empty" << endl;
		return *def;
	}
	Node<T> *s, *ptr;
	s = tail;
	if (pos > 0 && pos <= size)
	{
		for (int i = 1; i < pos; i++)
		{
			ptr = s;
			s = s->next;
		}
		return s->info;
	}
	else
	{
		cout << "\nPosition out of range" << endl;
		return *def;
	}
}
template<typename T>
unsigned SingleLList<T>::get_size() const
{
	return size;
}
template<typename T>
void SingleLList<T>::insert_pos(T value, unsigned pos)
{
	size++;
	int counter = 0;
	Node<T> *temp, *s, *ptr;
	temp = create_Node(value);
	if (pos == 1)
	{
		if (tail == NULL)
		{
			tail = temp;
			tail->next = NULL;
		}
		else
		{
			ptr = tail;
			tail = temp;
			tail->next = ptr;
		}
	}
	else if (pos > 1 && pos <= size)
	{
		s = tail;
		for (auto i = 1; i < pos; i++)
		{
			ptr = s;
			s = s->next;
		}
		ptr->next = temp;
		temp->next = s;
	}
	else
	{
		cout << "\nPositon out of range" << endl;
		size--;
	}
}
template<typename T>
void SingleLList<T>::sort()
{
	Node<T> *ptr, *s;
	int value;
	if (tail == NULL)
	{
		cout << "\nList is empty" << endl;
		return;
	}
	ptr = tail;
	while (ptr != NULL)
	{
		for (s = ptr->next; s != NULL; s = s->next)
			if (ptr->info > s->info)
			{
				value = ptr->info;
				ptr->info = s->info;
				s->info = value;
			}
		ptr = ptr->next;
	}
}
template<typename T>
void SingleLList<T>::delete_pos(unsigned pos)
{
	if (tail == NULL)
		return;
	size--;
	Node<T> *s = tail, *ptr = new Node<T>;
	if (pos == 1)
		tail = s->next;
	else
	{
		if (pos <= size)
		{
			for (unsigned i = 1; i < pos; i++)
			{
				ptr = s;
				s = s->next;
			}
			ptr->next = s->next;
		}
		else
		{
			cout << "\nPosition out of range" << endl;
			size++;
		}
	}
    free(s);
}
template<typename T>
void SingleLList<T>::update(T value, unsigned pos)
{
	if (tail == NULL)
	{
		cout << "\nList is empty" << endl;
		return;
	}
	Node<T> *s, *ptr;
	s = tail;
	if (pos == 1)
		tail->info = value;
	else
	{
		for (auto i = 0; i < pos - 1; i++)
		{
			if (s == NULL)
			{
				cout << "\nThere are less than " << pos << " elements";
				return;
			}
			s = s->next;
		}
		s->info = value;
	}
}
template<typename T>
void SingleLList<T>::search(T value) const
{
	int pos = 0;
	bool flag = false;
	if (tail == NULL)
	{
		cout << "\nList is empty" << endl;
		return;
	}
	Node<T> *s;
	s = tail;
	while (s != NULL)
	{
		pos++;
		if (s->info == value)
		{
			flag = true;
			cout << "\nElement " << value << " is found at position " << pos << endl;
		}
		s = s->next;
	}
	if (!flag)
		cout << "\nElement " << value << " not found in the list" << endl;
}
template<typename T>
void SingleLList<T>::reverse()
{
	Node<T> *ptr1, *ptr2, *ptr3;
	if (tail == NULL)
		return;
	if (tail->next == NULL)
		return;
	ptr1 = tail;
	ptr2 = ptr1->next;
	ptr3 = ptr2->next;
	ptr1->next = NULL;
	ptr2->next = ptr1;
	while (ptr3 != NULL)
	{
		ptr1 = ptr2;
		ptr2 = ptr3;
		ptr3 = ptr3->next;
		ptr2->next = ptr1;
	}
	tail = ptr2;
}
template<typename T>
void SingleLList<T>::display()
{
	Node<T> *temp;
	if (tail == NULL)
	{
		cout << "\nList is empty" << endl;
		return;
	}
	temp = tail;
	cout << "\nElements of list are: " << endl;
	while (temp != NULL)
	{
		cout << temp->info << " ";
		temp = temp->next;
	}
}
template<typename T>
void SingleLList<T>::erase()
{
	while (tail != NULL)
		delete_pos(1);
}
template<typename T>
iter_list<T> SingleLList<T>::end()
{
	Node<T>* s = tail;
	for (unsigned i = 1; i < get_size(); i++)
		s = s->next;
	return iter_list<T>(s);
}
template<typename T>
iter_list<T> SingleLList<T>::begin()
{
	return iter_list<T>(tail);
}
template<typename T>
SingleLList<T>& SingleLList<T>::operator = (const SingleLList<T>& o)
{
	erase();
	Node<T> *s, *ptr;
	s = o.tail;
	for (unsigned i = 1; i <= o.get_size(); i++)
	{
		push_back(s->info);
		s = s->next;
	}
	return *this;
}
