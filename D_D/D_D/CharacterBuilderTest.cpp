//! @file 
//! @brief Test Class implementation for CharacterDirector class  
//!
/**
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>

#include "Character.h"
#include "CharacterDirector.h"
#include "CharacterBuilder.h"
#include "Nimble.h"
#include "Bully.h"
#include "Tank.h"

#include <iostream>
#include <string>

using namespace CppUnit;
using namespace std;


//! Test Class for the CharacterDirector class
class TestCharacterBuilder : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestCharacterBuilder);
	CPPUNIT_TEST(testNimble); //test if the score order of preferences for Nimble abilities
	CPPUNIT_TEST(testTank); //test if the score order of preferences for Tank abilities
	CPPUNIT_TEST(testBully); //test if the score order of preferences for Bully abilities
	CPPUNIT_TEST(testVariousLevel); //test if Nimble/Tank/Bully's level is set correctly
	CPPUNIT_TEST_SUITE_END();
protected:
	void testNimble();
	void testTank();
	void testBully();
	void testVariousLevel();
};

//! cppunit test cases registration
CPPUNIT_TEST_SUITE_REGISTRATION(TestCharacterBuilder);

//! Testing the correctness of createNewCh function using the CharacterDirector class to construct the character
//! Test Case: construction of a Nimble character
//! Tested item: CharacterDirector::constructCharacter()
void TestCharacterBuilder::testNimble()
{
	CharacterDirector chDirector;
	bool result;
	int level = 1;
	////Create the Concrete Builder Nimble
	CharacterBuilder* nimble = new Nimble;
	////Tell the CharacterDirector which Concrete Builder to use
	chDirector.setCharacterBuilder(nimble);
	////Tell the Director to construct
	chDirector.constructCharacter(level, "friendly");
	////We are getting the character of nimble
	Character* _ch = chDirector.getCharacter();

	////We are checking if the score of nimble abilities are decreasing in order from highest to lowest.
	result = _ch->getAbility("Dexterity")->getScore() >= _ch->getAbility("Constitution")->getScore();
	CPPUNIT_ASSERT(true == result);
	

	result = _ch->getAbility("Constitution")->getScore() >= _ch->getAbility("Strength")->getScore();
	CPPUNIT_ASSERT(true == result);

	result = _ch->getAbility("Strength")->getScore() >= _ch->getAbility("Intelligence")->getScore();
	CPPUNIT_ASSERT(true == result);

	result = _ch->getAbility("Intelligence")->getScore() >= _ch->getAbility("Charisma")->getScore();
	CPPUNIT_ASSERT(true == result);

	result = _ch->getAbility("Charisma")->getScore() >= _ch->getAbility("Wisdom")->getScore();
	CPPUNIT_ASSERT(true == result);

	delete nimble;
	delete _ch;
}

// For testing purposes


//! Testing the correctness of createNewCh function using the CharacterDirector class to construct the character
//! Test Case: construction of a Tank character
//! Tested item: CharacterDirector::constructCharacter()
void TestCharacterBuilder::testTank()
{
	CharacterDirector chDirector;
	bool result;
	int level = 1;
	//Create the Concrete Builder Tank
	CharacterBuilder* tank = new Tank();
	//Tell the CharacterDirector which Concrete Builder to use
	chDirector.setCharacterBuilder(tank);
	//Tell the Director to construct
	chDirector.constructCharacter(level, "friendly");
	//We are getting the character of tank
	Character* _ch = chDirector.getCharacter();

	//We are checking if the score of tank abilities are decreasing in order from highest to lowest.
	result = _ch->getAbility("Constitution")->getScore() >= _ch->getAbility("Dexterity")->getScore();
	CPPUNIT_ASSERT(true == result);

	result = _ch->getAbility("Dexterity")->getScore() >= _ch->getAbility("Strength")->getScore();
	CPPUNIT_ASSERT(true == result);

	result = _ch->getAbility("Strength")->getScore() >= _ch->getAbility("Intelligence")->getScore();
	CPPUNIT_ASSERT(true == result);

	result = _ch->getAbility("Intelligence")->getScore() >= _ch->getAbility("Charisma")->getScore();
	CPPUNIT_ASSERT(true == result);

	result = _ch->getAbility("Charisma")->getScore() >= _ch->getAbility("Wisdom")->getScore();
	CPPUNIT_ASSERT(true == result);

	delete tank;
	delete _ch;
}

//! Testing the correctness of createNewCh function using the CharacterDirector class to construct the character
//! Test Case: construction of a Bully character
//! Tested item: CharacterDirector::constructCharacter()
void TestCharacterBuilder::testBully()
{
	CharacterDirector chDirector;
	bool result;
	int level = 1;
	//Create the Concrete Builder Bully
	CharacterBuilder* bully = new Bully();
	//Tell the CharacterDirector which Concrete Builder to use
	chDirector.setCharacterBuilder(bully);
	//Tell the Director to construct
	chDirector.constructCharacter(level, "friendly");
	//We are getting the character of bully
	Character* _ch = chDirector.getCharacter();

	//We are checking if the score of bully abilities are decreasing in order from highest to lowest.
	result = _ch->getAbility("Strength")->getScore() >= _ch->getAbility("Constitution")->getScore();
	CPPUNIT_ASSERT(true == result);

	result = _ch->getAbility("Constitution")->getScore() >= _ch->getAbility("Dexterity")->getScore();
	CPPUNIT_ASSERT(true == result);

	result = _ch->getAbility("Dexterity")->getScore() >= _ch->getAbility("Intelligence")->getScore();
	CPPUNIT_ASSERT(true == result);

	result = _ch->getAbility("Intelligence")->getScore() >= _ch->getAbility("Charisma")->getScore();
	CPPUNIT_ASSERT(true == result);

	result = _ch->getAbility("Charisma")->getScore() >= _ch->getAbility("Wisdom")->getScore();
	CPPUNIT_ASSERT(true == result);

	delete bully;
	delete _ch;
}

//! Testing the correctness of createNewCh function using the CharacterDirector class to construct the character and 
//! Test Case: construction of a Nimble character
//! Tested item: CharacterDirector::constructCharacter()
void TestCharacterBuilder::testVariousLevel()
{
	int level = 1;
	for (int i = 1; i < 21; i++){
		level = i;
		CharacterDirector chDirector;
		bool result;
		//Create the Concrete Builder Nimble
		CharacterBuilder* nimble = new Nimble();
		//Tell the CharacterDirector which Concrete Builder to use
		chDirector.setCharacterBuilder(nimble);
		//Tell the Director to construct
		chDirector.constructCharacter(level, "friendly");
		//We are getting the character of nimble
		Character* _ch = chDirector.getCharacter();

		//We are checking if the level nimble is set correctly
		result = _ch->getLevel() == i;
			CPPUNIT_ASSERT(true == result);

		//We are checking if the nimble hit points is bigger than the min roll dice (1d10) used to calculate the hit point
		result = _ch->getHitPoints() >= i;
			CPPUNIT_ASSERT(true == result);

		delete nimble;
		delete _ch;
	}

}

**/
