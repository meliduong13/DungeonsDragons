#include "MapEditor.h"
#include <fstream>
#include <map>
#include <iostream>
#include <windows.h>

//! @file
//! @brief Implementation file for the MapEditor class

using namespace std;

void MapEditor::saveItem(Item* item, ofstream* myfile)
{
	*myfile << item->getType() << "\n";
	*myfile << item->getId() << "\n";
	*myfile << item->getEnchBonus() << "\n";
	*myfile << item->getAbilityName() << "\n";
}

void MapEditor::saveItemContainer(ofstream* myfile, ItemContainer* item_container)
{
	*myfile << item_container->name << "\n";
	*myfile << item_container->getType() << "\n";
	*myfile << item_container->xCoord << "\n";
	*myfile << item_container->yCoord << "\n";
	vector<Item*> items = item_container->getItems();
	*myfile << items.size() << "\n";
	for (int i = 0; i<items.size(); i++)
	{
		saveItem(items[i], myfile);
	}
}

void MapEditor::saveAbility(ofstream* myfile, Ability* ability)
{
	*myfile << ability->getName() << "\n";
	*myfile << ability->getScore() << "\n";
	*myfile << ability->getModifier() << "\n";
}

void MapEditor::saveCharacters(ofstream* myfile)
{
	int size = current_map->getActors().size();
	*myfile << size << "\n";

	for (auto const& ent1 : current_map->getActors())
	{
		*myfile << ent1.first << "\n";
		Character * character = ent1.second;
		*myfile << character->getCharacterType() << "\n";
		*myfile << character->getCharacterClass() << "\n";
		ItemContainer* backpack = character->backpack;
		saveItemContainer(myfile, backpack);
		saveItemContainer(myfile, character->wornItems);
		saveItemContainer(myfile, character->treasureChest);
		vector<Ability*> abilities = character->getAbilities();
		*myfile << abilities.size() << "\n";
		for (int i = 0; i < abilities.size(); i++)
		{
			saveAbility(myfile, abilities[i]);
		}
		*myfile << character->damageBonus << "\n";
		*myfile << character->nbrOfAttacks << "\n";
		*myfile << character->armorClass << "\n";
		*myfile << character->getHitPoints() << "\n";
		*myfile << character->getLevel() << "\n";
		*myfile << character->getCol() << "\n";
		*myfile << character->getRow() << "\n";
	}
}

void MapEditor::saveChests(ofstream* myfile)
{
	int size = current_map->getChests().size();
	*myfile << size << "\n";
	for (auto const& ent1 : current_map->getChests())
	{
		*myfile << ent1.first << "\n";
		ItemContainer* item_container = ent1.second;
		saveItemContainer(myfile, item_container);
	}
}

//! Creates the map and saves it to a file 
//! @param height: the height of the map
//! @param width: the width of the map
//! @param map_name: the name of the map/quest
bool MapEditor::createMap(int hight, int width, std::string map_name)
{
	current_map = new Map(hight, width, map_name);
	return saveMap(map_name);
}

Item* MapEditor::parseItem(ifstream* myfile)
{
	string line; 

	string type;
	int id;
	int enchBonus;
	string abilityName;

	getline(*myfile, line);
	type = line;

	getline(*myfile, line);
	id = atoi(line.c_str());

	getline(*myfile, line);
	enchBonus = atoi(line.c_str());

	getline(*myfile, line);
	abilityName = line;

	return new Item(type, id, enchBonus, abilityName);
}

vector<Item*> MapEditor::parseItemVector(ifstream* myfile)
{
	vector<Item*> items;
	string line; 
	getline(*myfile, line);
	int size = atoi(line.c_str());
	for (int i = 0; i < size; i++)
	{
		Item *item = parseItem(myfile);
		items.push_back(item);
	}

	return items;
}

ItemContainer* MapEditor::parseItemContainer(ifstream* myfile)
{
	string line;
	getline(*myfile, line);
	string name = line;
	getline(*myfile, line);
	string type = line;
	getline(*myfile, line);
	int xCoord = atoi(line.c_str());
	getline(*myfile, line);
	int yCoord = atoi(line.c_str());
	vector<Item*> items = parseItemVector(myfile);
	return new ItemContainer(items, name, type, xCoord, yCoord);
}

Ability* MapEditor::parseAbility(ifstream* myfile)
{
	string line;

	string name;
	int score;
	float modifiier;

	getline(*myfile, line);
	name = line;
	getline(*myfile, line);
	score = atoi(line.c_str());
	getline(*myfile, line);
	modifiier = atof(line.c_str());

	return new Ability(name, score, modifiier);
}

vector<Ability*> MapEditor::parseAbilityVector(ifstream* myfile)
{
	vector<Ability*> abilities;
	string line; 
	
	getline(*myfile, line);
	int size = atoi(line.c_str());
	for (int i = 0; i < size; i++)
	{
		Ability *ability = parseAbility(myfile);
		abilities.push_back(ability);
	}

	return abilities;
}

Character* MapEditor::parseCharacter(ifstream* myfile)
{
	std::string line;
	getline(*myfile, line);
	string characterType = line; 
	getline(*myfile, line);
	string characterClass = line;
	ItemContainer* backpack = parseItemContainer(myfile);
	ItemContainer* wornItems = parseItemContainer(myfile);
	ItemContainer* treasureChest = parseItemContainer(myfile);
	vector<Ability*> abilities = parseAbilityVector(myfile);
	getline(*myfile, line);
	int damageBonus = atoi(line.c_str());
	getline(*myfile, line);
	int numberOfAttacks = atoi(line.c_str());
	getline(*myfile, line);
	int armorClass = atoi(line.c_str());
	getline(*myfile, line);
	int hitPoints = atoi(line.c_str());
	getline(*myfile, line);
	int level = atoi(line.c_str());
	getline(*myfile, line);
	int colPos = atoi(line.c_str());
	getline(*myfile, line);
	int rowPos = atoi(line.c_str());

	return new Character(characterType, characterClass, backpack, wornItems, treasureChest, 
		abilities, damageBonus, numberOfAttacks, armorClass, hitPoints, level, colPos, rowPos);
}

//! Loads the map from a file
//! @param mapname: the map name corresponding to the file that the map is saved in
//! @return a boolean reprenting whether the map can be loaded correctly
bool MapEditor::loadMap(std::string mapName)
{
	delete current_map;
	std::string name = "";
	int width = 0;
	int height = 0;
	std::string line;
	std::ifstream myfile(mapName);
	if (myfile.is_open())
	{
		std::getline(myfile, line);
		name = line;
		//std::cout << line << " :name";
		std::getline(myfile, line);
		height = atoi(line.c_str());
		std::getline(myfile, line);
		width = atoi(line.c_str());
		current_map = new Map(width, height, name);
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				char c = myfile.get();
				current_map->fillCell(i, j, c);
			}
		}
		std::getline(myfile, line);
		std::getline(myfile, line);
		int startx = atoi(line.c_str());
		std::getline(myfile, line);
		int starty = atoi(line.c_str());
		std::getline(myfile, line);
		int endx = atoi(line.c_str());
		std::getline(myfile, line);
		int endy = atoi(line.c_str());

		current_map->trySetStartPoint(startx, starty);
		current_map->trySetEndPoint(endx, endy);

		//starting on the character
		std::getline(myfile, line);
		int numOfCharacter = atoi(line.c_str());
		for (int i = 0; i < numOfCharacter; i++)
		{
			std::getline(myfile, line);
			string code = line;
			Character* character = parseCharacter(&myfile);
			current_map->addActor(code, character);
		}
		getline(myfile, line);
		int numOfChests = atoi(line.c_str());
		for (int i = 0; i < numOfChests; i++)
		{
			getline(myfile, line);
			string code = line;
			ItemContainer *item_container = parseItemContainer(&myfile);
			current_map->addItemContainer(code, item_container);
		}

		myfile.close();
		return true;
	}


	return false;
}

//! Saves the map the current map to a specific file
//! @param mapName: a string representing the map's file name 
//! @return a boolean representing that the map was saved successfully
bool MapEditor::saveMap(std::string mapName)
{
	if (!current_map->validatePath()) return false;

	std::ofstream myfile(mapName);
	if (myfile.is_open())
	{
		myfile << current_map->map_name << "\n";
		myfile << current_map->mapWidth << "\n" << current_map->mapHeight << "\n";
		for (int i = 0; i < current_map->mapHeight; i++)
		{
			for (int j = 0; j < current_map->mapWidth; j++)
			{
				myfile << current_map->getCharacter(i, j);
			}
		}
		myfile << "\n";
		myfile << current_map->start_point_x << "\n" << current_map->start_point_y << "\n" << current_map->end_point_x << "\n" << current_map->end_point_y << "\n";
		saveCharacters(&myfile);
		saveChests(&myfile);

		myfile.close();

		std::ofstream save_file("file_saves", std::ios_base::app);
		if (save_file.is_open())
		{
			save_file << mapName << "\n";
			save_file.close();
		}
		return true;
	}
	return false;
}

//! Gets all of the current maps
//! @return a set of all the map items in a directory
std::set<std::string> MapEditor::getMaps()
{
	std::set<std::string> set = std::set<std::string>();
	std::ifstream myfile("file_saves");
	std::string line;
	if (myfile.is_open())
	{
		while (myfile.good())
		{
			std::getline(myfile, line);
			set.insert(line);
		}
	}

	return set;
}
