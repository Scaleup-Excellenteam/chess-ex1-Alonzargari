#include "King.h"
//#include "designPatterns/factory/PieceFactory.h"
//bool King::m_register = PieceFactory::registerPiece('K',
//	[](std::string pos)->std::unique_ptr<Piece> {
//		return std::make_unique<King>(pos, "White");
//	})
//	&&
//	PieceFactory::registerPiece('k',
//	[](std::string pos)->std::unique_ptr<Piece> {
//		return std::make_unique<King>(pos, "Black");
//	});

King::King(std::string position, std::string teamColor) :
	Piece(position, teamColor)
{
}

bool King::doMove(std::string destinyPos)
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

//bool King::isThreating(const Piece& King)
//{
//	return false;
//}
