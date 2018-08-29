#include "AttackComponent.h"



AttackComponent::AttackComponent(DiceComponent & dice, int basePoints)
{
	attackPoints = basePoints;
	DiceComponent attackDice = dice;
	int attackDiceTrow = attackDice.trowDice();
	int TotalAttackPoints = attackPoints + attackDiceTrow;
	std::cout << "attackDice result is : " << attackDiceTrow << std::endl;
	std::cout << "Total number of attack points is: " << TotalAttackPoints << std::endl;
}

AttackComponent::~AttackComponent()
{
}
