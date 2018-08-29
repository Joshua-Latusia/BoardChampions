#include "BruteCard.h"


BruteCard::BruteCard(int uniqueID, int x, int y) : Card(uniqueID, x, y)
{
	attackValue = 4;
	defenceValue = 2;
	healthValue = 20;
	
		modelID = BRUTECARD;
}

BruteCard::BruteCard(int uniqueCode) : Card(uniqueCode)
{
	attackValue = 4;
	defenceValue = 2;
	healthValue = 20;

	modelID = BRUTECARD;

}

BruteCard::~BruteCard()
{
}
