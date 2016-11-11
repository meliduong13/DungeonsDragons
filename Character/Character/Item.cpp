#pragma once
#include "Item.h"
#include <iostream>
#include <time.h>
//! @file 
//! @brief Implementation file for the Item class  
//!


int Item::ID = 0;

Item::Item()
{
	type = "noname";//ex helmet, belt, etc
	thisId = ++ID;
	cout << "default contructor  id is " << thisId << endl;
	createAbilityVector();
	enchantedBonus = randomGen(1, 5);
}


//! default constructor
Item::Item(string atype)
{
	type = atype;//ex helmet, belt, etc
	thisId = ++ID;
	cout << "contructor taking a name-> the id of Item "<< atype << " is " << thisId<<endl;
	createAbilityVector();
	enchantedBonus = randomGen(1, 5);
	chosenAbility();
}

void Item::createAbilityVector()
{
	if (type == "Helmet"){
		cout << "Helmet Created"<<endl;
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

	else if (type == "Weapon"){
		cout << "Weapon Created" << endl;
		abilityVector.push_back("AttackBonus");
		abilityVector.push_back("DamageBonus");
	}
	else;

}

//!this function generates randomly the ability to be enchanted
//!it is chosen amongst the ability vector list for that item
//the user cannot choose the ability to be enhanced
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

int Item::randomGen(int min, int max)
{
	srand(time(NULL));
	int range = max - min + 1;
	return rand() % range + min;
}