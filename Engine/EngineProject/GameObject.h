#pragma once

#include <list>
#include "Vec.h"
#include "DrawComponent.h"
#include "Component.h"
#include <string>

class GameObject
{
protected:
	DrawComponent* drawComponent = nullptr;

public:
	GameObject();
	~GameObject();

	std::list<Component*> components;
	Vec3fl position;
	Vec3fl rotation;
	Vec3fl scale = Vec3fl(1.0f,1.0f,1.0f);
	Vec3fl velocity;

	template<typename TComp> TComp getComponent(std::string name);

	void addComponent(Component* component);
	virtual void init();
	virtual void update(float elapsedTime);
	virtual void draw();
};

template<typename TComp> TComp GameObject::getComponent(std::string name)
{
	for (Component* comp : components)
	{
		if (dynamic_cast<TComp>(comp) != nullptr)
		{
			return (dynamic_cast<TComp>(comp));
		}
	}
}
