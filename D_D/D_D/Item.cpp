#pragma once
#include "Item.h"
#include <iostream>
#include <time.h>
//! @file 
//! @brief Implementation file for the Item class  
//!


int Item::ID = 0;

//! the default constructor 
Item::Item()
{
	type = "noname";//ex helmet, belt, etc
	thisId = ++ID;
	cout << "default contructor  id is " << thisId << endl;
	createAbilityVector();
	enchantedBonus = randomGen(1, 5);
}


//! Creates a item of a specific type
Item::Item(string atype)
{
	type = atype;//ex helmet, belt, etc
	thisId = ++ID;
	cout << "contructor taking a name-> the id of Item " << atype << " is " << thisId << endl;
	createAbilityVector();
	enchantedBonus = randomGen(1, 5);
	chosenAbility();
}

Item::Item(string type, int id, int enchBonus, string abilityName)
{
	createAbilityVector();
	this->type = type;
	this->thisId = id;
	this->enchantedBonus = enchBonus;
	this->abilityName = abilityName;
	randomStatNum = 0; 
}

//! Creates a ability vector 
void Item::createAbilityVector()
{
	if (type == "Helmet"){
		cout << "Helmet Created" << endl;
		abilityVector.push_back("Intelligence");
		abilityVector.push_back("Wisdom");
		abilityVector.push_back("ArmorClass");
	}

	else if (type == "Armor"){
		cout << "Armor Created" << endl;
		abilityVector.push_back("ArmorClass");
	}
	else if (type == "Shield"){
		cout << "shield Created";
		abilityVector.push_back("ArmorClass");
	}
	else if (type == "Ring"){
		cout << "Ring Created" << endl;
		abilityVector.push_back("ArmorClass");
		abilityVector.push_back("Strength");
		abilityVector.push_back("Constitution");
		abilityVector.push_back("Wisdom");
		abilityVector.push_back("Charisma");
	}
	else if (type == "Belt"){
		cout << "Belt Created" << endl;
		abilityVector.push_back("Constitution");
		abilityVector.push_back("Strength");
	}
	else if (type == "Boots"){
		cout << "Boots Created" << endl;

		abilityVector.push_back("ArmorClass");
		abilityVector.push_back("Dexterity");
	}

	else if (type == "Sword"){
		cout << "Sword Created" << endl;
		abilityVector.push_back("AttackBonus");
		abilityVector.push_back("DamageBonus");
	}
	else;

}

//!this function generates randomly the ability to be enchanted
//!it is chosen amongst the ability vector list for that item
//the user cannot choose the ability to be enhanced
//! @return the ability name
string Item::chosenAbility()
{
	int max = abilityVector.size() - 1;
	int min = 0;
	//	cout << "max is" << max << endl;
	//	cout << "size of influence is" << influence.size() << endl;
	randomStatNum = randomGen(min, max);
	//cout << "----------------------my random chosen number is :" << randomStatNum << endl;
	abilityName = abilityVector.at(randomStatNum);
	//cout << "-------------------------my random ability name:" << abilityName << endl;
	return abilityName;
}

//! Generates a random number
//! @param min: the minimum range of the random number 
//! @param max: the maximum range of the random number 
//! @return a random number 
int Item::randomGen(int min, int max)
{
	srand(time(NULL));
	int range = max - min + 1;
	return rand() % range + min;
}