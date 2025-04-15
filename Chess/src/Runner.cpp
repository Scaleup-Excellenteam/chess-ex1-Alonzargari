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
	return std::make_unique<Runner>(pos, "White");
	})
	&&
	PieceFactory::registerPiece('b',
	[](const std::string& pos)->std::unique_ptr<Piece> {
		return std::make_unique<Runner>(pos, "Black");
	});

//=========================================================
/*
* Runner contructor get the same parameters as Piece class
*/

Runner::Runner(const std::string& position, const std::string& teamColor):
Piece(position,teamColor)
{
}

//=========================================================
/*
* override implementation of the base class this function return
* if the movment is legal or false if not
*/

bool Runner::canDoStep(const std::string& destination)
{
	int curPosX = getPosition()[1] - '1';
	int curPosY = getPosition()[0] - 'a';
	int desPosX = destination[1] - '1';
	int desPosY = destination[0] - 'a';
	return abs(desPosX - curPosX) == abs(desPosY - curPosY);
}
