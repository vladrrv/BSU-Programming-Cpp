#include "Magician.h"
#include <iostream>
#include <conio.h>
using namespace std;
template<class T>
T& CharGenerator(char* name)
{

	T ch(race[rand() % 5], gender[rand() % 2]);
	ch.setName(name);
	ch.setAge(rand() % 50);
	ch.setCondition(normal);
	ch.setMovability(true);
	ch.setTalkability(true);
	ch.setXP(rand() % 500);
	ch.setMaxHP(rand() % 100);
	ch.setHP(rand() % 90 + 10);

	if (typeid(ch) == typeid(Magician))
	{
		ch.setMaxMana(rand() % 1000);
		ch.setMana(rand() % 900 + 100);
	}
	return ch;
};

void main(char* args)
{
	Magician ch;
	Character ch2(elf, female);
	ch2.setName("ee");
	ch2.setAge(50);
	ch2.setCondition(normal);
	ch2.setMovability(true);
	ch2.setTalkability(true);
	ch2.setXP(10);
	ch2.setMaxHP(100);
	ch2.setHP(0);

	ch.setName("somename");
	ch.setAge(35);
	ch.setCondition(normal);
	ch.setMovability(true);
	ch.setTalkability(false);
	ch.setXP(315);
	ch.setMaxHP(100);
	ch.setHP(65);
	ch.setMaxMana(1000);
	ch.setMana(135);

	cout << ch2;

	ch.healthSpell(ch2, 60);
	cout << ch2;
	cout << ch;
	_getch();
}