#pragma once
#include "Card.h"

// Default defines for fields of card

#define DEF_ATTACK_POINTS 0
#define DEF_HEALTH_POINTS 0
#define DEF_DEFENCE_POINTS 0
#define DEF_MOVEMENT_RANGE 0
#define DEF_ATTACK_RANGE 0

class MeleeCard : public Card
{
private:

public:

	MeleeCard(int uniqueID, int x, int y);
	MeleeCard(int uniqueID);
	~MeleeCard();

};
