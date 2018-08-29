#include "KeyboardMovementComponent.h"
#include <iostream>


void KeyboardMovementComponent::listenKeyPressed(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w': 
		/*gameObject->velocity = Vec3fl(0, 5.0f, 0);*/
		break;
		case 'a': 
		//gameObject->velocity = Vec3fl(-5.0f, 0, 0); 
		break;
		case 's': 
		//gameObject->velocity = Vec3fl(0, -5.0f, 0);
		break;
		case 'd': 
		//gameObject->velocity = Vec3fl(5.0f, 0, 0);
		break;
		case 'q':
			//gameObject->velocity = Vec3fl(5.0f, 0, 0);
		break;
		case 'e':
			//gameObject->velocity = Vec3fl(5.0f, 0, 0);
		break;
		case 27:
			exit(0);
	    break;
	}
}

void KeyboardMovementComponent::init()
{
	//Init here
}

KeyboardMovementComponent::KeyboardMovementComponent()
{
}


KeyboardMovementComponent::~KeyboardMovementComponent()
{
}
