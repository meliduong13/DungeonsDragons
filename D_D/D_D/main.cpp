#include "Ability.h"
#include "Character.h"
#include "ItemContainer.h"
#include "Item.h"
#include "Map.h"
#include "MapEditor.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Nimble.h"
#include "CharacterDirector.h"
#include <String>

using namespace std;

Character* make_player();

int choice;
int height, width;
int x, y;
string mapName;

char name;
char answer;
int row, col;
char obj;
bool exitWhile = false;
bool exitFromSelOpt = false;

string questName;
Character *enemy;
Character *aCharacter = make_player();
Map *aMap = new Map();
MapEditor *editor = new MapEditor();
Item *myItem;
string aname = "";


Character* make_player()
{
	CharacterDirector chDirector;
	int level = 1;
	////Create the Concrete Builder Nimble
	CharacterBuilder* nimble = new Nimble;
	////Tell the CharacterDirector which Concrete Builder to use
	chDirector.setCharacterBuilder(nimble);
	////Tell the Director to construct
	chDirector.constructCharacter(level, "friendly");
	////We are getting the character of nimble
	return chDirector.getCharacter();
}


void createNewMap() {
	delete aMap;
	cout << "Enter the quest name: " << endl;
	cin >> mapName;
	cout << "Enter desired map width: " << endl;
	cin >> width;

	cout << "Enter desired map height: " << endl;
	cin >> height;

	editor->createMap(height, width, mapName);
	aMap = editor->current_map;
} //3

bool chooseNewMap() {
	cout << "Do you wish to create:" << endl;
	cout << "[1] Map" << endl << "[2] Default Map" << endl;
	cin >> choice;
	if (choice != 1 && choice != 2)
	{
		return false;
	}

	if (choice == 1)
	{
		createNewMap();
	}
	else {
		editor->createMap(5, 5, "default");
		aMap = editor->current_map;
	}

	aMap->trySetStartPoint(0, 0);
	aMap->trySetEndPoint(width - 1, height - 1);
	aMap->setCharacterAtStartingPoint();
	editor->current_map->addActor("p", aCharacter);
	editor->saveMap(editor->current_map->map_name);

	return true;
} //2
bool startNewGame() {
	cout << "Menu:" << endl << "[1] Start new game :" << endl << "[2] Load previous game " << endl << endl;
	cin >> choice;
	if (choice != 1 && choice != 2)
	{
		return false;
	}

	if (choice == 1)
	{
		while (!chooseNewMap()) {
			cout << "Invalid Choice! Select between 1 and 2";
		}
	}
	else
	{

		cout << "Welcome back, the game will now resume from the previous state" << endl;
		cout << "Loading..." << endl;
		set<string> s = editor->getMaps();
		vector<string> v(s.begin(), s.end());
		int i = 0;
		int choice;
		for each (string var in v)
		{
			if (i == 0)
			{
				i++;
				continue;
			}
			cout << i << "\t" << var << endl;
			i++;
		}
		cin >> choice;
		editor->loadMap(v[choice]);
		aMap = editor->current_map;
	}

	return true;
} //1

void fillCellHandler() {
	switch (choice)
	{
	case 1: obj = 'i';
		aMap->fillCell(x, y, obj);
		system("CLS");
		aMap->displayMap();
		break;

	case 2: obj = 'o';//adding chest
		
		system("CLS");
		aMap->displayMap();
		break;

	case 3: obj = 'w';
		aMap->fillCell(x, y, obj);
		//verify if adding a new wall would still make the map traversable
		//if traversable, display map
		if (aMap->validatePath(0, 0, aMap->mapWidth - 1, aMap->mapHeight - 1))
		{
			system("CLS");
			aMap->displayMap();
		}
		else//otherwise do not fill the cell, and ask the user to add another item
		{
			aMap->fillCell(x, y, ' ');
			system("CLS");
			aMap->displayMap();
			cout << "Your last wall coordinate does not offer any valid path" << endl;
		}
		break;
	case 4: obj = 'c';//adding a chest
		//ItemContainer name = new ItemContainer();
		aMap->fillCell(x, y, obj);
		aname = to_string(x) + "," + to_string(y);
		aMap->addItemContainer(aname, new ItemContainer());
		do {
			do {
				cout << "Select which item do you want to add to chest" << endl;
				cout << "1 - Armor" << endl;
				cout << "2 - Ring" << endl;
				cout << "3 - Helmet" << endl;
				cout << "4 - Boots" << endl;
				cout << "5 - Belt" << endl;
				cout << "6 - Sword" << endl;
				cout << "7 - Shield" << endl;
				cout << "8 - Nothing more to add" << endl;
				cin >> choice;
			} while (choice < 0 || choice > 8);//do while

			switch (choice)
			{
			case 1: 
				aMap->getChests()[aname]->addItem(new Item("Armor"));
				break;
			case 2: 
				aMap->getChests()[aname]->addItem(new Item("Ring"));
				break;
			case 3: 
				aMap->getChests()[aname]->addItem(new Item("Helmet"));
				break;
			case 4:
				aMap->getChests()[aname]->addItem(new Item("Boots"));
				break;
			case 5: 
				aMap->getChests()[aname]->addItem(new Item("Belt"));
				break;
			case 6: 
				aMap->getChests()[aname]->addItem(new Item("Sword"));
				break;
			case 7: 
				aMap->getChests()[aname]->addItem(new Item("Shield"));
				break;
			case 8: break;
			}
		} while (choice != 8);// if you do not want to add anything anymore
		system("CLS");
		aMap->displayMap();
		cout << "---------------ADDED CHEST "<<aname <<" CONTAINS------------------" << endl;
		for (int i = 0; i < aMap->getChestsAsList().at(0)->getItems().size(); i++) {
			cout << "--> " << aMap->getChestsAsList().at(0)->getItems().at(i)->getType() << endl;
		}
		cout << "---------------ADDED CHEST " << aname << " CONTAINS------------------"<<endl;
		break;

	case 5: obj = 'a';
		enemy = make_player();
		enemy->setCol(x);
		enemy->setRow(y);
		editor->current_map->addActor("a", enemy);
		editor->saveMap(editor->current_map->map_name);
		system("CLS");
		aMap->displayMap();
		break;

	case 0: cout << "Starting the game" << endl;
		exitWhile = true;
		break;
	}
} //7


bool selectCoord() {
	cout << "Select the coordinates, the height and width of the map" << endl;
	cout << "Enter the x coordinate (starts from 0): " << endl;
	cin >> x;
	cout << "Enter the y coordinate (starts from 0): " << endl;
	cin >> y;
	if (x >= aMap->mapWidth || y >= aMap->mapHeight || x < 0 || y < 0) {
		return false;
	}
	return true;
} //6

bool selectOption() {
	cout << "Select between the options offered" << endl;
	cin >> choice;
	if (choice != 0 && choice < 1 || choice > 5) { //invalid choice
		return false;
	}
	if (choice == 0) {
		exitFromSelOpt = true;
	}
	return true;
} //5

bool addMapObject() {
	cout << "Select which object you want to add to the map:" << endl;
	cout << "1 - Entry door [i]" << endl;
	cout << "2 - Exit door [o]" << endl;
	cout << "3 - Wall [w]" << endl;
	cout << "4 - Chest [c]" << endl;
	cout << "5 - Characters [a]" << endl;
	cout << "0 - To Continue..." << endl << endl;
	if (selectOption() == true && exitWhile == false)
	{
		if (exitFromSelOpt)
			return false;

		if (selectCoord())
		{
			fillCellHandler();
			if (exitWhile == false) {
				addMapObject();
			}
			if (exitWhile)
				return false;
			return true;
		}
	}
	return false;
}//4


void moveCharacter(string code, Character* aCharacter){
	vector<char> surroundedEnemies;
	surroundedEnemies = aMap->getSurroundingEnemies();
	bool canAttack = false;
	if (surroundedEnemies.size() > 0) {
		canAttack = true;
	}
	do{
		cout << "Move the character again" << endl;
		cout << "8 - Move up" << endl;
		cout << "4 - Move left" << endl;
		cout << "5 - Move down" << endl;
		cout << "6 - Move right" << endl;
		if(canAttack)
		cout << "7 - Attack" << endl;
		cout << "0 - Save game" << endl;
		cin >> choice;
		if (choice == 4)
		{
			system("CLS");
			aMap->moveLeft(code);
			aMap->displayMap();

		}
		else if (choice == 5) {
			system("CLS");
			aMap->moveDown(code);
			aMap->displayMap();

		}
		else if (choice == 6) {
			system("CLS");
			aMap->moveRight(code);
			aMap->displayMap();

		}
		if (choice == 8)
		{
			system("CLS");
			aMap->moveUp(code);
			aMap->displayMap();

		}
		if (choice == 7 && canAttack) {
			cout << "Who do you wish to attack?" << endl;
			string attackChoice;
			for (int i = 0; i < surroundedEnemies.size(); i++) {
				cout << surroundedEnemies.at(i) << endl;
			}
			cin >> attackChoice;
			aCharacter->attack(aMap->getActor(attackChoice));
		}
		if (choice == 0)
		{
			editor->saveMap(editor->current_map->map_name);
		}
		if (aCharacter->getPlayerX() == aMap->mapWidth-1 && aCharacter->getPlayerY() == aMap->mapHeight-1)
		{
			cout << "Character Level BEFORE is : " << aCharacter->getLevel();
			cout << "Character Level AFTER is : " << aCharacter->incrLevel();
			return;
		}
	} while (true);
}



bool addItem() {
	cout << "Select which item do you want to create" << endl;
	cout << "1 - Armor" << endl;
	cout << "2 - Ring" << endl;
	cout << "3 - Helmet" << endl;
	cout << "4 - Boots" << endl;
	cout << "5 - Belt" << endl;
	cout << "6 - Sword" << endl;
	cout << "7 - Shield" << endl;
	cout << "0 - To Continue..." << endl << endl;
	cin >> choice;
	if (choice < 0 || choice > 7)
	{
		return false;
	}

	if (choice == 0)
	{
		return true;
	}

	switch (choice)
	{
	case 1: myItem = new Item("Armor");
		aCharacter->getWornItemContainer()->addItem(myItem);
		aCharacter->wearUpdate("add");
		aCharacter->printProfile();
		break;
	case 2: myItem = new Item("Ring");
		aCharacter->getWornItemContainer()->addItem(myItem);
		aCharacter->wearUpdate("add");
		aCharacter->printProfile();
		break;
	case 3: myItem = new Item("Helmet");
		aCharacter->getWornItemContainer()->addItem(myItem);
		aCharacter->wearUpdate("add");
		aCharacter->printProfile();
		break;
	case 4: myItem = new Item("Boots");
		aCharacter->getWornItemContainer()->addItem(myItem);
		aCharacter->wearUpdate("add");
		aCharacter->printProfile();
		break;
	case 5: myItem = new Item("Belt");
		aCharacter->getWornItemContainer()->addItem(myItem);
		aCharacter->wearUpdate("add");
		aCharacter->printProfile();
		break;
	case 6: myItem = new Item("Sword");
		aCharacter->getWornItemContainer()->addItem(myItem);
		aCharacter->wearUpdate("add");
		aCharacter->printProfile();
		break;
	case 7: myItem = new Item("Shield");
		aCharacter->getWornItemContainer()->addItem(myItem);
		aCharacter->wearUpdate("add");
		aCharacter->printProfile();
		break;
	}

	return false;
}
bool removeItem() {
	cout << "Select which item do you want to remove" << endl;
	cout << "1 - Armor" << endl;
	cout << "2 - Ring" << endl;
	cout << "3 - Helmet" << endl;
	cout << "4 - Boots" << endl;
	cout << "5 - Belt" << endl;
	cout << "6 - Sword" << endl;
	cout << "7 - Shield" << endl;
	cout << "0 - To Continue..." << endl << endl;
	cin >> choice;
	if (choice < 0 || choice > 7)
	{
		return false;
	}

	if (choice == 0)
	{
		return true;
	}

	bool found = false;
	switch (choice)
	{
	case 1:

		if (0 == aCharacter->getWornItemContainer()->getItems().size()) {
			cout << "backpack is empty , cannot remove items" << endl;
		}
		for (int i = 0; i < aCharacter->getWornItemContainer()->getItems().size(); i++) {
			if ("Armor" == aCharacter->getWornItemContainer()->getItems().at(i)->getType()) {
				aCharacter->getBackPackContainer()->addItem(aCharacter->getWornItemContainer()->removeItem("Armor"));
				aCharacter->wearUpdate("remove");
				aCharacter->printProfile();
				found = true;
				break;
			}

			if (!found) {
				cout << "YOU DON'T HAVE THIS ITEM!" << endl;
			}
		}
		break;
	case 2:
		if (0 == aCharacter->getWornItemContainer()->getItems().size()) {
			cout << "YOU DON'T HAVE THIS ITEM!" << endl;
		}
		for (int i = 0; i < aCharacter->getWornItemContainer()->getItems().size(); i++) {
			if ("Ring" == aCharacter->getWornItemContainer()->getItems().at(i)->getType()) {
				aCharacter->getBackPackContainer()->addItem(aCharacter->getWornItemContainer()->removeItem("Ring"));
				aCharacter->wearUpdate("remove");
				aCharacter->printProfile();
				found = true;
				break;
			}
			if (!found) {
				cout << "YOU DON'T HAVE THIS ITEM!" << endl;
			}
		}
		break;
	case 3:
		if (0 == aCharacter->getWornItemContainer()->getItems().size()) {
			cout << "YOU DON'T HAVE THIS ITEM!" << endl;
		}
		for (int i = 0; i < aCharacter->getWornItemContainer()->getItems().size(); i++) {
			if ("Helmet" == aCharacter->getWornItemContainer()->getItems().at(i)->getType()) {
				aCharacter->getBackPackContainer()->addItem(aCharacter->getWornItemContainer()->removeItem("Helmet"));
				aCharacter->wearUpdate("remove");
				aCharacter->printProfile();
				found = true;
				break;
			}
			if (!found) {
				cout << "YOU DON'T HAVE THIS ITEM!" << endl;
			}
		}
		break;
	case 4:
		if (0 == aCharacter->getWornItemContainer()->getItems().size()) {
			cout << "YOU DON'T HAVE THIS ITEM!" << endl;
		}
		for (int i = 0; i < aCharacter->getWornItemContainer()->getItems().size(); i++) {
			if ("Boots" == aCharacter->getWornItemContainer()->getItems().at(i)->getType()) {
				aCharacter->getBackPackContainer()->addItem(aCharacter->getWornItemContainer()->removeItem("Boots"));
				aCharacter->wearUpdate("remove");
				aCharacter->printProfile();
				found = true;
				break;
			}
			if (!found) {
				cout << "YOU DON'T HAVE THIS ITEM!" << endl;
			}
		}
		break;
	case 5:
		if (0 == aCharacter->getWornItemContainer()->getItems().size()) {
			cout << "YOU DON'T HAVE THIS ITEM!" << endl;
		}
		for (int i = 0; i < aCharacter->getWornItemContainer()->getItems().size(); i++) {
			if ("Belt" == aCharacter->getWornItemContainer()->getItems().at(i)->getType()) {
				aCharacter->getBackPackContainer()->addItem(aCharacter->getWornItemContainer()->removeItem("Belt"));
				aCharacter->wearUpdate("remove");
				aCharacter->printProfile();
				found = true;
				break;
			}
			if (!found) {
				cout << "YOU DON'T HAVE THIS ITEM!" << endl;
			}
		}
		break;
	case 6:
		if (0 == aCharacter->getWornItemContainer()->getItems().size()) {
			cout << "YOU DON'T HAVE THIS ITEM!" << endl;
		}
		for (int i = 0; i < aCharacter->getWornItemContainer()->getItems().size(); i++) {
			if ("Sword" == aCharacter->getWornItemContainer()->getItems().at(i)->getType()) {
				aCharacter->getBackPackContainer()->addItem(aCharacter->getWornItemContainer()->removeItem("Sword"));
				aCharacter->wearUpdate("remove");
				aCharacter->printProfile();
				found = true;
				break;
			}
			if (!found) {
				cout << "YOU DON'T HAVE THIS ITEM!" << endl;
			}
		}
		break;
	case 7:
		if (0 == aCharacter->getWornItemContainer()->getItems().size()) {
			cout << "YOU DON'T HAVE THIS ITEM!" << endl;
		}
		for (int i = 0; i < aCharacter->getWornItemContainer()->getItems().size(); i++) {
			if ("Shield" == aCharacter->getWornItemContainer()->getItems().at(i)->getType()) {
				aCharacter->getBackPackContainer()->addItem(aCharacter->getWornItemContainer()->removeItem("Shield"));
				aCharacter->wearUpdate("remove");
				aCharacter->printProfile();
				found = true;
				break;
			}
			if (!found) {
				cout << "YOU DON'T HAVE THIS ITEM!" << endl;
			}
		}
		break;
	}

	return false;
}

bool addItemDecision() {
	cout << "Do you wish to add a new item?" << endl << "[1]  yes" << endl << "[2] no" << endl;
	cin >> choice;
	if (choice != 1 && choice != 2)
	{
		return false;
	}

	if (choice == 1)
	{
		while (!addItem()) {}
	}

	return true;
}

bool removeItemDecision() {
	cout << "Do you wish to remove an item?" << endl << "[1]  yes" << endl << "[2] no" << endl;
	cin >> choice;
	if (choice != 1 && choice != 2)
	{
		return false;
	}

	if (choice == 1)
	{
		while (!removeItem()) {}
	}

	return true;
}

int main() {

	cout << "Welcome to Dragon and Dugeons" << endl;

	while (!startNewGame()) {
		cout << " Invalid choice. Please select a choice between 1 and 2" << endl;
	}

	aCharacter->printProfile(); //THIS DOES NOT WORK FIX!

	aMap->displayMap();


	while (!addMapObject()) {
		if (exitFromSelOpt || exitWhile) {
			cout << "Starting the game" << endl;
			break;
		}
		cout << "Invalid Choice!" << endl;
	}

	while (!addItemDecision()) {
		cout << "Please select a choice between the offered options" << endl;
	}
	while (!removeItemDecision()) {
		cout << "Please select a choice between the offered options" << endl;

	}
	editor->current_map->displayMap();
	moveCharacter("p",aCharacter);


	return 0;
}

//main for builder pattern
/*
//#include "CharacterDirector.h"
//#include "CharacterBuilder.h"
//
//#include "Nimble.h"
//#include "Bully.h"
//#include "Tank.h"
//
//int level = 1;
//CharacterDirector chDirector;
//CharacterBuilder* nimble = new Nimble;
//chDirector.setCharacterBuilder(nimble);
////Character* _ch = new Character;
//chDirector.constructCharacter(level, "friendly");
*/

//old main
/*
#include "Ability.h"
#include "Character.h"
#include "ItemContainer.h"
#include "Item.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {

Character* aCharacter = new Character();
cout << "*****************************When we CREATE new character : " << endl;
aCharacter->printProfile();
Item* i1 = new Item("Ring");
Item* i2 = new Item("Helmet");
cout << endl;
cout << "******************************When we CREATE a new item which is a \'Ring\' : " << endl;
aCharacter->getWornItemContainer()->addItem(i1);
aCharacter->printProfile();
cout << "******************************When we CREATE a new item which is a \'Helmet\' : " << endl;
aCharacter->getWornItemContainer()->addItem(i2);
aCharacter->printProfile();
cout << endl;
cout << "***************************When we ADD a new item which is a \'Ring\' & \'Helmet\' : " << endl;
aCharacter->printProfile();
aCharacter->wearUpdate("add");
cout << endl;
cout << "******************************When we UPDATE the score after wearing ring & helmet : " << endl;
aCharacter->printProfile();
cout << endl;
cout << "***************************When we REMOVE a new item which is a \'Ring\' : " << endl;
aCharacter->getWornItemContainer()->removeItem(i1);
aCharacter->wearUpdate("remove");
aCharacter->printProfile();
cout << "***************************When we REMOVE a new item which is a \'Helmet\' : " << endl;
aCharacter->getWornItemContainer()->removeItem(i2);
aCharacter->wearUpdate("remove");
aCharacter->printProfile();

}
*/