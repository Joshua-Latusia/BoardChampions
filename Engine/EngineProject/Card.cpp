#include "Card.h"
#include <ostream>
#include <iostream>


Card::Card(int uniqueID, int x, int y) : playerID(uniqueID), x(x), y(y)
{
	if (uniqueID < 6)
		team = teamRed;
	else
		team = teamBlack;
}

Card::Card(int uniqueID) : playerID(uniqueID)
{
	if (uniqueID < 6)
		team = teamRed;
	else
		team = teamBlack;
}


Card::~Card()
{
}
