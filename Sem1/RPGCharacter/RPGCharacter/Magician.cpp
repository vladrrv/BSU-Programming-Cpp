#include "Magician.h"
#include <iostream>
using namespace std;

Magician::Magician()
{ }
Magician::Magician(race _rc = human, gender _gdr = male) : Character(_rc, _gdr)
{ }
void Magician::setMana(unsigned _mana)
{
	mana = _mana;
}
void Magician::setMaxMana(unsigned _maxmana)
{
	maxmana = _maxmana;
}
void Magician::healthSpell(Character& o, unsigned add_hp)
{
	if (mana >= add_hp * 2)
	{
		unsigned dif = o.getMaxHP() - o.getHP();
		if (dif < add_hp)
			add_hp = dif;
		mana -= add_hp * 2;
		o.setHP(o.getHP() + add_hp);
	}
}
ostream& operator << (ostream& o, const Magician& ch)
{
	char* cndname[] = { "normal", "weak", "sick", "poisoned", "paralized", "dead" };
	char* rcname[] = { "human", "gnome", "elf", "orc", "dragon" };
	char* gdrname[] = { "male", "female" };
	o << "\nName: " << ch.name <<
		"\nRace: " << rcname[ch.rc] <<
		"\nGender: " << gdrname[ch.gdr] <<
		"\nAge: " << ch.age <<
		"\nCondition: " << cndname[ch.cnd] <<
		"\nCan move: " << boolalpha << ch.movable <<
		"\nCan talk: " << ch.talkable <<
		"\nHP: " << ch.hp << "/" << ch.maxhp <<
		"\nXP: " << ch.xp <<
		"\nMana: " << ch.mana << "/" << ch.maxmana;
	return o;
}
