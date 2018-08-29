#pragma once

#include "DrawComponent.h"
class PlayingFieldComponent : public DrawComponent
{
private:
	float size;

public:
	PlayingFieldComponent(float newSize);
	PlayingFieldComponent(float newSize, char* texPath);
	~PlayingFieldComponent();

	void draw() override;
};

