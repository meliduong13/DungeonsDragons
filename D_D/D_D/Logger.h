#pragma once
#include <string>
#include <fstream>

using namespace std;
namespace GameLogger
{
	static bool enabled;
	static void printEvent(string event)
	{
		if (!enabled)
		{
			return;
		}

		std::ofstream myfile;
		myfile.open("game_log.txt", std::ofstream::out | ios_base::app);
		if (myfile.is_open())
		{
			myfile << event << "\n";
		}

		myfile.close();
	}
}

