#pragma once
#include <set>
#include <string>
#include "Character.h"
#include <map>


//! @file 
//! @brief the implementation of the D&D map class
//! The map is reprented by a 2d array grid of characters.
//! This class has getters and setters, with several methods to check the game board. 
//! 
//! Game rules: The D&D game rules does not allow for 2 characters per space and has to have a valid game board. 
//!		for a game board to be valid it needs to have a clear path without walls. Characters can pass through anything
//!		other than walls. 
//!
//! Implementation details: In order to check if there would be a valid path from the start to end position I used a 
//!		depth first search inside the array going diagonally, horizontally, and vertically. I used a set to keep track
//!		of the locations that I already visited. 
//!
//!	Libraries used: I used the C++ STD library for the set collection and string functions
class Map //: public CObject
{
private:
	std::set<std::string> set;
	bool validate(int start_x, int start_y, int end_x, int end_y, std::set<std::string>& set);
	map<string, Character*> actors;
public:
	char** map;

	int player_x;
	int player_y;
	int enemy_x;
	int enemy_y;
	int mapWidth;
	int mapHeight;
	int start_point_x;
	int start_point_y;
	int end_point_x;
	int end_point_y;
	void addActor(string actorCode, Character* character);
	void removeActor(string actorCode);
	Map();
	Map(int height, int width, std::string map_name);
	~Map();
	std::map<string, Character*> getActors() { return actors; }
	Character* getActor(string actor) { return actors[actor]; }
	std::string map_name;
	bool validatePath(int start_x, int start_y, int end_x, int end_y);
	bool validatePath();
	bool trySetEndPoint(int end_x, int end_y);
	bool trySetStartPoint(int start_x, int start_y);
	void fillCell(int x, int y, char obj);
	bool isOccupied(int x, int y);
	char getCharacter(int x, int y);
	void displayMap();
	bool moveLeft(string code);
	bool enemyMoveUp();
	bool moveUp(string code);
	bool enemyMoveDown();
	void setEnemyAtStartingPoint();
	bool enemyMoveRight();
	bool enemyMoveLeft();
	string canAttack(string code);
	bool moveDown(string code);
	void setCharacterAtStartingPoint();
	bool moveRight(string code);
};

