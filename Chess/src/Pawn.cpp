
#include "Pawn.h"
#include "designPatterns/factory/PieceFactory.h"
bool Pawn::m_register = PieceFactory::registerPiece('P',
	[](const std::string& pos)->std::unique_ptr<Piece> {
		return std::make_unique<Pawn>(pos, "White",1);
	})
	&&
	PieceFactory::registerPiece('p',
	[](const std::string& pos)->std::unique_ptr<Piece> {
		return std::make_unique<Pawn>(pos, "Black",1);
	});
//=========================================================

Pawn::Pawn(const std::string& position, const std::string& teamColor, int rank) :
Piece(position, teamColor,rank), m_hasMoved(false) 
{
}
//=========================================================

bool Pawn::canDoStep(const std::string& destinyPos, bool isEnemyThere)
{
	const std::string& current = getPosition();
	int dx = destinyPos[1] - current[1];
	int dy = destinyPos[0] - current[0];
	auto check = current[0] - 'a';
	int direction = (getTeamColor() == "White") ? 1 : -1;

	bool inStartRow = (getTeamColor() == "White" && current[0]-'a' == 1) ||
		(getTeamColor() == "Black" && current[0]-'a' == 6);

	if (!isEnemyThere && dx == 0) {
		if (dy == direction) return true;
		if (inStartRow && dy == 2 * direction)return true;
	}

	if (isEnemyThere && std::abs(dx) == 1 && dy == direction) {
		return true;
	}

	return false;
}

