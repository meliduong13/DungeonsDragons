//! @file 
//! @brief Dice class implementation file  

#include "Dice.h"
#include "Logger.h"

//! @param string : a string of the form "xdy[+z]".
//! @return an integer which is the addition of the value of all dice and return -1 when the expression dose not follow he right format
int Dice::roll(string rollString) {
	GameLogger::printEvent("rolling dice");
	bool checkRollStrMatched = true;
	checkRollString(rollString);

	if (checkRollStrMatched) {
		regex valueRegexGrouping("(\\d*)d(\\d*)\\[([\\+\\|-])(\\d+)\\]");
		smatch matches;

		string xMatchResult;
		string yMatchResult;
		string zMatchResult;
		string modifierMatchResult;


		if (std::regex_search(rollString, matches, valueRegexGrouping)) {
			//cout << "A match found\n";

			for (size_t i = 0; i < matches.size(); ++i) {
				// I know I have 4 groups
				if (i == 1){ xMatchResult = matches[i].str(); }
				if (i == 2){ yMatchResult = matches[i].str(); }
				if (i == 3){ modifierMatchResult = matches[i].str(); }
				if (i == 4){ zMatchResult = matches[i].str(); }
			}
		}
		else {
			cerr << "Match not found\n";
		}

		xRollValue = stoi(xMatchResult);
		yRollValue = stoi(yMatchResult);
		zRollValue = stoi(zMatchResult);
		modifierRollSign = modifierMatchResult;

		//setDiceValues(xRollValue, yRollValue, zRollValue, modifierRollSign);
		int result = rollDice(xRollValue, yRollValue, zRollValue, modifierRollSign);
		GameLogger::printEvent("dice roll resulted in " + to_string(result));
		return result;
	}
	else {
		cerr << "ERROR: Wrong Format!" << std::endl;
		exit(0);
	}
}

//! @param int, int, int, string: an x, y, z, modifier values
//! @return an integer which final result of rolling a dice
int Dice::rollDice(int xRollValue, int yRollValue, int zRollValue, string modifierRollSign){
	int diceresult;
	for (int i = 0; i<xRollValue; i++){
		sumDiceRolls += rand() % yRollValue + 1;
	}
	if (modifierRollSign == "+"){
		diceresult = sumDiceRolls + zRollValue;
		return diceresult;
	}
	else {
		diceresult = sumDiceRolls - zRollValue;
		return diceresult;
	}
}

//! Following the d20 rules you can have "-" modifier for rolling the dice, so the requirement of a roll string is in form of "xdy[+|-z]"
//! @param string : a string of the form "xdy[+z]".
//! @return an bool which is true if the paramter aRollString matched the requirement and false if the roll string does not match the requirement
bool Dice::checkRollString(string aRollString){
	//regex rollRegex("^\\d*d\\d{1,2}[4\\|6\\|8\\|10\\|12\\|20\\|100]\\[[\\+\\|-]\\d*\\]$");
	regex rollRegex("^(\\d+d[4|6|8]\\[[\\+\\|-]\\d*\\])|(\\d*d10\\[[\\+\\|-]\\d*\\])|(\\d*d12\\[[\\+\\|-]\\d*\\])|(\\d*d20\\[[\\+\\|-]\\d*\\])|(\\d*d100\\[[\\+\\|-]\\d*\\])");
	int regexResult = 0;
	regexResult = regex_match(aRollString, rollRegex);
	// Found the Correct Match.
	if (regexResult){
		// Correct Match.
		return true;
	}
	else{
		return false;
	}
}

//! Empty Constructor
Dice::Dice(){
	xRollValue = 0;
	yRollValue = 0;
	zRollValue = 0;
	modifierRollSign = "";
};

//! @param empty
//! @return an integer which is the x value of the roll string "xdy[+|-z]"
int Dice::getDiceX() { return xRollValue; }
//! @param empty
//! @return an integer which is the y value of the roll string "xdy[+|-z]"
int Dice::getDiceY() { return yRollValue; }
//! @param empty
//! @return an integer which is the z value of the roll string "xdy[+|-z]"
int Dice::getDiceZ() { return zRollValue; }

//! @param empty
//! @return an integer which is the modifier value "+|-" of the roll string "xdy[+|-z]"
string Dice::getDiceModifier() { return modifierRollSign; }

//! @param int, int, int, string: an x, y, z, modifier values
//! @return void
void Dice::setDiceValues(int xValue, int yValue, int zValue, string modifierSign){
	xRollValue = xValue;
	yRollValue = yValue;
	zRollValue = zValue;
	modifierRollSign = modifierSign;
}
