#include <string>
#include "Character.h"
using namespace std;

void Character::setHitPoints(int level) {
	Dice aDice;
	for (int i = 0; i < level; i++){
		hitPoints += aDice.roll("1d10[+" + to_string(getAbility("Constitution")->getModifier()) + "]");
	}
}

Ability* Character::getAbility(string aName) {
	for (int i = 0; i < abilities.size(); i++) {
		if (abilities[i]->getName() == aName)
			return abilities[i];
	}
}

//! according to the items in the wornItems container
//! we update the abilities by calling the function 
//! chosen ability, which randomly chooses the ability to be enchanted
//! The way enchantments work is 
void Character::wearUpdate(string addOrRemove) {
	vector<Item*> bp = wornItems->getItems();
	//cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&BAG TYPE IS: " << wornItems->getType();
	if (wornItems->getType() == "wornItems") {
		//cout << "UPDATING ABILITIES ->Character's container is a wornItem bag" << endl;
		for (int i = 0; i < bp.size(); i++) {
			for (int j = 0; j < abilities.size(); j++)
				if (bp[i]->getAbilityName() == abilities[j]->getName())
				{
				if (addOrRemove == "add") {
					abilities[j]->incScore(bp[i]->getEnchBonus());
				}
				else if (addOrRemove == "remove")  {
					abilities[j]->incScore(-(bp[i]->getEnchBonus()));
				}
				else cout << "WRONG PASSED PARAMETER!";

				abilities[j]->calculateModifier();
				//COUT
				cout << "character's ability: " << abilities[j]->getName() << endl;
				cout << "Score : " << abilities[j]->getScore() << endl;
				cout << "enchanted bonus is : " << bp[i]->getEnchBonus() << endl;
				}//inner if
		}//for
	}//if
}//function

void Character::removeUpdate(Item *item) {
	//int itemPosition = wornItems->getItemPosition(item->getType());
	//vector<Item*> itemList = wornItems->getItems();
	//TESTING Commented Code
	/*for (int i = 0; i < itemList.size(); i++) {
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
	<< " itemList at " << i << " : " << itemList.at(i) << endl;
	}*/
	//TESTING Commented Code
	//itemList.erase(itemList.begin()+itemPosition);
	getAbility(item->getAbilityName())->incScore(-(item->getEnchBonus()));
	getAbility(item->getAbilityName())->calculateModifier();
	//cout << "UPDATING ABILITIES ->update the character's ability" + item->getAbilityName() + " score ";
	//	cout << " of -" + item->getEnchBonus() << endl;
	//cout << " and the final score is " << getAbility(item->getAbilityName())->getScore();
}

//! Calculates the proficiency bonus of the character
//! @return proficiency bonus
int Character::calculatePB() {
	if (1 <= level <= 4)
		return 2;
	if (5 <= level <= 8)
		return 3;
	if (9 <= level <= 12)
		return 4;
	if (13 <= level <= 16)
		return 5;
	if (17 <= level <= 20)
		return 6;
}

//! Prints the profile of the character 
void Character::printProfile(){

	vector<Item*> bp = wornItems->getItems();
	vector<Item*> backpack_bp = backpack->getItems();
	vector<Item*> treasure_bp = tresureChest->getItems();

	cout << "USER PROFILE" << endl;
	cout << "level : " << level << endl;
	cout << "hitPoints : " << hitPoints << endl;
	cout << "maxHitDice : " << maxHitDice << endl;
	//loop through all character's abilities
	for (int i = 0; i < abilities.size(); i++)
	{
		cout << "ability " << abilities[i]->getName() << " score : ";
		cout << abilities[i]->getScore() << " modifier : " << abilities[i]->getModifier() << endl;
	}
	if (bp.size() == 0)
	{
		cout << "*********************EMPTY WORN ITEM*******************" << endl;
		cout << "*********************END OF EMPTY WORN ITEM*******************" << endl;
	}

	else
	{
		cout << "**********************EMPTY WORN ITEM****************" << endl;
		//loop through all items of wornItems itemContainer
		for (int i = 0; i < bp.size(); i++)
		{
			cout << "ID : " << bp[i]->getId() << endl;
			cout << "item type (name) : " << bp[i]->getType() << endl;
			cout << "chosen ability toe enchanted by the item : " << bp[i]->getAbilityName() << endl;
			cout << "enchanted bonus is : " << bp[i]->getEnchBonus() << endl;
		}
		cout << "**********************END OF EMPTY WORN ITEM****************" << endl;


	}//else
	//------------------------------------------------------------------------------------------
	if (backpack_bp.size() == 0)
	{
		cout << "*********************BACKPACK ITEM*******************" << endl;
		cout << "*********************END OF EMPTY BACKPACK ITEM *******************" << endl;
	}

	else
	{
		cout << "**********************EMPTY BACKPACK ITEM****************" << endl;
		//loop through all items of wornItems itemContainer
		for (int i = 0; i < backpack_bp.size(); i++)
		{
			cout << "ID : " << backpack_bp[i]->getId() << endl;
			cout << "item type (name) : " << backpack_bp[i]->getType() << endl;
			cout << "chosen ability toe enchanted by the item : " << backpack_bp[i]->getAbilityName() << endl;
			cout << "enchanted bonus is : " << backpack_bp[i]->getEnchBonus() << endl;
		}
		cout << "**********************END OF BACKPACK ITEM****************" << endl;
	}//else


	//------------------------------------------------------------------------------------------
	if (backpack_bp.size() == 0)
	{
		cout << "*********************TREASURE ITEM*******************" << endl;
		cout << "*********************END OF EMPTY TREASURE ITEM *******************" << endl;
	}

	else
	{
		cout << "**********************EMPTY TREASURE ITEM****************" << endl;
		//loop through all items of wornItems itemContainer
		for (int i = 0; i < treasure_bp.size(); i++)
		{
			cout << "ID : " << treasure_bp[i]->getId() << endl;
			cout << "item type (name) : " << treasure_bp[i]->getType() << endl;
			cout << "chosen ability toe enchanted by the item : " << treasure_bp[i]->getAbilityName() << endl;
			cout << "enchanted bonus is : " << treasure_bp[i]->getEnchBonus() << endl;
		}
		cout << "**********************END OF TREASURE ITEM****************" << endl;


	}//else

}//end of function

void Character::setAbilities() { //Added from a3
	abilities.push_back(new Ability("Strength"));
	abilities.push_back(new Ability("Constitution"));
	abilities.push_back(new Ability("Dexterity"));
	abilities.push_back(new Ability("Intelligence"));
	abilities.push_back(new Ability("Wisdom"));
	abilities.push_back(new Ability("Charisma"));
}

void Character::setArmorClass() { //Added from a3
	Dice aDice;
	armorClass = 11 + aDice.roll("1d20[+" + to_string(getAbility("Dexterity")->getScore()) + "]") + calculatePB();
}

void Character::setDamageBonus() { //Added from a3
	Dice aDice;
	damageBonus = aDice.roll("1d20[+" + to_string(getAbility("Strength")->getScore()) + "]");
}

void Character::setAttackBonus(int level) { //Added from a3
	int movingLevel = level;

	while (movingLevel>0) {
		attackBonus.push_back(movingLevel);
		movingLevel = movingLevel - 5;
	}
}

void Character::setNbrOfAttacks(int level) { //Added from a3
	int movingLevel = level;
	int counter = 0;

	while (movingLevel>0) {
		counter++;
		nbrOfAttacks = counter;
		movingLevel = movingLevel - 5;
	}
}

void Character::setWornItems() { //Added from a3
	wornItems = new ItemContainer("bag1", "wornItems");
}

void Character::setBackPack() { //Added from a3
	backpack = new ItemContainer("bag2", "backpack");
}

void Character::setTreasureChest() { //Added from a3
	tresureChest = new ItemContainer("bag3", "treasureChest");
}
