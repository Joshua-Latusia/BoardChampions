#include "DefenceComponent.h"







DefenceComponent::DefenceComponent(DiceComponent & dice, int basePoints)
{
	defencePoints = basePoints;
	DiceComponent defenceDice = dice;
	int defenceDiceTrow = defenceDice.trowDice();
	int TotaldefencePoints = defencePoints + defenceDiceTrow;
	std::cout << "DefenceDice result is: " << defenceDiceTrow << std::endl;
	std::cout << "Total number of defence points  is: " << TotaldefencePoints << std::endl;
}

DefenceComponent::~DefenceComponent()
{
}
