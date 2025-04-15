#include "King.h"


//=========================================================
/*
* King constructor get the same parameters as Piece class
*/

King::King(const std::string& position, const std::string& teamColor) :
	Piece(position, teamColor)
{
}

//=========================================================
/*
* override implementation of the base class this function return
* if the movment is legal or false if not
*/

bool King::canDoStep(const std::string& destinyPos)
{
	auto curXpos = getPosition()[1]-'0';
	auto desXpos = destinyPos[1]-'0';
	auto curYpos = getPosition()[0]-'a';
	auto desYpos = destinyPos[0]-'a';

	if (desXpos==curXpos+1 || desXpos == curXpos - 1
		||desYpos==curYpos-1|| desYpos == curYpos + 1
		||(desXpos == curXpos + 1 && desYpos == curYpos -1)
		||(desXpos == curXpos -1 && desYpos == curYpos - 1)
		||(desXpos == curXpos + 1 && desYpos == curYpos + 1)
		||(desXpos == curXpos - 1 && desYpos == curYpos + 1))
	{
		return true;
	}
	return false;
}

//=========================================================
/*
* king ignore the path he only care about the destination cell
*/

bool King::ignorePath()
{
	return true;
}
