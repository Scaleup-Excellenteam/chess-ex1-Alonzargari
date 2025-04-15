#include "Rook.h"
#include "designPatterns/factory/PieceFactory.h"

//=========================================================
/*
* the registration of the piece to the factory map
(mapping his representing char to the the function that
return unique ptr of this piece)
*/

bool Rook::m_register = PieceFactory::registerPiece('R',
	[](const std::string& pos)->std::unique_ptr<Piece> {
		return std::make_unique<Rook>(pos, "White");
	})
	&&
	PieceFactory::registerPiece('r',
	[](const std::string& pos)->std::unique_ptr<Piece> {
		return std::make_unique<Rook>(pos, "Black");
	});

//=========================================================
/*
* Rook contructor get the same parameters as Piece class
*/

Rook::Rook(const std::string& position, const std::string& teamColor):
	Piece(position,teamColor)
{
}

//=========================================================
/*
* override implementation of the base class this function return
* if the movment is legal or false if not
*/

bool Rook::canDoStep(const std::string& destinyPos)
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
