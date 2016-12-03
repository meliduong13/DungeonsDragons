#include "ItemContainer.h"
#include <iostream>
//! @file 
//! @brief IMplementation file for the ItemContainer class  
//!
//! default constructor
ItemContainer::ItemContainer()
{
	items = vector<Item*>();
}

//! Contructor to make a item container
//! @param aname: the container name
//! @param atype: the container's type
ItemContainer::ItemContainer(string aname, string atype)
{
	items = vector<Item*>();
	name = aname;
	type = atype;
}

//! constructor that takes a vector of items which are given to an ItemContainer
//! @param containeritems: vector of type Item 
ItemContainer::ItemContainer(vector<Item*> containeritems)
{
	items = containeritems;
}

ItemContainer::ItemContainer(vector<Item*> items, string name, string type, int xCoord, int yCoord)
{
	this->items = items;
	this->name = name;
	this->type = type;
	this->xCoord = xCoord;
	this->yCoord = yCoord;
}

//! method to get the items of the container
//! @return : return the vector of items contained in the ItemContainer
vector<Item*> ItemContainer::getItems()
{
	return items;
}

//! method to add an Item to the ItemContainer
//! method makes sure that the item to be added must have a valid name, if given, otherwise it is not added
//! @param anitem : an Item to put in the ItemContainer
//!@return: boolean which indicates if true, the item has been successfully added, or false, the Item cannot be added because it has an invalid name
bool ItemContainer::addItem(Item* anitem)
{
  string itemType=anitem->getType();
	for (int i = 0; i < items.size(); i++) 
	{
		if (items.at(i)->getType() == itemType) {
			cout << "cannot add duplicate of " << anitem->getType() << endl;
			return false;
		}
	}
	if ((itemType == "Helmet") || (itemType == "Armor") || (itemType == "Shield") || (itemType == "Ring") || (itemType == "Belt") || (itemType == "Boots") || (itemType == "Sword"))
	{
		items.push_back(anitem);
		return true;
	}
		
	else
	{
		cout << "Invalid item. Item could not be added";
		return false;
	}

	//cout << " addItem->item " + anitem->getType() + " was added" << endl;

	////if it is a wornItem, update the abilities of the player
	//if (type == "wornItems")
	//{
	//	for (int i = 0; i < items.size(); i++)
	//	{
	//		for (int j = 0; j < aCharacter->getAbilities().size(); j++)
	//		{

	//			if (items[i]->chosenAbility() == aCharacter->getAbilities().at(j)->getName())
	//			
	//			{
	//				aCharacter->getAbilities().at(j)->incScore(items[i]->getEnchBonus());
	//				cout << "ability " + aCharacter->getAbilities().at(j)->getName() + " is increased by "
	//					<< items[i]->getEnchBonus() << " to " ;
	//				cout << aCharacter->getAbilities().at(j)->getScore() << endl;
	//			}
	//		}
	//	}
	//}
	//

}//addItem

//! Removes an item from the container
//! @param anitem: the item to remove
Item* ItemContainer::removeItem(string anitem)
{
	if (type == "wornItems")

	{
		cout << "going to remove a worn item" << endl;
		//aCharacter->getAbility(anitem->getAbilityName)->incScore(anitem->getEnchBonus());
		//cout << "update the character's ability" + anitem->getAbilityName() + " score ";
		//cout << " of -" + anitem->getEnchBonus()<<endl;
		//cout << " and the final score is " + aCharacter->getAbility(anitem->getAbilityName)->getScore();

	}
	int itemPosition = getItemPosition(anitem);
	Item* object = items.at(itemPosition);
	Item* copy = new Item(object->getType(), object->getId(), object->getEnchBonus(), object->getAbilityName());
	items.erase(items.begin() + itemPosition);

	return copy;

}


//! method to return an Item by giving its unique id ItemContainer
//! @param itemId : id of the Item to be extract from the ItemContainer
//! @return : item with associated id, which was passed as argument to the method
Item* ItemContainer::getItem(int itemId)
{
	for (int i = 0; i < items.size(); i++)
		if (items[i]->getId() == itemId)
			return items[i];
}

//todo: retrieve a list of ID for an item type


//! gets the type of the item container
//! @return string: the type of the container 
string ItemContainer::getType(){

	return type;
}

//! gets the size of the item container
//! @return int: the size of the container 
int ItemContainer::getSize()
{
	int num = 0;
	for (int i = 0; i < items.size(); i++)
		num++;
	return num;
}

//! gets a item's index withn the item container 
//! @param aitemName: the item name 
//! @return int: the item's index
int ItemContainer::getItemPosition(string aitemName) {
	for (int i = 0; i < items.size(); i++) {
		if (items[i]->getType() == aitemName)
			return i;
	}
}

//! Displays the content within a container 
void ItemContainer::displayContent(){
	for (int i = 0; i < items.size(); i++)
		cout << "item " << (i + 1) << "_" << items[i]->getType() << endl;
}