#pragma once
#include <string>
using namespace std;


class Ability {
protected:
	string name;
	int score;
	float modifier;

public:
	Ability(string aName);
	Ability(string name, int score, float modifier);
	int getScore() { return score; }
	void setScore(int aScore) { score = aScore; }
	void ArmorClass();
	void DamageBonus();
	//void AttackBonus();
	void incScore(int number);
	int getModifier() { return modifier; }
	string getName() { return name; }
	int calculateScore();
	void calculateModifier();
};