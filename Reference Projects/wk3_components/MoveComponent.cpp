#include "MoveComponent.h"
#include "GameObject.h"

extern bool keys[256];

MoveComponent::MoveComponent()
{

}

MoveComponent::MoveComponent(float newSpeed)
{
	speed = newSpeed;
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::update(float elapsedTime)
{
	if (keys['d']){ gameObject->position.x += speed * elapsedTime; }
	if (keys['a']){ gameObject->position.x -= speed * elapsedTime; }
	if (keys['w']) { gameObject->position.y += speed * elapsedTime; }
	if (keys['s']) { gameObject->position.y -= speed * elapsedTime; }
}


