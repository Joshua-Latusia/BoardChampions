#pragma once

#include "Listener.h"
#include "Component.h"



class KeyboardMovementComponent : public Component, public Listener
{
private:
	void move(float angle, float fac);
public:

	void listenKeyPressed(unsigned char key, int x, int y) override;
	void init() override;
	KeyboardMovementComponent();
	~KeyboardMovementComponent();
};

