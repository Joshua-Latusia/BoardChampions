#include "DiceGameObject.h"




void DiceGameObject::rollDices()
{
	Dice1 = rand() % 6 + 1;
	Dice2 = rand() % 6 + 1;
	std::cout << Dice1 << std::endl;
}

void DiceGameObject::DrawDices()
{
}


void DiceGameObject::init()
{
	rollDices();
}

void DiceGameObject::update(float elapsedTime)
{
}

DiceGameObject::DiceGameObject()
{
}


DiceGameObject::~DiceGameObject()
{
}
