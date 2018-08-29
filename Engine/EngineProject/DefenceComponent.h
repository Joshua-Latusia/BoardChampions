#pragma once
#include "DiceComponent.h"
#include "component.h"
class DefenceComponent: public Component
{

private:
	int defencePoints;
public:
	DefenceComponent(DiceComponent& dice , int basePoints);
	~DefenceComponent();
};

