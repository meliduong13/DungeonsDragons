#include "MapEditor.h"
#include <fstream>
#include <map>
#include <iostream>
#include <windows.h>

bool MapEditor::createMap(int hight, int width, std::string map_name)
{
	current_map = new Map(hight, width, map_name);
	return saveMap(map_name);
}

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
		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				char c = myfile.get();
				current_map->fillCell(i, j, c);
			}
		}
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

		myfile.close();
		return true;
	}


	return false;
}

bool MapEditor::saveMap(std::string mapName)
{
	if (!current_map->validatePath()) return false;

	std::ofstream myfile(mapName);
	if (myfile.is_open())
	{
		myfile << current_map->map_name << "\n";
		myfile << current_map->mapWidth << "\n" << current_map->mapHeight << "\n";
		for (int i = 0; i < current_map->mapHeight; ++i)
		{
			for (int j = 0; j < current_map->mapWidth; ++j)
			{
				myfile << current_map->getCharacter(i, j);
			}
		}
		myfile << "\n";
		myfile << current_map->start_point_x << "\n" << current_map->start_point_y << "\n" << current_map->end_point_x << "\n" << current_map->end_point_y << "\n";
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
