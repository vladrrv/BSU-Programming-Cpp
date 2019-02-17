#include "Character.h"
#include <iostream>
using namespace std;

Character::Character() : rc(human), gdr(male)
{ }
Character::Character(race _rc = human, gender _gdr = male) : rc(_rc), gdr(_gdr)
{
	static int counter = 0;
	id = counter++;
}
char* Character::getName()
{
	return name;
}
condition Character::getCondition() const
{
	return cnd;
}
race Character::getRace() const
{
	return rc;
}
gender Character::getGender() const
{
	return gdr;
}
unsigned Character::getAge() const
{
	return age;
}
bool Character::canMove() const
{
	return movable;
}
bool Character::canTalk() const
{
	return talkable;
}
unsigned Character::getHP() const
{
	return hp;
}
unsigned Character::getMaxHP() const
{
	return maxhp;
}
unsigned Character::getXP() const
{
	return xp;
}

int Character::cmpXP(const Character& o) const
{
	return xp - o.xp;
}
int Character::cmpHP(const Character& o) const
{
	return (hp / maxhp) - (o.hp / o.maxhp);
}

void Character::setName(char* _name)
{
	strcpy_s(name, _name);
}
void Character::setCondition(condition _cnd)
{
	cnd = _cnd;
}
void Character::setAge(unsigned _age)
{
	age = _age;
}
void Character::setMovability(bool f)
{
	if (cnd != paralized && cnd != dead)
		movable = f;
	else
		movable = false;
}
void Character::setTalkability(bool f)
{
	if (cnd != dead)
		talkable = f;
	else
		talkable = false;
}
void Character::setHP(unsigned _hp)
{
	hp = _hp;
	int hp_percentage = hp * 100 / maxhp;
	if (hp_percentage > 10)
		cnd = normal;
	else if (hp_percentage > 0)
		cnd = weak;
	else
	{
		cnd = dead;
		movable = false;
		talkable = false;
	}
}
void Character::setMaxHP(unsigned _maxhp)
{
	maxhp = _maxhp;
}
void Character::setXP(unsigned _xp)
{
	xp = _xp;
}
Character& Character::operator = (const Character& o)
{
	strcpy_s(name, o.name);
	memcpy(&rc, o.rc, 32);
	gdr;
	cnd;
	age;
	movable;
	talkable;
	hp;
	maxhp;
	xp;
}

ostream& operator << (ostream& o, const Character& ch)
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
		"\nXP: " << ch.xp;
	return o;
}
void Character::printID()
{
	cout << id << endl;
}

