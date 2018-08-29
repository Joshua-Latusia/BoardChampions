#include "InputSystem.h"
#include <GL/freeglut.h>
#include "InputComponent.h"
#include "KeyboardMovementComponent.h"
#include "ComputerVisionComponent.h"
#include "CameraMovementComponent.h"
#include "Game.h"

void InputSystem::init()
{
	/*Adds all the objects to the inputsystem*/
	systemInit();

	/*Calls init function of every object*/
	objectInit();
}

void InputSystem::systemInit()
{
	/*KeyboardObj handles all the input that is entered through keyboard input*/
	InputGameObject* keyboardObj = new InputGameObject(this);
	keyboardObj->addComponent(new InputComponent);

	InputGameObject* cvObj = new InputGameObject(this);
	cvObj->addComponent(new ComputerVisionComponent(BUILT_IN_CAM));

	InputGameObject* camObj = new InputGameObject(this);
	camObj->addComponent(new CameraMovementComponent(1));


	objects.push_back(keyboardObj);
	objects.push_back(cvObj);
	objects.push_back(camObj);
}

void InputSystem::objectInit()
{
	for (InputGameObject* inp : objects)
	{
		inp->init();
	}
}

void InputSystem::update(float dt)
{
	for (InputGameObject* inp : objects)
	{
		inp->update(dt);
	}
}

InputSystem::InputSystem()
{
}


InputSystem::~InputSystem()
{
}
