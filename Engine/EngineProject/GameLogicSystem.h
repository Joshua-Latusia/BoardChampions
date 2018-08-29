#pragma once

#include<list>
#include "LogicGameObject.h"
#include "Listener.h"

class GameLogicSystem : public Listener
{
private:
	void systemInit();
	void objectInit();

	LogicGameObject* map = nullptr;
	long gameTime = 0;
	float M_PI = 3.14159265358979323846f;

public:
	std::list<LogicGameObject*> objects;

	int activePlayer = 0;

	typedef enum
	{
		GAMEINIT,
		GAMELOAD,
		PLAYER1SETUP,
		PLAYER2SETUP,
		PLAYER1STARTTURN,
		PLAYER1MOVEUNIT,
		PLAYER1UNITCOMBAT,
		PLAYER1ENDTURN,
		PLAYER2STARTTURN,
		PLAYER2MOVEUNIT,
		PLAYER2UNITCOMBAT,
		PLAYER2ENDTURN
	} GameState;
	static GameState gameState;


	void init();
	void update(float dt);
	void draw();
	static void setStatusBars();
	void listenMapLoaded() override;
	GameLogicSystem();
	~GameLogicSystem();

	
};

