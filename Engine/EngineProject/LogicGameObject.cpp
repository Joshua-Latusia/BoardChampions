#include "LogicGameObject.h"

void LogicGameObject::init()
{
	for (Component* comp : components)
	{
		comp->init();
	}
}

void LogicGameObject::update(float elapsedTime)
{
	for (Component* comp : components)
	{
		comp->update(elapsedTime);
	}

	position.x += velocity.x * elapsedTime;
	position.y += velocity.y * elapsedTime;
	position.z += velocity.z * elapsedTime;
}

LogicGameObject::LogicGameObject()
{
}

LogicGameObject::~LogicGameObject()
{
}
