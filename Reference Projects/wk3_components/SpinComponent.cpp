#include "SpinComponent.h"
#include "GameObject.h"


SpinComponent::SpinComponent(float speed)
{
	this->speed = speed;
}


SpinComponent::~SpinComponent()
{
}

void SpinComponent::update(float elapsedTime)
{
	//gameObject->rotation.x += elapsedTime * speed;
	//gameObject->rotation.y += elapsedTime * speed;
	gameObject->rotation.z += elapsedTime * speed;
}
