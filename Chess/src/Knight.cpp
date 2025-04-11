#include "Knight.h"
#include "designPatterns/factory/PieceFactory.h"

bool Knight::m_register = PieceFactory::registerPiece('N',
	[](std::string pos)->std::unique_ptr<Piece> {
		return std::make_unique<Knight>(pos, "White");
	})
	&&
	PieceFactory::registerPiece('n',
	[](std::string pos)->std::unique_ptr<Piece> {
		return std::make_unique<Knight>(pos, "Black");
	});

	Knight::Knight(std::string position, std::string teamColor):
		Piece(position,teamColor)
	{
	}

	bool Knight::canMoveTo(std::string destinyPos)
	{
		auto curXpos = getPosition()[1] - '0';
		auto desXpos = destinyPos[1] - '0';
		auto curYpos = getPosition()[0] - 'a';
		auto desYpos = destinyPos[0] - 'a';

		int directionX = std::abs(desXpos - curXpos);
		int directionY = std::abs(desYpos - curYpos);

		return (directionX == 2 && directionY == 1) || (directionX == 1 && directionY == 2);
	}

	bool Knight::ignorePath() const
	{
		return true;
	}
