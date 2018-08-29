#pragma once
#include "GameObject.h"

class InputSystem;

class InputGameObject : public GameObject
{
public:
	InputSystem* inputSystem;

	InputGameObject(InputSystem* inputSystem);
	~InputGameObject();

	void init() override;
	void update(float elapsedTime) override;
};

