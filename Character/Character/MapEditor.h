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
public:
	Map* current_map;
	bool createMap(int hight, int width, std::string map_name);
	bool loadMap(std::string mapName);
	bool saveMap(std::string mapName);
	std::set<std::string> getMaps();
};

