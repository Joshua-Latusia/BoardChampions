#pragma once

#include "DrawComponent.h"

class CubeComponent : public DrawComponent
{
public:
	CubeComponent(float size);
	~CubeComponent();

	virtual void draw() override;
};

