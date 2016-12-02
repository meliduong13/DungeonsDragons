#include "Map.h"
#include "set"
#include <string> 
#include <locale>
#include <iostream>
using namespace std;
//IMPLEMENT_SERIAL(Map, Map, 1);

//! @file
//! @brief Implementation file for the Map class  
//!

void Map::addActor(string actorCode, Character* character)
{
	actors[actorCode] = character;
}

void Map::removeActor(string actorCode)
{
	actors.erase(actorCode);
}

Map::Map()
{
	Map(5, 5, "default");
}

//! Constructor which creates a new map with a specific size
//! @param height: the height of the map
//! @param width: the width of the map
Map::Map(int height, int width, std::string map_name)
{
	set = std::set<std::string>();
	mapHeight = height;
	mapWidth = width;
	map = new char*[height];
	Map::map_name = map_name;
	for (int i = 0; i < height; ++i)
	{
		map[i] = new char[width];
	}

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			map[i][j] = ' ';
		}
	}
}

//! Destructor that clears the class and deallocates memory
Map::~Map()
{
	delete map;
}

//! A helper function that recursively uses a dfs to find if there is a valid path
//! @return bool value, true of the map is valid (there is at least one clear path between the mandatory begin and end cell).
//! @param start_x: an integer value of the horizontal index of the starting point
//! @param start_y: an integer value of the vertical index of the starting point
//! @param end_x: an integer value of the horizontal index of the ending point
//! @param end_y: an integer value of the vertical index of the ending point
//! @param set: a reference to a set that stores the visited nodes 
bool Map::validate(int start_x, int start_y, int end_x, int end_y, std::set<std::string>& set)
{
	std::string placement = std::to_string(start_x) + "," + std::to_string(start_y);
	if (set.count(placement))
	{
		return false;
	}
	if (start_x == end_x && start_y == end_y) return true;
	if (map[start_y][start_x] == 'w') return false;
	int x[2];
	int y[2];
	x[0] = ((start_x == 0) ? start_x : start_x - 1);
	x[1] = ((start_x == mapWidth - 1) ? start_x : start_x + 1);
	y[0] = ((start_y == 0) ? start_y : start_y - 1);
	y[1] = ((start_y == mapHeight - 1) ? start_y : start_y + 1);
	set.insert(placement);

	bool result = false;

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (!(start_x == x[i] && start_y == y[j]) && !(set.count(std::to_string(x[i]) + "," + std::to_string(y[j]))))
			{
				result = result || validate(x[i], y[j], end_x, end_y, set);
			}
		}
	}

	return result;
}

//! Implementation of the map verification
//! @return bool value, true of the map is valid (there is at least one clear path between the mandatory begin and end cell).
//! @param start_x: an integer value of the horizontal index of the starting point
//! @param start_y: an integer value of the vertical index of the starting point
//! @param end_x: an integer value of the horizontal index of the ending point
//! @param end_y: an integer value of the vertical index of the ending point
bool Map::validatePath(int start_x, int start_y, int end_x, int end_y)
{
	set.clear();
	return validate(start_x, start_y, end_x, end_y, set);
}


//! The validates the path at the set starting and ending points
//! @return bool value that indicates whether there is a valid at the set start and end points.
bool Map::validatePath()
{
	return validatePath(start_point_x, start_point_y, end_point_x, end_point_y);
}


//! Tries to set the end points
//! @param x: an integer value of the horizontal index of the starting point
//! @param y: an integer value of the vertical index of the starting point
//! @return bool whether the start point is valid
bool Map::trySetEndPoint(int end_x, int end_y)
{
	if (end_x < 0 || end_x >= mapWidth || end_y < 0 || end_y >= mapHeight)
	{
		return false;
	}

	end_point_x = end_x;
	end_point_y = end_y;
	return true;
}


//! Tries to set the start points
//! @param x: an integer value of the horizontal index of the starting point
//! @param y: an integer value of the vertical index of the starting point
//! @return bool whether the start point is valid
bool Map::trySetStartPoint(int start_x, int start_y)
{
	if (start_x < 0 || start_x >= mapWidth || start_y < 0 || start_y >= mapHeight)
	{
		return false;
	}

	start_point_x = start_x;
	start_point_y = start_y;
	return true;
}

//! Implementation of fill cell, set any cell to anything it might eventually contain
//! @param x: an integer value of horizontal index of the map's grid
//! @param y: an integer value of vertical index of the map's grid
//! @param obj: a character value of object that fills the cell
void Map::fillCell(int x, int y, char obj)
{
	//Prevents the user from going out of bounds or rewriting a occupied space
	if ((x > mapWidth || y > mapHeight || y < 0 || x < 0))
	{
		return;
	}

	map[y][x] = obj;

}

//! Implementation occupation of a cell, check if a cell is occupied
//! @param x: an integer value of horizontal index of the map's grid
//! @param y: an integer value of vertical index of the map's grid
//! @return : a boolean true if the cell is occupeid false otherwise
bool Map::isOccupied(int x, int y)
{
	if (map[y][x] != ' ') {
		return true;
	}
	return false;
}

//! Implementation of getting a character from a cell
//! @param x: an integer value of horizontal index of the map's grid
//! @param y: an integer value of vertical index of the map's grid
//! @return : a character value of what's at the map cell
char Map::getCharacter(int x, int y)
{
	return map[x][y];
}

//! Moves the character up in the map
//! @return a boolean indicating that the character can move up
bool Map::moveUp(){
	if (player_y == 0 || map[player_y - 1][player_x] == 'w' || map[player_y - 1][player_x] == 'a' || map[player_y - 1][player_x] == 'c'){
		return false;
	}
	map[player_y][player_x] = ' ';
	player_y--;
	map[player_y][player_x] = 'p';
	return true;
}

//! Moves the character down in the map
//! @return a boolean indicating that the character can move down
bool Map::moveDown(){
	if (player_y == mapHeight - 1 || map[player_y + 1][player_x] == 'w' || map[player_y + 1][player_x] == 'a' || map[player_y + 1][player_x] == 'c'){
		return false;
	}
	map[player_y][player_x] = ' ';
	player_y++;
	map[player_y][player_x] = 'p';
	return true;
}

void Map::setCharacterAtStartingPoint()
{
	map[start_point_y][start_point_x] = 'p';
}

//! Moves the character right in the map
//! @return a boolean indicating that the character can move right 
bool Map::moveRight(){
	if (player_x == mapWidth - 1 || map[player_y][player_x + 1] == 'w' || map[player_y][player_x + 1] == 'a' || map[player_y][player_x + 1] == 'c')
	{
		return false;
	}
	map[player_y][player_x] = ' ';
	player_x++;
	map[player_y][player_x] = 'p';
	return true;
}

//! Moves the character left in the map
//! @return a boolean indicating that the character can move left 
bool Map::moveLeft(){
	if (player_x == 0 || map[player_y][player_x - 1] == 'w' || map[player_y][player_x - 1] == 'a' || map[player_y][player_x - 1] == 'c'){
		return false;
	}
	map[player_y][player_x] = ' ';
	player_x--;
	map[player_y][player_x] = 'p';
	return true;
}

bool Map::enemyMoveUp() {
	if (player_y == 0) {
		return false;
	}
	map[enemy_y][enemy_x] = ' ';
	enemy_y--;
	map[enemy_y][enemy_x] = 'E';
	return true;
}

//! Moves the character down in the map
//! @return a boolean indicating that the character can move down
bool Map::enemyMoveDown() {
	if (enemy_y == mapHeight - 1) {
		return false;
	}
	map[enemy_y][enemy_x] = ' ';
	enemy_y++;
	map[enemy_y][enemy_x] = 'E';
	return true;
}

void Map::setEnemyAtStartingPoint()
{
	map[mapHeight - 1][mapWidth - 1] = 'E';
	enemy_x = mapHeight - 1;
	enemy_y = mapWidth - 1;
}

//! Moves the character right in the map
//! @return a boolean indicating that the character can move right 
bool Map::enemyMoveRight() {
	if (enemy_x == mapWidth - 1)
	{
		return false;
	}
	map[enemy_y][enemy_x] = ' ';
	enemy_x++;
	map[enemy_y][enemy_x] = 'E';
	return true;
}

//! Moves the character left in the map
//! @return a boolean indicating that the character can move left 
bool Map::enemyMoveLeft() {
	if (enemy_x == 0) {
		return false;
	}
	map[enemy_y][enemy_x] = ' ';
	enemy_x--;
	map[enemy_y][enemy_x] = 'E';
	return true;
}

//! Displays the map and clears the map before displaying
//! the character at a new position
void Map::displayMap()
{
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			cout << "[";
			cout << map[i][j];
			cout << "]";

		}
		cout << endl;
	}
}
