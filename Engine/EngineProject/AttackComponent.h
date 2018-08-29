#pragma once
#include "DiceComponent.h"
#include "Component.h"
class AttackComponent : public Component
{

private:
	int attackPoints;
public:
	
	AttackComponent(DiceComponent& dice, int basePoints);
	~AttackComponent();
};

