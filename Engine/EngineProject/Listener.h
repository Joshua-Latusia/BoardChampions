#pragma once
class Listener
{
public:
	virtual void listenKeyPressed(unsigned char key, int x, int y);
	virtual void listenKeyReleased(unsigned char key, int x, int y);
	virtual void listenMouseMoved(int mouseX, int mouseY);
	virtual void listenMapLoaded();
	Listener();
	virtual ~Listener();
};

