#pragma once
#include "DrawComponent.h"

class StatusComponent : public DrawComponent
{
public:

	float statusPoints = 0;


	StatusComponent();
	~StatusComponent();

	virtual void draw() override;

	
};

