//! @file 
//! @brief Nimble class header file
//!

#pragma once
#include "CharacterBuilder.h"

class Nimble : public CharacterBuilder {

public:

	//! Declaring createNewCh function which is inherited from the abstract class CharacterBuilder
	virtual void buildCharacter();
};
