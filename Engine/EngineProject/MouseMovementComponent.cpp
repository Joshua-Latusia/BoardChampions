#include "MouseMovementComponent.h"
#include "GameObject.h"


void MouseMovementComponent::listenMouseMoved(int mouseX, int mouseY)
{
	this->gameObject->rotation.z = mouseX;
}

MouseMovementComponent::MouseMovementComponent()
{
}


MouseMovementComponent::~MouseMovementComponent()
{
}
