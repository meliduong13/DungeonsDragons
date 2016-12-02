#pragma once
#include "item.h"
#include <string>
#include<vector>
//! @file 
//! @brief Header file for the ItemContainer class  
//!

//! class that implements an ItemContainer which can add items to it, and retrieve a specific Item using its unique ID. it can also return a list of Item it contains
class ItemContainer{

protected:
	//enum containerName { backpack, wornItems, treasureChest };
	string type;

	vector<Item*>items;

public:
	string name;
	ItemContainer::ItemContainer();
	ItemContainer::~ItemContainer();
	ItemContainer::ItemContainer(string aname, string atype);
	ItemContainer::ItemContainer(vector<Item*> containeritems);
	ItemContainer(vector<Item*> items, string name, string type);
	bool ItemContainer::addItem(Item* anitem);
	void ItemContainer::removeItem(Item* anitem);
	Item ItemContainer::getItem(int itemId);
	vector<Item*> ItemContainer::getItems();
	string ItemContainer::getType();
	int ItemContainer::getSize();
	int getItemPosition(string aitemName);
	void displayContent();

};



