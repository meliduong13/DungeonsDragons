//! @file 
//! @brief Tank class header file
//!

#pragma once
#include "CharacterBuilder.h"

class Tank : public CharacterBuilder {

public:

	//! Declaring createNewCh function which is inherited from the abstract class CharacterBuilder
	virtual void buildCharacter();
};
