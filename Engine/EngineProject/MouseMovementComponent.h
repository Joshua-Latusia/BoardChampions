#pragma once
#include "Component.h"
#include "Listener.h"

class MouseMovementComponent : public Component, public Listener
{
public:
	void listenMouseMoved(int mouseX, int mouseY) override;

	MouseMovementComponent();
	~MouseMovementComponent();
};

