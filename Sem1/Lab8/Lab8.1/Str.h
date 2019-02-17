class Str
{
protected:
	char *value;
	unsigned int len; //includes terminating "\0"
public:
	Str();
	Str(const Str &);
	Str(const char *);
	void clear();
	void print() const;
	int getLength() const;
	void operator = (const Str &);
	virtual void operator += (const Str &);
	bool operator == (const Str &) const;
	bool operator != (const Str &) const;
	virtual bool operator > (const Str &) const;
	virtual bool operator < (const Str &) const;
	~Str();
};

class StrDigits : public Str
{
public:
	StrDigits();
	StrDigits(const StrDigits &);
	StrDigits(const char *);
	StrDigits(int);
	unsigned int getIntValue() const;
	void operator += (const StrDigits &);
	bool operator > (const StrDigits &) const;
	bool operator < (const StrDigits &) const;
	//~StrDigits();
};
