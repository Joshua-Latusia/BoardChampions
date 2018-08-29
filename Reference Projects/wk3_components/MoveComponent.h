#pragma once
#include "Component.h"
class MoveComponent : public Component
{
public:
	MoveComponent();
	MoveComponent(float newSpeed);
	~MoveComponent();

	float speed = 5.0f;

	void update(float elapsedTime) override;
};

