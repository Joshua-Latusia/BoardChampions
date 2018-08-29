	#pragma once

#include "Subject.h"
#include "ProjectionComponent.h"



class InputSystem;
class GameLogicSystem;


class Game
{
private:
	/*Timer specific variables*/
	static int lastTime;
protected:
	struct Camera
	{
		float posX = -27.104f;
		float posY = -126.887f;
		float posZ = -67.11f;
		float rotX = 27.0f;
		float rotY = 90.0f;
		float rotZ = 0;
	};


public:
	struct Screen
	{
		int width;
		int height;
	};
	/*Camera struct*/
	static Camera camera;

	/*Screen info*/
	static Screen screen;

	/*Input events*/
	static Subject inputEvents;

	/*Systems*/
	static InputSystem* inputSystem;
	static GameLogicSystem* gameLogicSystem;
	static GameLogicSystem* hudLogicSystem;
	static ProjectionComponent* projection;

	/*Opengl static functions*/
	void static init(int argc, char* argv[]);
	void static display();
	void static update();
	void static reshape(int w, int h);

	/*Constructors & Destructor*/
	Game(int argc, char* argv[]);
	~Game();
};
