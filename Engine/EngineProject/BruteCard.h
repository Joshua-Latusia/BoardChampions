#pragma once
#include "Card.h"

// Default defines for fields of card

#define DEF_ATTACK_POINTS 0
#define DEF_HEALTH_POINTS 0
#define DEF_DEFENCE_POINTS 0
#define DEF_MOVEMENT_RANGE 0
#define DEF_ATTACK_RANGE 0

class BruteCard : public Card
{
private:

public:

	//BruteCard(int xTile, int yTile);
	BruteCard(int uniqueCode, int x, int y);
	BruteCard(int uniqueCode);
	~BruteCard();
};

