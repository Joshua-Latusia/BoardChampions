#pragma once
#include "Component.h"
#include <iostream>
class DiceComponent : public Component
{
public:
	int trowDice();
	DiceComponent();
	~DiceComponent();
};

