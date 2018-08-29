#pragma once
#include <stdlib.h> 
#include <iostream>
#include "GameObject.h"

class DiceGameObject : public GameObject
{
public:
	static int Dice1;
	static int Dice2;

	void static rollDices();
	void static DrawDices();

	void init() override;
	void update(float elapsedTime) override;

	DiceGameObject();
	~DiceGameObject();
};

