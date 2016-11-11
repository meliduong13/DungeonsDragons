#pragma once
#include "Map.h"
#include <vector>

class MapEditor
{
public:
	Map* current_map;
	bool createMap(int hight, int width, std::string map_name);
	bool loadMap(std::string mapName);
	bool saveMap(std::string mapName);
	std::set<std::string> getMaps();
};

