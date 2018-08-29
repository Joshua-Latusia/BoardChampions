#include "KeyListener.h"
#include <iostream>

void KeyListener::listenKeyPressed(unsigned char key, int x, int y)
{
	std::cout << "Listener has listened" << std::endl;
}

KeyListener::KeyListener()
{
}


KeyListener::~KeyListener()
{
}
