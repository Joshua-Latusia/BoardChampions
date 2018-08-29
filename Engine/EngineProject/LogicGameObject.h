#pragma once

#include "GameObject.h"

class GameLogicSystem;

class LogicGameObject : public GameObject
{
public:
	GameLogicSystem* gameLogicSystem;

	void init() override;
	void update(float elapsedTime) override;

	LogicGameObject();
	~LogicGameObject();
};

