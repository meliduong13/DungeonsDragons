//! @file 
//! @brief CharacterBuilder class header file  
//!
#pragma once
#include "Character.h"
#include "Dice.h"
#include <vector>
using namespace std;

// Abstract class providing the structure for all concrete character builders
class CharacterBuilder
{
protected:
	//Product built by Character Builder
	Character* _ch;
	
	//These functions below are the many 'buildPart()'(s)
public:
	//get the built Character from the Builder
	Character* getCharacter(){ return _ch; }

	//------------------------------------------------------------------
	void swapValues(int& v1, int& v2) {
		int temp;
		temp = v1;
		v1 = v2;
		v2 = temp;
	}

	int indexOfSmallest(const int abilityScore[], int startIndex, int abilitySize) {
		int min = abilityScore[startIndex];
		int indexOfMin = startIndex;
		for (int index = startIndex + 1; index < abilitySize; index++)
			if (abilityScore[index] < min) {
			min = abilityScore[index];
			indexOfMin = index;
			// min is the smallest of abilityScore[startIndex] through abilityScore[index]
			}
		return indexOfMin;
	}

	void sort(int abilityScore[], int abilitySize) {
		int indexOfNextSmallest;
		for (int index = 0; index < abilitySize - 1; index++) {
			//Place the correct value in abilityScore[index]:
			indexOfNextSmallest = indexOfSmallest(abilityScore, index, abilitySize);
			swapValues(abilityScore[index], abilityScore[indexOfNextSmallest]);
		}


	}

	//------------------------------------------------------------------
	
	void createNewCh() { 
		_ch = new Character; 
	}

	void buildAbilities() {
		_ch->setAbilities();
	}

	void buildArmorClass() {
		_ch->setArmorClass();
	}

	void buildDamageBonus() {
		_ch->setDamageBonus();
	}

	void buildChType(string chType) {
		_ch->setCharacterType(chType);
	}
	
	void buildLevel(int level) {
		_ch->setLevel(level);
	}

	void buildHitPoints(int level) {
		_ch->setHitPoints(level);
	}

	void buildNbrOfAttacks(int level) {
		_ch->setNbrOfAttacks(level);
	}

	void buildAttackBonus(int level) {
		_ch->setAttackBonus(level);
	}

	void buildWornItems() {
		_ch->setWornItems();
	}

	void buildBackPack() {
		_ch->setBackPack();
	}

	void buildTreasureChest() {
		_ch->setTreasureChest();
	}

	//A buildPart() which is a common functionality of the builders that are extending the Character Builder abstract class
	//! Declaring createNewCh function which build a character which is filled with the appropriate score depending of the given chType
	virtual void buildCharacter() = 0;
};
