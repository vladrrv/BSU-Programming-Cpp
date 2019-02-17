#pragma once
#include "Character.h"
#include <iostream>
using namespace std;

class Magician : public Character
{
	unsigned mana;
	unsigned maxmana;
public:
	Magician();
	Magician(race, gender);
	void setMana(unsigned);
	void setMaxMana(unsigned);
	void healthSpell(Character&, unsigned);
	friend ostream& operator << (ostream&, const Magician&);
};

