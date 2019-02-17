#pragma once
#include <iostream>
using namespace std;

enum condition { normal, weak, sick, poisoned, paralized, dead };
enum race { human, gnome, elf, orc, dragon };
enum gender { male, female };

class Character
{
	int id;
protected:
	char name[256];
	const race rc;
	const gender gdr;
	condition cnd;
	unsigned age;
	bool movable;
	bool talkable;
	unsigned hp;
	unsigned maxhp;
	unsigned xp;
public:
	Character();
	Character(race, gender);

	char* getName();
	condition getCondition() const;
	race getRace() const;
	gender getGender() const;
	unsigned getAge() const;
	bool canMove() const;
	bool canTalk() const;
	unsigned getHP() const;
	unsigned getMaxHP() const;
	unsigned getXP() const;

	int cmpXP(const Character&) const;
	int cmpHP(const Character&) const;

	void setName(char*);
	void setCondition(condition);
	void setAge(unsigned);
	void setMovability(bool);
	void setTalkability(bool);
	void setHP(unsigned);
	void setMaxHP(unsigned);
	void setXP(unsigned);
	Character& operator = (const Character&);
	friend ostream& operator << (ostream&, const Character&);
	void printID();
};
