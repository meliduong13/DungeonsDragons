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
	string characterType = "friendly"; // (friendly/hostile) :: By default friendly 
	string characterClass = "fighter";
	
	vector <int> attackBonus;//Added from a3
	vector <Ability*> abilities;
	


public:
	Character(string characterType, string characterClass, ItemContainer* backpack, ItemContainer* wornItems, ItemContainer* treasureChest, vector<Ability*> abilities, int damageBonus, 
		int nbrOfAttacks, int armorClass, int hitPoints, int level, int colPos, int rowPos);
	Character();
	void setHitPoints(int level);
	Ability* getAbility(string aName);
	ItemContainer* getWornItemContainer() { return wornItems; }
	void updateAbilities();
	int calculatePB();
	void wearUpdate(string addOrRemove);
	void removeUpdate(Item  *i);
	vector <Ability*> getAbilities(){ return abilities; }
	void printProfile();
	int getRow() { return rowPos; };
	int getCol() { return colPos; };
	ItemContainer *backpack;
	ItemContainer *wornItems;
	ItemContainer *tresureChest;
	void setRow(int rw){ rowPos = rw; }
	void setCol(int col){ colPos = col; }
	void setCoordinates(int row, int col){ rowPos = row, colPos = col; }
	int incrLevel() { return level += 1; }
	std::string getCharacterType() { return characterType; }
	std::string getCharacterClass() { return characterClass; }
	void setLevel(int alevel) { level = alevel; } //Added from a3
	int getLevel() { return level; } //Added from a3
	int getHitPoints() { return hitPoints; } //Added from a3
	vector <int> getAttackBonus() { return attackBonus; } //Added from a3
	void setAttackBonus(int level); //Added from a3
	void Character::setNbrOfAttacks(int level); //Added from a3
	void setArmorClass(); //Added from a3
	void setDamageBonus(); //Added from a3
	void setCharacterType(string chType){ //Added from a3
		if (chType == "enemy") {
			characterType = chType;
		} else {} //do nothing because it is already set by default friendly
	}//Added from a3
	void setWornItems(); //Added from a3
	void setBackPack(); //Added from a3
	void setTreasureChest(); //Added from a3
	void setAbilities(); //Added from a3
	int armorClass = 0; //Added from a3
	int damageBonus = 0; //Added from a3
	int nbrOfAttacks = 0; //Added from a3
}; 