#include "CameraMovementComponent.h"
#include "Game.h"
#include "GameObject.h"
#include "GL\freeglut.h"


void CameraMovementComponent::move(float angle, float fac)
{
	Game::camera.posX += (float)cos((Game::camera.rotY + angle) / 180 * M_PI) * fac;
	Game::camera.posY += (float)sin((Game::camera.rotY + angle) / 180 * M_PI) * fac;
}

bool forced = false;
void CameraMovementComponent::listenMouseMoved(int mouseX, int mouseY)
{
	int dx = mouseX - Game::screen.width / 2;
	int dy = mouseY - Game::screen.height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400 && !forced)
	{
		Game::camera.rotX += dy / 10.0f;
		Game::camera.rotY += dx / 10.0f;
	}
	if (!forced)
	{
		glutWarpPointer(Game::screen.width / 2, Game::screen.height / 2);
		forced = true;
	}
	else
	{
		forced = false;
	}
}

void CameraMovementComponent::listenKeyPressed(unsigned char key, int x, int y)
{
	this->keys[key] = true;
}

void CameraMovementComponent::listenKeyReleased(unsigned char key, int x, int y)
{
	this->keys[key] = false;
}

void CameraMovementComponent::init()
{
	memset(this->keys, 0, sizeof(this->keys));
}

void CameraMovementComponent::update(float dt)
{
	if (this->keys['a']) { move(0, dt * speed);	}
	if (this->keys['d']) { move(180, dt * speed); }
	if (this->keys['w']) { move(90, dt * speed);	}
	if (this->keys['s']) { move(270, dt * speed); }
	if (this->keys['q']) { Game::camera.posZ -= speed * dt; }
	if (this->keys['e']) { Game::camera.posZ += speed * dt; }
	
	// TODO turn switching camera
	if (this->keys['1']) { Game::camera.posZ += 1; };
	if (this->keys['2']) {};
}

CameraMovementComponent::CameraMovementComponent(float speed)
{
	this->speed = speed;
}


CameraMovementComponent::~CameraMovementComponent()
{
}
