#include "Subject.h"

void Subject::notifyButtonPressed(unsigned char key, int x, int y)
{
	for (Listener* ln : observerList)
	{
		ln->listenKeyPressed(key, x, y);
	}
}

void Subject::notifyButtonReleased(unsigned char key, int x, int y)
{
	for (Listener* ln : observerList)
	{
		ln->listenKeyReleased(key, x, y);
	}
}

void Subject::notifyMouseMoved(int mouseX, int mouseY)
{
	for (Listener* ln : observerList)
	{
		ln->listenMouseMoved(mouseX, mouseY);
	}
}

void Subject::notifyMapLoaded()
{

	observerList.front()->listenMapLoaded();
}

void Subject::attachListener(Listener* listener)
{
	observerList.push_back(listener);
}

void Subject::detachListener(int index)
{
	observerList.erase(observerList.begin() + index);
}

Subject::Subject()
{
}

Subject::~Subject()
{
}
