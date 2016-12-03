#pragma once
#include "Map.h"
#include <vector>

//! @file 
//! @brief the implementation of the D&D map manager class
//! 
//! This class manages all of the io for maps within the game. It creates, saves, loads, and lists all the maps. 
//!  
//!
//! Implementation details: We are saving files to the current directory of the project. In order to get a list of the files we are 
//! also appending the file name to a file with the file names. As we get the file names we put it in a set to protect against duplicates.
//!
//!	Libraries used: I used the C++ STD library for the set collection and string functions

class MapEditor
{
private:
	void saveItem(Item* item, ofstream* myfile);
	void saveItemContainer(ofstream* myfile, ItemContainer * item_container);
	void saveAbility(ofstream* myfile, Ability* ability);
	void saveCharacters(ofstream* myfile);
public:
	Map* current_map;
	bool createMap(int hight, int width, std::string map_name);
	Item* parseItem(ifstream* myfile);
	vector<Item*> parseItemVector(ifstream* myfile);
	ItemContainer* parseItemContainer(ifstream* myfile);
	Ability* parseAbility(ifstream* myfile);
	vector<Ability*> parseAbilityVector(ifstream* myfile);
	Character* parseCharacter(ifstream* myfile);
	bool loadMap(std::string mapName);
	void saveChests(ofstream* myfile);
	bool saveMap(std::string mapName);
	std::set<std::string> getMaps();
};

