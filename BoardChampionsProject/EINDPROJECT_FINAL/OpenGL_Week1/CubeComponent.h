#pragma once

#include "DrawComponent.h"

class CubeComponent : public DrawComponent
{
	float size;
public:
	CubeComponent(float size);
	~CubeComponent();

	virtual void draw() override;
};

