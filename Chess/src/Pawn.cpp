
#include "Pawn.h"
#include "designPatterns/factory/PieceFactory.h"
//=========================================================
/*
* Register the Pawn piece type with the PieceFactory for both white ('P') and black ('p') pawns.
* Associates the character identifier with a lambda function that creates a new Pawn instance.
*/

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
/**
 * Constructs a Pawn object.
 *
 * @param position The initial position of the pawn on the board (e.g., "e2").
 * @param teamColor The color of the team the pawn belongs to ("White" or "Black").
 * @param rank The piece rank (used in general Piece constructor).
 */

Pawn::Pawn(const std::string& position, const std::string& teamColor, int rank) :
Piece(position, teamColor,rank), m_hasMoved(false) 
{
}

//=========================================================

/**
 * Determines whether the pawn can move to a specified destination.
 *
 * @param destinyPos The target position the pawn attempts to move to.
 * @param isEnemyThere True if there is an enemy piece at the destination, false otherwise.
 * @return True if the move is legal for a pawn, false otherwise.
 *
 * Logic:
 * - Pawns can move forward by one square if the square is empty.
 * - If on their starting row, they may move forward two squares (if both are empty).
 * - Pawns can capture diagonally one square forward if an enemy piece is present.
 */

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

