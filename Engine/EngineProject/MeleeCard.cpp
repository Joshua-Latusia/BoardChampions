#include "MeleeCard.h"

MeleeCard::MeleeCard(int uniqueID, int x, int y) : Card(uniqueID, x,y)
{

	attackValue = 4;
	defenceValue = 2;
	healthValue = 20;

	modelID = MELEECARD;
}

MeleeCard::MeleeCard(int uniqueID) : Card(uniqueID)
{

	attackValue = 4;
	defenceValue = 2;
	healthValue = 20;

	modelID = MELEECARD;
}

MeleeCard::~MeleeCard()
{
}
