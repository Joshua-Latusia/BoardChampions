#pragma once
#include "Component.h"

extern int  mouseClicked;

class InputComponent : public Component
{
private:
	void static keyboardDown(unsigned char key, int x, int y);
	void static keyboardUp(unsigned char key, int x, int y);
	void static mouseMotion(int mouseX, int mouseY);
	static void mouseClick(int button, int state, int x, int y);

public:


	void init() override;
	InputComponent();
	~InputComponent();
};

