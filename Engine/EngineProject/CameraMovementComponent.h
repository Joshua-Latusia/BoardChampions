#pragma once
#include "Component.h"
#include "Listener.h"

#define M_PI 3.14159265358979323846 

class CameraMovementComponent : public Component, public Listener
{
private:
	void move(float angle, float fac);
	float speed;

public:
	bool keys[256];
	void listenMouseMoved(int mouseX, int mouseY) override;
	void listenKeyPressed(unsigned char key, int x, int y) override;
	void listenKeyReleased(unsigned char key, int x, int y) override;

	void init() override;
	void update(float dt) override;
	CameraMovementComponent(float speed);
	~CameraMovementComponent();
};

