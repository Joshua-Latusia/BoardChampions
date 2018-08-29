#pragma once

#include "Component.h"
#include "Texture.h"

class DrawComponent : public Component
{
public:
	DrawComponent();
	DrawComponent(char* texPath);
	~DrawComponent();

	float size = 0;

	Texture* texture = nullptr;
	virtual void draw() = 0;
};

