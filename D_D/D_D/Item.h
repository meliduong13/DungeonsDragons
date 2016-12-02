#pragma once
#ifndef Item_h
#define Item_h
#include <string>
#include<vector>
#include "Ability.h"

//! @file 
//! @brief Header file for the Item class  
//!
using namespace std;
class Item
{

	//! class for the implementation of Item wearable by a character
private:
	//Ability chosenAbility;
	int enchantedBonus;
	string type;
	vector<string> abilityVector;
	int randomStatNum;
	static int ID;//shared global ID amongst all created items
	int thisId;
	string abilityName;

public:
	Item();
	Item(string type);
	Item(string type, int id, int enchBonus, string abilityName);
	string getType(){ return type; }
	int getId(){ return thisId; }
	int getEnchBonus() { return enchantedBonus; }
	string getAbilityName(){ return abilityName; }
	void createAbilityVector();
	string chosenAbility();
	int randomGen(int min, int max);

};

#endif


