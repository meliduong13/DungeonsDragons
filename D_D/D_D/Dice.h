//! @file 
//! @brief Dice class header file 
#pragma once 
#ifndef INC_345_DICE_H
#define INC_345_DICE_H
#endif //INC_345_DICE_H


#include <random>
#include <regex>
#include <iostream>
using namespace std;

class Dice
{
private:
	int xRollValue, yRollValue, zRollValue;
	string modifierRollSign;
	int sumDiceRolls = 0;

public:
	//! Empty Constructor
	Dice();

	//! Declaring getter to get x value"
	int getDiceX();
	//! Declaring getter to get y value"
	int getDiceY();
	//! Declaring getter to get z value"
	int getDiceZ();
	//! Declaring getter to get modifier value"
	string getDiceModifier();

	//! Declaring setter to set x, y, z, and modifier values"
	void setDiceValues(int xValue, int yValue, int zValue, string modifierSign);

	//! Declaring checkRollString function"
	bool checkRollString(string aRollString);

	//! Declaring roll function"
	int roll(string rollString);

	//! Declaring rollDice function"
	int rollDice(int xRollValue, int yRollValue, int zRollValue, string modifierRollSign);
};

