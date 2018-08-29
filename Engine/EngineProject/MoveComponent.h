#pragma once
#include "Component.h"
#include "KeyListener.h"
#include "FieldComponent.h"
#include "PlayingFieldComponent.h"



class MoveComponent : public Component, public KeyListener
{
private:
	FieldComponent* targetField;
	FieldComponent* currentField;
	float speed;
	enum direction { UP, DOWN, LEFT, RIGHT };
	enum states { MOVE_X, MOVE_Y, IDLE, };
	int player;
	direction directionX;
	direction directionY;
	states state;
	bool moveY(MoveComponent::direction d, float elapsedTime);
public:
	bool done;
	MoveComponent();
	MoveComponent(float newSpeed);
	~MoveComponent();
	void CheckMovement();
	void update(float elapsedTime) override;
	bool moveX(MoveComponent::direction, float elapsedTime);
	void centerObject();
	void setTarget(int x, int y);
};
