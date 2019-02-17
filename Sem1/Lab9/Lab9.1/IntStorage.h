class IntStorage
{
	unsigned bitsize;
	unsigned bytesize;
	char *field;
public:
	IntStorage();
	IntStorage(unsigned);
	IntStorage(const IntStorage &);
	unsigned getSize() const;
	void store(unsigned);
	bool find(unsigned) const;
	void remove(unsigned);
	void print() const;
	void changeSize(unsigned);
	IntStorage &operator = (const IntStorage &);
	~IntStorage();
};


