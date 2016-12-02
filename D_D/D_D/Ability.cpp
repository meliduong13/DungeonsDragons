#include <string>
#include "Ability.h"
#include "Dice.h"
using namespace std;

Ability::Ability(string aName){
	name = aName;
	score = calculateScore();
	calculateModifier();
	//cout << "name = " << aName << " score = " << score << " modifier = " << modifier << endl;
}

Ability::Ability(string name, int score, float modifier)
{
	this->name = name;
	this->score = score;
	this->modifier = modifier;
}

// We are taking the best 3 out of 4 rolls
int Ability::calculateScore() {

	Dice* aDice = new Dice();
	const int scoreLength = 4;
	int scoreList[scoreLength];
	int totalScore = 0;

	for (int i = 0; i < scoreLength; i++) {
		scoreList[i] = aDice->roll("1d6[+0]");
		//cout << "scoreList[" << i << "] = " << scoreList[i] << endl;
		totalScore += scoreList[i];
	}

	int minScore = scoreList[0];
	for (int j = 1; j < scoreLength; j++) {
		if (scoreList[j] < minScore)
			minScore = scoreList[j];
	}

	//cout << "score = " << " totalScore = " << totalScore << " minScore = " << minScore << endl;
	return  totalScore - minScore;
}

//! Calculates the modifiyer of the character
void Ability::calculateModifier() {
	//cout << "+_+_+_+__++_+__+_+_+__+_+_+_+_++_+_++ HERE: " << " score : " << score << " modifier : " << floor(float((score - 10.0) / 2.0)) << endl;
	//cout << "modifier = " << floor((score - 10) / 2) << endl;
	modifier = floor(float((score - 10.0) / 2.0));
}

//! increases the score
//! @param score number to increase by
void Ability::incScore(int number) {
	score += number;
}