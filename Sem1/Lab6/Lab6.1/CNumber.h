class CNumber
{
	double re;
	double im;
	double mod;
public:
	CNumber();
	CNumber(const CNumber &);
	CNumber(double, double);
	CNumber operator + (const CNumber &) const;
	CNumber operator - (const CNumber &) const;
	CNumber operator * (const CNumber &) const;
	CNumber operator / (const CNumber &) const;
	bool operator == (const CNumber &) const;
	bool operator >= (const CNumber &) const;
	bool operator <= (const CNumber &) const;
	bool operator > (const CNumber &) const;
	bool operator < (const CNumber &) const;
	void printAlg();
	void printDot();
};