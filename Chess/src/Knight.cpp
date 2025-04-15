#include "Knight.h"
#include "designPatterns/factory/PieceFactory.h"


//=========================================================
/*
* the registration of the piece to the factory map 
(mapping his representing char to the the function that 
return unique ptr of this piece)
*/

bool Knight::m_register = PieceFactory::registerPiece('N',
	[](const std::string& pos)->std::unique_ptr<Piece> {
		return std::make_unique<Knight>(pos, "White");
	})
	&&
	PieceFactory::registerPiece('n',
	[](const std::string& pos)->std::unique_ptr<Piece> {
		return std::make_unique<Knight>(pos, "Black");
	});

//=========================================================
/*
* knigt contructor get the same parameters as Piece class
*/
Knight::Knight(const std::string& position, const std::string& teamColor):
	Piece(position,teamColor)
{
}

//=========================================================
/*
* override implementation of the base class this function return
* if the movment is legal or false if not
*/

bool Knight::canDoStep(const std::string& destinyPos)
{
	auto curXpos = getPosition()[1] - '0';
	auto desXpos = destinyPos[1] - '0';
	auto curYpos = getPosition()[0] - 'a';
	auto desYpos = destinyPos[0] - 'a';

	int directionX = std::abs(desXpos - curXpos);
	int directionY = std::abs(desYpos - curYpos);

	return (directionX == 2 && directionY == 1) || (directionX == 1 && directionY == 2);
}

//=========================================================
/*
* Knight ignore the path he can step over other pieces he only
* care the destination cell
*/

bool Knight::ignorePath()
{
	return true;
}
