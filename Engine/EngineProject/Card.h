#pragma once

#define MELEECARD 0
#define BRUTECARD 1
#define MAGICCARD 2

#define teamRed 0
#define teamBlack 1

class Card
{
protected:



	//int movementRange;
	//int attackRange;



public:
	int attackValue;
	int defenceValue;
	int healthValue;

	int team;

	int playerID;
	int modelID;

	int x;
	int y;
	Card(int uniqueID, int x, int y);
	Card(int uniqueID);
	virtual ~Card();
};

