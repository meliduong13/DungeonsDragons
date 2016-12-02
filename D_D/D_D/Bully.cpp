//! @file 
//! @brief Bully implementation class  
//!
#pragma once
#include "Bully.h"
#include <iostream>
using namespace std;


//! Implementation create a character according of specified type (Bully)
//! @param chType: 
//! @return void: this function creates a character from a given character type (Bully) 
void Bully::buildCharacter() {

	const int abilitySize = 6;//_ch->getAbilities.size() - 3;
	int abilityScore[abilitySize];

	// 1. put abilities on array
	abilityScore[0] = _ch->getAbility("Strength")->getScore();
	abilityScore[1] = _ch->getAbility("Constitution")->getScore();
	abilityScore[2] = _ch->getAbility("Dexterity")->getScore();
	abilityScore[3] = _ch->getAbility("Intelligence")->getScore();
	abilityScore[4] = _ch->getAbility("Wisdom")->getScore();
	abilityScore[5] = _ch->getAbility("Charisma")->getScore();

	// 2. sort the array scores from MIN is index 0 ---> MAX is index 5
	sort(abilityScore, abilitySize);

	// 3. affect the good score to the good ability
	// Order of creating the character: Strength, Constitution, Dexterity, Intelligence, Wisdom, Charisma
	// Order of prefrences for Bully: Strength, Constitution, Dexterity, Intelligence, Charisma, Wisdom

	_ch->getAbility("Wisdom")->setScore(abilityScore[0]);
	_ch->getAbility("Charisma")->setScore(abilityScore[1]);
	_ch->getAbility("Intelligence")->setScore(abilityScore[2]);
	_ch->getAbility("Dexterity")->setScore(abilityScore[3]);
	_ch->getAbility("Constitution")->setScore(abilityScore[4]);
	_ch->getAbility("Strength")->setScore(abilityScore[5]);
}