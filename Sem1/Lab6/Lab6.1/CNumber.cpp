#include "CNumber.h"
#include <iostream>
using namespace std;

CNumber::CNumber()
{
	re = 0;
	im = 0;
	mod = 0;
}
CNumber::CNumber(const CNumber &z)
{
	re = z.re;
	im = z.im;
	mod = z.mod;
}
CNumber::CNumber(double r, double i)
{
	re = r;
	im = i;
	mod = sqrt(r*r + i*i);
}
CNumber CNumber::operator + (const CNumber &z) const
{
	return CNumber(re + z.re, im + z.im);
}
CNumber CNumber::operator - (const CNumber &z) const
{
	return CNumber(re - z.re, im - z.im);
}
CNumber CNumber::operator * (const CNumber &z) const
{
	return CNumber(re*z.re - im*z.im, re*z.im + im*z.re);
}
CNumber CNumber::operator / (const CNumber &z) const
{
	return CNumber((re*z.re + im*z.im) / (z.re*z.re + z.im*z.im), (im*z.re - re*z.im) / (z.re*z.re + z.im*z.im));
}
bool CNumber::operator == (const CNumber &z) const
{
	return (mod == z.mod);
}
bool CNumber::operator >= (const CNumber &z) const
{
	return (mod >= z.mod);
}
bool CNumber::operator <= (const CNumber &z) const
{
	return (mod <= z.mod);
}
bool CNumber::operator > (const CNumber &z) const
{
	return (mod > z.mod);
}
bool CNumber::operator < (const CNumber &z) const
{
	return (mod < z.mod);
}
void CNumber::printAlg()
{
	cout << re << " + " << im << "i";
}
void CNumber::printDot()
{
	cout << "(" << re << ", " << im << ")";
}