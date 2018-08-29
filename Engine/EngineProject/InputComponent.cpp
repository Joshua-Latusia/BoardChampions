#include "InputComponent.h"
#include <GL/freeglut.h>
#include <functional>
#include "Game.h"


void InputComponent::keyboardDown(unsigned char key, int x, int y)
{
	Game::inputEvents.notifyButtonPressed(key, x, y);
}

void InputComponent::keyboardUp(unsigned char key, int x, int y)
{
	Game::inputEvents.notifyButtonReleased(key, x, y);
}

void InputComponent::mouseMotion(int mouseX, int mouseY)
{
	Game::inputEvents.notifyMouseMoved(mouseX, mouseY);
}

void InputComponent::mouseClick(int button, int state, int x, int y)
{
	// state 0 = ingedrukt
	if(mouseClicked != 0)
		mouseClicked = state;
}

void InputComponent::init()
{
	glutKeyboardFunc(InputComponent::keyboardDown);
	glutKeyboardUpFunc(InputComponent::keyboardUp);
	glutPassiveMotionFunc(InputComponent::mouseMotion);
	glutMouseFunc(InputComponent::mouseClick);
}

InputComponent::InputComponent()
{
}


InputComponent::~InputComponent()
{
}
