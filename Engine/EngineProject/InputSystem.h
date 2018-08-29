#pragma once
#include <vector>
#include <list>
#include "InputGameObject.h"

class InputSystem
{
private:
	void systemInit();
	void objectInit();
public:
	std::list<InputGameObject*> objects;
	
	void init();
	void update(float dt);

	InputSystem();
	~InputSystem();
};

