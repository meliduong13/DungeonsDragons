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


static void createMap(Character *acharacter, Map *aMap)
{
	int choice;
	int height, width;
	int x, y;
	char obj;
	cout << "Welcome to Dragon and Dugeons" << endl;
	cout << "Menu:" << endl << "[1] Start new game :" << endl << "[2] Load previous game " << endl << endl;
	cin >> choice;
	if (choice < 1 || choice>2)
	{
		do
		{
			cout << " Invalid choice. Please select a choice between 1 and 2" << endl;
			cin >> choice;
		} while (choice < 1 || choice > 2);
	}//if choice is not 1 or 2

	//if choice is 1 FIRST 
	if (choice == 1)
	{
		cout << "----------USER PROFILE----------" << endl;
		acharacter->printProfile();
		cout << "----------USER PROFILE----------" << endl;
		cout << "Do you wish to create:" << endl;
		cout << "[1] Map" << endl << "[2] Default Map" << endl;
		cin >> choice;
		if (choice < 1 || choice>2)
			do
			{
			cout << "invalid choice, select between 1 and 2";
			cin >> choice;
			} while (choice < 1 || choice > 2);

		//create a map and display
		if (choice == 1)
		{
			//	cout << "Enter the quest name: " << endl;
			//	cin >> mapName;
			cout << "Set the map dimensions" << endl;
			cout << "Enter desired width" << endl;
			cin >> width;
			aMap->mapHeight = width;
			cout << "Enter desired height" << endl;
			cin >> height;
			aMap->mapHeight = height;
			aMap->displayMap();
			//editor->createMap(height, width, questName);
			//m = editor->current_map;

			//add objects to map

			do{//do while add object
				cout << "Select which object you want to add to the map" << endl;
				cout << "1 - Entry door [i]" << endl;
				cout << "2 - Exit door [o]" << endl;
				cout << "3 - walls [w]" << endl;
				cout << "4 - chest [c]" << endl;
				cout << "5 - characters [a]" << endl;
				cout << "0 - To Continue..." << endl << endl;
				do
				{
					cout << "Select between the options offered" << endl;
					cin >> choice;
				} while (choice < 0 || choice > 5);


				do{
					cout << "Select within the height and width of the map" << endl;
					cout << "Enter the x coordinate (starts from 0): " << endl;
					cin >> x;
					cout << "Enter the y coordinate (starts from 0): " << endl;
					cin >> y;
				} while (x >= aMap->mapWidth || y >= aMap->mapHeight || x < 0 || y < 0);

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
					break;
				}//switch
			} while (choice != 0); //do while add object
		}//if choice is 1
	}//if choice is 1 FIRST
}//end of function createMap




int main() {
		
		char name;
		char answer;
		int row, col;
		
		string questName;
		Character *c = new Character();
		Map *m= new Map(10, 10, "default");
	//	MapEditor *editor = new MapEditor();
		Item *myItem;
		createMap(c, m);		
			

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

		return 0;
	}






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