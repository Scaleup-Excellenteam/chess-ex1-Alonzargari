#include "Rook.h"

Rook::Rook(std::string position):
	Piece(position)
{
}

bool Rook::doMove(std::string destinyPos)
{
	auto curXpos = getPosition()[1];
	auto curYpos = getPosition()[0];
	auto desXpos = destinyPos[1];
	auto desYpos = destinyPos[0];
	
	if (curXpos == desXpos || curYpos == desYpos) {
		setPosition(destinyPos);
	}
	return false;
}
