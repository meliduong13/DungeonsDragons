#pragma once
#include <string>
#include <vector>
#include "Ability.h"
#include "Dice.h"
#include "ItemContainer.h"
using namespace std;

class Character {
protected:
	int rowPos = 0;
	int colPos = 0;
	int level;
	int hitPoints = 0;
	const int maxHitDice = 10;
	char name;
	string characterClass;
	vector <Ability*> abilities;
	ItemContainer *backpack;
	ItemContainer *wornItems;
	ItemContainer *tresureChest;

public:
	Character();
	void calcHitPoints();
	Ability* getAbility(string aName);
	ItemContainer* getWornItemContainer() { return wornItems; }
	//correct the score of AttackBonus, ArmorClass, and DamageBonus
	//according to their function.
	void correctScore();
	void updateAbilities();
	int calculatePB();
	void wearUpdate(string addOrRemove);
	void removeUpdate(Item  *i);
	vector <Ability*> getAbilities(){ return abilities; }
	void printProfile();
	int getRow();
	int getCol();
	void setRow(int rw){ rowPos = rw; }
	void setCol(int col){ colPos = col; }
	void setCoordinates(int row, int col){ rowPos = row, colPos = col; }
	int incrLevel() { return level += 1; }
	int getLevel() { return level; }
};