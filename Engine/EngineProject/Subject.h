#pragma once
#include "EventSystem.h"
#include "Listener.h"
#include <vector>
#include<iostream>

class Subject
{
private:
	std::vector<Listener*> observerList;
public:
	void notifyButtonPressed(unsigned char key, int x, int y);
	void notifyButtonReleased(unsigned char key, int x, int y);
	void notifyMouseMoved(int mouseX, int mouseY);
	void notifyMapLoaded();
	void attachListener(Listener* listener);
	void detachListener(int index);

	Subject();
	~Subject();
};

