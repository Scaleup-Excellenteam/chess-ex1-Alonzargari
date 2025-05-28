#include "Runner.h"
#include "designPatterns/factory/PieceFactory.h"

//=========================================================
/*
* the registration of the piece to the factory map
(mapping his representing char to the the function that
return unique ptr of this piece)
*/

bool Runner::m_register=PieceFactory::registerPiece('B',
	[](const std::string& pos)->std::unique_ptr<Piece> {
	return std::make_unique<Runner>(pos, "White",3);
	})
	&&
	PieceFactory::registerPiece('b',
	[](const std::string& pos)->std::unique_ptr<Piece> {
		return std::make_unique<Runner>(pos, "Black",3);
	});

//=========================================================
/*
* Runner contructor get the same parameters as Piece class
*/

Runner::Runner(const std::string& position, const std::string& teamColor,int rank):
Piece(position,teamColor, rank)
{
}

//=========================================================
/*
* override implementation of the base class this function return
* if the movment is legal or false if not
*/

bool Runner::canDoStep(const std::string& destinyPos, bool isEnemyThere)
{
	int curPosX = getPosition()[1] - '1';
	int curPosY = getPosition()[0] - 'a';
	int desPosX = destinyPos[1] - '1';
	int desPosY = destinyPos[0] - 'a';
	return abs(desPosX - curPosX) == abs(desPosY - curPosY);
}
