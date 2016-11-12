#include "Ability.h"
#include "Character.h"
#include "ItemContainer.h"
#include "Item.h"
#include "Map.h"
#include "MapEditor.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

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
Character *aCharacter = new Character();
Map *aMap = new Map(); 
MapEditor *editor = new MapEditor();
Item *myItem;


bool startNewGame() {
	cout << "Menu:" << endl << "[1] Start new game :" << endl << "[2] Load previous game " << endl << endl;
	cin >> choice;
	if (choice != 1 && choice != 2) 
	{ 
		return false; 
	}

	return true;
} //1
bool chooseNewMap() {
	cout << "Do you wish to create:" << endl;
	cout << "[1] Map" << endl << "[2] Default Map" << endl;
	cin >> choice;
	if (choice != 1 && choice != 2) 
	{
		return false;
	}
	return true;
} //2
void createNewMap() {
	delete aMap;
	cout << "Enter the quest name: " << endl;
	cin >> mapName;
	cout << "Enter desired map width: " << endl;
	cin >> width;

	cout << "Enter desired map height: " << endl;
	cin >> height;

	editor->createMap(height, width, questName);
	aMap = editor->current_map;
	aMap->displayMap();
} //3


void fillCellHandler() {
	switch (choice)
	{
		case 1: obj = 'i';
			aMap->fillCell(x, y, obj);
			system("CLS");
			aMap->displayMap();
			break;

		case 2: obj = 'o';
			aMap->fillCell(x, y, obj);
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
		case 4: obj = 'c';
			aMap->fillCell(x, y, obj);
			system("CLS");
			aMap->displayMap();
			break;

		case 5: obj = 'a';
			aMap->fillCell(x, y, obj);
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
	if (choice !=0 && choice < 1 || choice > 5 ) { //invalid choice
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
	if (selectOption()==true && exitWhile == false)
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
	
 

static void createMap(Character *acharacter, Map *aMap )
{
	//create a map and display
	if (choice == 1)
	{
		//2
		//3

		do{//do while add object
			//4 {//5 //6}

			//switch
		} while (choice != 0); //do while add object
	}//if choice is 1
}//if choice is 1 FIRST

void moveCharacter(){
	cin >> choice;

	do{
		cout << "Move the character again"<<endl;
		cout << "8 - Move up" << endl;
		cout << "4 - Move left" << endl;
		cout << "5 - Move down" << endl;
		cout << "6 - Move right" << endl;
		cin >> choice;
	if (choice == 4)
	{
		system("CLS");
		aMap->moveLeft();
		aMap->displayMap();
	}
	if (choice == 5){
		system("CLS");
		aMap->moveDown();
		aMap->displayMap();
	}
	if (choice == 6){
		system("CLS");
		aMap->moveRight();
		aMap->displayMap();
	}
	if (choice == 8){
		system("CLS");
		aMap->moveUp();
		aMap->displayMap();
	}
	} while (true);
}

int main() {

	cout << "Welcome to Dragon and Dugeons" << endl;
	while (!startNewGame()) {
		cout << " Invalid choice. Please select a choice between 1 and 2" << endl;
	}

	cout << "----------USER PROFILE----------" << endl;
	aCharacter->printProfile();
	cout << "----------USER PROFILE----------" << endl;

	while (!chooseNewMap()) {
		cout << "Invalid Choice! Select between 1 and 2";
	}

	createNewMap();

	while (!addMapObject()) {
		if (exitFromSelOpt || exitWhile) {
			cout << "Stasrting the game" << endl;
			break;
		}
		cout << "Invalid Choice!" << endl;
	}
	cout << "Starting the game" << endl;
	cout << "Star moving the character" << endl;
	cout << "8 - Move up" << endl;
	cout << "4 - Move left" << endl;
	cout << "5 - Move down" << endl;
	cout << "6 - Move right" << endl;
	moveCharacter();

		
	return 0;
}
	//createMap(c, m);		


	//	cout << "do you wish to add a new item?" << endl << "1 - yes" << endl << "2 - no" << endl;
	//	do{
	//		cout << "Please select a choice between the offered options" << endl;
	//		cin >> choice;
	//	} while (choice < 1 || choice > 2);
	//	if (choice == 1){
	//		
	//		do{
	//			cout << "Select which item do you want to create" << endl;
	//			cout << "1 - Armor" << endl;
	//			cout << "2 - Ring" << endl;
	//			cout << "3 - Helmet" << endl;
	//			cout << "4 - Boots" << endl;
	//			cout << "5 - Belt" << endl;
	//			cout << "6 - Sword" << endl;
	//			cout << "7 - Shield" << endl;
	//			cout << "0 - To Continue..." << endl << endl;
	//			do{
	//				cin >> choice;
	//			} while (choice < 0 || choice > 7);
	//			
	//			
	//			switch (choice)
	//			{
	//				case 1: myItem = new Item("Armor");
	//						c->getWornItemContainer()->addItem(myItem);
	//						c->wearUpdate("add");
	//						c->printProfile();
	//						break;
	//				case 2: myItem = new Item("Ring");
	//						c->getWornItemContainer()->addItem(myItem);
	//						c->wearUpdate("add");
	//						c->printProfile();
	//						break;
	//				case 3: myItem = new Item("Helmet");
	//						c->getWornItemContainer()->addItem(myItem);
	//						c->wearUpdate("add");
	//						c->printProfile();
	//						break;
	//				case 4: myItem = new Item("Boots");
	//						c->getWornItemContainer()->addItem(myItem);
	//						c->wearUpdate("add");
	//						c->printProfile();
	//						break;
	//				case 5: myItem = new Item("Belt");
	//						c->getWornItemContainer()->addItem(myItem);
	//						c->wearUpdate("add");
	//						c->printProfile();
	//						break;
	//				case 6: myItem = new Item("Sword");
	//						c->getWornItemContainer()->addItem(myItem);
	//						c->wearUpdate("add");
	//						c->printProfile();
	//						break;
	//				case 7: myItem = new Item("Shield");
	//						c->getWornItemContainer()->addItem(myItem);
	//						c->wearUpdate("add");
	//						c->printProfile();
	//						break;
	//				case 0: cout << "Starting the game" << endl;
	//					break;
	//			}
	//		} while (choice != 0);
	//	}//Once selected, prompt the item enhancement

	//}//first if
	//else
	//{
	//	cout << "Welcome back, the game will now resume from the previous state" << endl;
	//	cout << "Loading..." << endl;
	//		set<string> s = editor->getMaps();
	//		vector<string> v(s.begin(), s.end());
	//		int i = 1;
	//		int choice;
	//		for each (string var in v)
	//		{
	//			cout << i << "\t" << var << endl;
	//			i++;
	//		}
	//		cin >> choice;
	//		editor->loadMap(v[choice - 1]);
	//	
	//	// load map, character and items
	//}


	////c->Notify(); //notify map of the character's position
	////m->displayMap();//changes from character reflected in the map
	//m->player_x = 0;
	//m->player_y = 0;
	//m->fillCell(0, 0, 'p');
	//do
	//{
	//	cout << "1 - Character Status, 2 - Controls, 3 - Save&Leave" << endl;
	//	
	//	m->displayMap();
	//	//This is the do while that will loop until the player leaves the game through the menu 
	//	//1- display character status
	//	cin >> choice;
	//	if (choice == 1){
	//		c->printProfile();
	//	}
	//	if (choice == 2){
	//		cout << "8 - Move up" << endl;
	//		cout << "4 - Move left" << endl;
	//		cout << "5 - Move down" << endl;
	//		cout << "6 - Move right" << endl;
	//	}
	//	if (choice == 3){
	//		string name;
	//		cout << "Enter the name of your state" << endl;
	//		cin >> name;
	//		editor->saveMap(name);
	//		return 0;
	//	}
	//	if (choice == 4)
	//	{
	//		system("CLS");
	//		m->moveLeft();
	//		m->displayMap();
	//	}
	//	if (choice == 5){
	//		system("CLS");
	//		m->moveDown();
	//		m->displayMap();
	//	}
	//	if (choice == 6){
	//		system("CLS");
	//		m->moveRight();
	//		m->displayMap();
	//	}
	//	if (choice == 8){
	//		system("CLS");
	//		m->moveUp();
	//		m->displayMap();
	//	}
	//	cout << "1 - Character Status, 2 - Controls, 3 - Save&Leave" << endl;
	//
	//	//2 - display the items
	//	//3 - display the controls - w go up, a go left, d go right and s go down
	//	//w,a,s,d will move the character
	//} while (choice != 0 || choice != 7 || choice > 8);

	//if (choice != 'Y' || choice != 'y')
	//{
	//	cout << "thanks for playing! see you next time" << endl;
	//	return 0;
	//}











	/*float x1 = -4.5;
	double x2 = -1.0/2.0;
	int x3 = 4 + x1;
	Character* aCharacter = new Character();
	cout << endl;
	cout << "x1 = " << floor(x1) << " x2 = " << x2 << " floor(x2) = " << floor(x2) << endl;
	*/
	/*Character* aCharacter = new Character();
	cout << "*****************************When we CREATE new character : " << endl;
	aCharacter->printProfile();
	Item* i1 = new Item("Ring");
	Item* i2 = new Item("Helmet");

	cout << endl;

	cout << "******************************When we CREATE a new item which is a \'Ring\' : " << endl;
	aCharacter->printProfile();
	aCharacter->getWornItemContainer()->addItem(i1);
	cout << "******************************When we CREATE a new item which is a \'Helmet\' : " << endl;
	aCharacter->printProfile();
	aCharacter->getWornItemContainer()->addItem(i2);

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
	*/
	//**************************************************************************		