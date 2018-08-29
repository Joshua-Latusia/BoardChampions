#include "MoveComponent.h"
#include "GameObject.h"
#include <iostream>

float M_PI = 3.14159265358979323846f;
float lastAngle;
float degTurned = 0;

MoveComponent::MoveComponent()
{
	done = false;
}

MoveComponent::MoveComponent(float newSpeed)
{
	speed = newSpeed;
	done = false;
	state = IDLE;
}

MoveComponent::~MoveComponent()
{
}


void MoveComponent::update(float elapsedTime)
{
	switch (state)
	{
	case MOVE_Y:
		if (moveY(directionY, elapsedTime))
			state = MOVE_X;
		break;

	case MOVE_X:
		if (moveX(directionX, elapsedTime))
			state = IDLE;
		break;

	case IDLE:
		done = true;
		break;
	}
}


bool MoveComponent::moveX(MoveComponent::direction d, float elapsedTime)
{
	switch (d)
	{
	case LEFT:
		gameObject->position.x += speed * elapsedTime;
		if (gameObject->position.x >= targetField->middleX)
			return true;
		break;

	case RIGHT:
		gameObject->position.x -= speed * elapsedTime;
		if (gameObject->position.x <= targetField->middleX)
			return true;
		break;
	}

	return false;
}

bool MoveComponent::moveY(MoveComponent::direction d, float elapsedTime)
{
	switch (d)
	{
	case UP:
		gameObject->position.z += speed * elapsedTime;
		if (gameObject->position.z >= targetField->middleY)
			return true;
		break;

	case DOWN:
		gameObject->position.z -= speed * elapsedTime;
		if (gameObject->position.z <= targetField->middleY)
			return true;
		break;
	}

	return false;
}

void MoveComponent::centerObject()
{
	currentField = PlayingFieldComponent::getfieldComponent(this->gameObject->position.x, this->gameObject->position.z);
	gameObject->position.x = currentField->middleX;
	gameObject->position.z = currentField->middleY;
}


void MoveComponent::setTarget(int x, int y)
{
	centerObject();
	targetField = PlayingFieldComponent::fields[x][y];
	currentField = PlayingFieldComponent::getfieldComponent(this->gameObject->position.x, this->gameObject->position.z);

	done = false;
	//if (targetField->red == 1.0f && targetField->green == 0.0f && targetField->filled == true)
	//{


		float dx = targetField->middleX - currentField->middleX;
		float dy = targetField->middleY - currentField->middleY;
		if (dy > 0)
			directionY = UP;
		else
			directionY = DOWN;
		if (dx > 0)
			directionX = LEFT;
		else
			directionX = RIGHT;

		state = MOVE_Y;
	//}
	//else
	//{
	//	std::cout << "not a legit move " << std::endl;
	//}
}








