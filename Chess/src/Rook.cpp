#include "Rook.h"
#include "designPatterns/factory/PieceFactory.h"

bool Rook::m_register = PieceFactory::registerPiece('R',
	[](std::string pos)->std::unique_ptr<Piece> {
		return std::make_unique<Rook>(pos, "White");
	})
	&&
	PieceFactory::registerPiece('r',
	[](std::string pos)->std::unique_ptr<Piece> {
		return std::make_unique<Rook>(pos, "Black");
	});


Rook::Rook(std::string position,std::string teamColor):
	Piece(position,teamColor)
{
}

bool Rook::canDoStep(std::string destinyPos)
{
	auto curXpos = getPosition()[1];
	auto curYpos = getPosition()[0];
	auto desXpos = destinyPos[1];
	auto desYpos = destinyPos[0];
	
	if (curXpos == desXpos || curYpos == desYpos) {
		return true;
	}
	return false;
}
