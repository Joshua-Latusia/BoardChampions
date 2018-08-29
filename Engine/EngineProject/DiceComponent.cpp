#include "DiceComponent.h"
#include <stdlib.h> 
#include<time.h>


int Result = 0;

int DiceComponent::trowDice()
{
	
	Result = std::rand() % 6 + 1;
	
	return Result;
	std::cout << Result << std::endl;
}

DiceComponent::DiceComponent()
{
	srand(time(NULL));
}


DiceComponent::~DiceComponent()
{
}
