#include "Runner.h"
#include "designPatterns/factory/PieceFactory.h"

bool Runner::m_register=PieceFactory::registerPiece('B',
	[](std::string pos)->std::unique_ptr<Piece> {
	return std::make_unique<Runner>(pos, "White");
	})
	&&
	PieceFactory::registerPiece('b',
	[](std::string pos)->std::unique_ptr<Piece> {
		return std::make_unique<Runner>(pos, "Black");
	});

Runner::Runner(std::string position, std::string teamColor):
	Piece(position,teamColor)
{
}

bool Runner::canDoStep(std::string destination)
{
	int curPosX = getPosition()[1] - '1';
	int curPosY = getPosition()[0] - 'a';
	int desPosX = destination[1] - '1';
	int desPosY = destination[0] - 'a';
	return abs(desPosX - curPosX) == abs(desPosY - curPosY);
}
