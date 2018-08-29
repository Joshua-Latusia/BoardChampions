#include "MagicCard.h"

MagicCard::MagicCard(int uniqueID, int x, int y) : Card(uniqueID, x, y)
{
	attackValue = 5;
	defenceValue = 2;
	healthValue = 15;

	modelID = MAGICCARD;
}

MagicCard::MagicCard(int uniqueID) : Card(uniqueID)
{
	attackValue = 5;
	defenceValue = 2;
	healthValue = 15;

	modelID = MAGICCARD;
}



MagicCard::~MagicCard()
{
}
