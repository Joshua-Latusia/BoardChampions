#pragma once
class UISystem
{
public:
	void init();
	void update(float dt);
	void static drawString(char *string, int height);
	UISystem();
	~UISystem();
};

