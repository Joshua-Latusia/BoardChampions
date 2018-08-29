#include "InputGameObject.h"
#include "InputSystem.h"

InputGameObject::InputGameObject(InputSystem* inputSystem)
{
	this->inputSystem = inputSystem;
}

InputGameObject::~InputGameObject()
{
	
}

void InputGameObject::init()
{
	for (Component* comp : components)
	{
		comp->init();
	}
}

void InputGameObject::update(float elapsedTime)
{
	for (Component* comp : components)
	{
		comp->update(elapsedTime);
	}
}
