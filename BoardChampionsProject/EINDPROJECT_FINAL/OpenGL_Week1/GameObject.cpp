#include "GameObject.h"
#include "DrawComponent.h"
#include <GL/freeglut.h>

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::addComponent(Component * component)
{
	component->setGameObject(this);
	components.push_back(component);

	if (!drawComponent)
		drawComponent = dynamic_cast<DrawComponent*>(component);
}


void GameObject::draw()
{
	if (!drawComponent)
		return;

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);
	glScalef(scale.x, scale.y, scale.z);
	drawComponent->draw();
	glPopMatrix();
}

void GameObject::update(float elapsedTime)
{
	for (auto &c : components)
		c->update(elapsedTime);
}