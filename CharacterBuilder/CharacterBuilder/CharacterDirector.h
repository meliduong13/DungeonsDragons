//! @file 
//! @brief CharacterDirector class header file
//!

#pragma once
#include "CharacterBuilder.h"
#include <iostream>
using namespace std;

class CharacterDirector
{
private:
	CharacterBuilder* chBuilder;

public:
	//! Declaring a default CharacterDirector constructor


	//! Declaring getter function to get the constructed Character
	Character * getCharacter() {
		return chBuilder->getCharacter();
	}

	//! Declaring setCharacterBuilder function which uses a concrete builder for building a specific kind of Character of type fighter class
	void setCharacterBuilder(CharacterBuilder* _chbuilder) {
		chBuilder = _chbuilder;
	}

	//! Declaring constructCharacter function which is a creational process (calling the buildPart()s) to create a character using the builder. 
	void constructCharacter(int level, string chType) {
		chBuilder->createNewCh();
		chBuilder->buildAbilities();
		chBuilder->buildArmorClass();
		chBuilder->buildDamageBonus();
		chBuilder->buildChType(chType);
		chBuilder->buildLevel(level);
		chBuilder->buildHitPoints(level);
		chBuilder->buildNbrOfAttacks(level);
		chBuilder->buildAttackBonus(level);
		chBuilder->buildWornItems();
		chBuilder->buildBackPack();
		chBuilder->buildTreasureChest();
		chBuilder->buildCharacter();
	}
};
