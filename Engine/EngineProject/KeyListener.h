#pragma once
#include"Listener.h"
class KeyListener : public Listener
{
public:
	void listenKeyPressed(unsigned char key, int x, int y) override;
	KeyListener();
	~KeyListener();
};

