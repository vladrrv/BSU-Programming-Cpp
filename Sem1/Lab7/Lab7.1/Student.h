class Student
{
	char *firstname;
	char *lastname;
	int group;
public:
	Student();
	Student(const Student &);
	Student(char *, char *, int);
	virtual void showInf() const;
	virtual double avrg() const;
	~Student();
};

class StAfterS1 : public Student
{
	int *marks1;
public:
	StAfterS1();
	StAfterS1(const StAfterS1 &);
	StAfterS1(char *, char *, int, int *);
	virtual void showInf() const;
	virtual double avrg() const;
	~StAfterS1();
};

class StAfterS2 : public StAfterS1
{
	int *marks2;
public:
	StAfterS2();
	StAfterS2(const StAfterS2 &);
	StAfterS2(char *, char *, int, int *, int *);
	virtual void showInf() const;
	virtual double avrg() const;
	~StAfterS2();
};