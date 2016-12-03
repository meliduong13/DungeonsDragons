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
#include <string>
#include "Logger.h"
#include <io.h>
#include <locale>
#include <cstdio>  // for _fileno
#include <fcntl.h> // for _O_U16TEXT
#include <codecvt>
#include "Tank.h"
#include "Bully.h"

using namespace std;

Character* make_player(int level, string selectOption);

int choice;
int height, width;
int x, y;
string mapName;

char name;
char answer;
int row, col;
string obj;
bool exitWhile = false;
bool exitFromSelOpt = false;
void newStage();
string questName;
Character *enemy;
Character *aCharacter = make_player(2, "Nimble");
Map *aMap = new Map();
MapEditor *editor = new MapEditor();
Item *myItem;
string aname = "";
int enemyNum = 0;
string enemyCode = "";

bool campaignMode = false;
int stage = 0;

void printEnding();
void printAsciiArt(string file);
void printStage(wstring file);

Character* make_player(int level, string selecOptionString)
{
	CharacterDirector chDirector;
	////Create the Concrete Builder Nimble
	if (selecOptionString == "Bully") {
		CharacterBuilder* bully = new Bully;
		////Tell the CharacterDirector which Concrete Builder to use
		chDirector.setCharacterBuilder(bully);
	}
	else if (selecOptionString == "Nimble") {
		CharacterBuilder* nimble = new Nimble;
		////Tell the CharacterDirector which Concrete Builder to use
		chDirector.setCharacterBuilder(nimble);
	}
	else if (selecOptionString == "Tank") {
		CharacterBuilder* tank = new Tank;
		////Tell the CharacterDirector which Concrete Builder to use
		chDirector.setCharacterBuilder(tank);
	}
	////Tell the Director to construct
	chDirector.constructCharacter(level, "friendly");
	////We are getting the character of nimble
	return chDirector.getCharacter();
}


void printAsciiArt(wstring file)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	// open the file as Unicode, so we can read into wstrings
	wifstream ifs(file);

	// imbue the file with a codecvt_utf8 facet which knows how to
	// convert from UTF-8 to UCS2 (the 2-byte part of UTF-16)
	// Note this is available in Visual C++ 2010 and later
	locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
	ifs.imbue(utf8_locale);

	// Skip the BOM (this gets translated from the UTF-8 to the
	// UTF-16 version so will be a single character.)
	wchar_t bom = L'\0';
	ifs.get(bom);

	// Read the file contents and write to wcout
	wstring line;
	while (getline(ifs, line)) {
		wcout << line << endl;
	}
	_setmode(_fileno(stdout), _O_TEXT);
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
		GameLogger::printEvent("Creating a new non default game");
		createNewMap();
	}
	else {
		GameLogger::printEvent("Using the default game");
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
	cout << "Menu:" << endl << "[1] Start new game :" << endl << "[2] Load previous game " << endl << "[3] Campaign Mode " << endl << endl;
	cin >> choice;
	if (choice != 1 && choice != 2 && choice !=3)
	{
		return false;
	}

	if (choice == 1)
	{
		GameLogger::printEvent("creating a new game..");
		while (!chooseNewMap()) {
			cout << "Invalid Choice! Select between 1 and 2";
		}
	}
	else if (choice == 2)
	{
		GameLogger::printEvent("loading a existing game");

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
		GameLogger::printEvent("chose to load the " + v[choice] + " game");
		editor->loadMap(v[choice]);
		aMap = editor->current_map;
		aCharacter = editor->current_map->getActor("p");
	} else if (choice == 3)
	{
		campaignMode = true;
		GameLogger::printEvent("Starting campaign mode");
		editor->loadMap("c0");
		aMap = editor->current_map;
		aCharacter = editor->current_map->getActor("p");
		printAsciiArt(L"start_campaign.txt");
		system("pause");
	}

	return true;
} //1

void fillCellHandler() {
	int tempLevel = 1;
	int selcOption;
	string selcOptionString;
	string choiceEorF;
	switch (choice)
	{
	case 1: obj = "i";
		GameLogger::printEvent("adding a entry door to the map");
		aMap->fillCell(x, y, obj);
		system("CLS");
		aMap->displayMap();
		break;

	case 2: obj = "o";
		GameLogger::printEvent("adding a exit door to the map");
		aMap->fillCell(x, y, obj);
		aMap->trySetEndPoint(x, y);
		system("CLS");
		aMap->displayMap();
		break;

	case 3: obj = "w";
		GameLogger::printEvent("adding a wall to the map");
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
			aMap->fillCell(x, y, " ");
			system("CLS");
			aMap->displayMap();
			cout << "Your last wall coordinate does not offer any valid path" << endl;
		}
		break;
	case 4: obj = "c";//adding a chest
					  //ItemContainer name = new ItemContainer();
		GameLogger::printEvent("adding a chest to the map");
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
				GameLogger::printEvent("selected armor");
				aMap->getChests()[aname]->addItem(new Item("Armor"));
				break;
			case 2:
				GameLogger::printEvent("selected ring");
				aMap->getChests()[aname]->addItem(new Item("Ring"));
				break;
			case 3:
				GameLogger::printEvent("selected helmet");
				aMap->getChests()[aname]->addItem(new Item("Helmet"));
				break;
			case 4:
				GameLogger::printEvent("selected boots");
				aMap->getChests()[aname]->addItem(new Item("Boots"));
				break;
			case 5:
				GameLogger::printEvent("selected belt");
				aMap->getChests()[aname]->addItem(new Item("Belt"));
				break;
			case 6:
				GameLogger::printEvent("selected sword");
				aMap->getChests()[aname]->addItem(new Item("Sword"));
				break;
			case 7:
				GameLogger::printEvent("selected shield");
				aMap->getChests()[aname]->addItem(new Item("Shield"));
				break;
			case 8: break;
			}
		} while (choice != 8);// if you do not want to add anything anymore
		system("CLS");
		aMap->displayMap();
		cout << "---------------ADDED CHEST " << aname << " CONTAINS------------------" << endl;
		for (int i = 0; i < aMap->getChests()[aname]->getItems().size(); i++) {
			cout << "--> " << aMap->getChests()[aname]->getItems().at(i)->getType() << endl;
		}
		cout << "---------------ADDED CHEST " << aname << " CONTAINS------------------" << endl;
		break;

	case 5: obj = "a";
		cout << "Please enter the level of the enemy: " << endl;
		cin >> tempLevel;
		cout << "Please enter the type of enemy : " << endl;
		cout << "1- Bully" << endl;
		cout << "2- Nimble" << endl;
		cout << "3- Tank" << endl;
		cin >> selcOption;
		if (selcOption == 1) {
			selcOptionString = "Bully";
		}
		else if (selcOption == 2) {
			selcOptionString = "Nimble";
		}
		else {
			selcOptionString = "Tank";
		}
		GameLogger::printEvent("made player");
		enemy = make_player(tempLevel, selcOptionString);
		enemyCode = "a" + to_string(enemyNum);
		enemyNum++;
		enemy->setCol(x);
		enemy->setRow(y);
		editor->current_map->addActor(enemyCode, enemy);
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


void moveCharacter(string code, Character* aCharacterP){
	vector<string> surroundedEnemies;
	bool canAttack;

	do{
		surroundedEnemies = aMap->getSurroundingEnemies();
		canAttack = surroundedEnemies.size() > 0;
		aCharacterP->printProfile();
		cout << "Move the character again" << endl;
		cout << "8 - Move up" << endl;
		cout << "4 - Move left" << endl;
		cout << "5 - Move down" << endl;
		cout << "6 - Move right" << endl;
		if(canAttack)
		cout << "7 - Attack" << endl;
		cout << "9 - disable the logger" << endl;
		cout << "10 - enable the logger" << endl;
		cout << "11 - disable the inventory view" << endl;
		cout << "12 - enable the inventory view" << endl;
		cout << "0 - Save game" << endl;
		cin >> choice;

		if (choice == 4)
		{
			GameLogger::printEvent("player moving left");
			system("CLS");
			aMap->moveLeft(code);
			aMap->displayMap();

		}
		else if (choice == 5){
			GameLogger::printEvent("player moving down");
			system("CLS");
			aMap->moveDown(code);
			aMap->displayMap();

		}
		else if (choice == 6){
			GameLogger::printEvent("player moving right");
			system("CLS");
			aMap->moveRight(code);
			aMap->displayMap();

		}
		if (choice == 8)
		{
			GameLogger::printEvent("player moving up");
			system("CLS");
			aMap->moveUp(code);
			aMap->displayMap();

		}

		if (choice == 9)
		{
			GameLogger::printEvent("disabling the logger");
			GameLogger::enabled = false;
			system("CLS");
			cout << "logger disabled" << endl;
			aMap->displayMap();
		}

		if (choice == 10)
		{
			
			GameLogger::enabled = true;
			GameLogger::printEvent("enabled the logger");
			system("CLS");
			cout << "logger enabled" << endl;
			aMap->displayMap();
		}

		if (choice == 11)
		{
			aCharacterP->togglePrinting(false);
			GameLogger::printEvent("diable the inventory view");
			system("CLS");
			cout << "inventory disabled" << endl;
			aMap->displayMap();
		}

		if (choice == 12)
		{
			aCharacterP->togglePrinting(true);
			GameLogger::printEvent("enabled the inventory view");
			system("CLS");
			cout << "inventory enabled" << endl;
			aMap->displayMap();
		}

		if (choice == 7 && canAttack) {
			cout << "Who do you wish to attack?" << endl;
			string attackChoice;
			GameLogger::printEvent("attacking " + attackChoice);
			for (int i = 0; i < surroundedEnemies.size(); i++) {
				cout << surroundedEnemies.at(i) << endl;
			}
			cin >> attackChoice;
			bool dead;
			cout << "=========== Player Attack Phase ===========" << endl;
			dead = aCharacter->attack(aMap->getActor(attackChoice));
			if (dead) {
				GameLogger::printEvent("destroyed " + attackChoice);
				aMap->destroyEnemy(attackChoice);
			}
			else {
				cout << endl << "=========== Enemy Attack Phase ===========" << endl;
				cout << "Enemy attacked back!!" << endl;
				aMap->getActor(attackChoice)->attack(aCharacter);
			}
			aMap->displayMap();		
		}
		if (choice == 0)
		{
			GameLogger::printEvent("saving game");
			editor->saveMap(editor->current_map->map_name);
			aMap->displayMap();
		}
		if (aCharacterP->getPlayerX() == aMap->mapWidth-1 && aCharacterP->getPlayerY() == aMap->mapHeight-1)
		{
			cout << "Character Level BEFORE is : " << aCharacterP->getLevel();
			cout << "Character Level AFTER is : " << aCharacterP->incrLevel();
			return;
		}
		if (aMap->isAtExit(aCharacterP))
		{
			if (campaignMode)
			{
				stage++;
				if (stage == 3)
				{
					printEnding();
				}
				editor->loadMap("c" + to_string(stage));
				aMap = editor->current_map;
				aCharacter = editor->current_map->getActor("p");
				wstring file = L"c" + to_wstring(stage) + L".txt";
				printStage(file);
				newStage();
			} else
			{
				printEnding();
			}
			
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

			if(!found) {
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

void printEnding()
{
	system("CLS");
	printAsciiArt(L"final_screen.txt");
	system("pause");
	exit(0);
}

void printStage(wstring file)
{
	system("CLS");
	printAsciiArt(file);
	system("pause");
}

void newStage()
{
	system("CLS");
	aCharacter->printProfile();

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
	moveCharacter("p", aCharacter);
}

int main() {
	GameLogger::enabled = true;
	printAsciiArt(L"intro.txt");
	cout << "Welcome to Dragon and Dugeons" << endl;
	GameLogger::printEvent("Starting the welcome screen");
	while (!startNewGame()) {
		cout << " Invalid choice. Please select a choice between 1 and 2" << endl;
	}

	newStage();

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