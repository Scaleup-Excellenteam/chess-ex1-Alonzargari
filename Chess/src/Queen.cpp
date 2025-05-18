#include "Queen.h"
#include "designPatterns/factory/PieceFactory.h"


//=========================================================
/*
* the registration of the piece to the factory map
(mapping his representing char to the the function that
return unique ptr of this piece)
*/

bool Queen::m_register = PieceFactory::registerPiece('Q', 
	[](const std::string& pos)->std::unique_ptr<Piece>
	{
		return std::make_unique<Queen>(pos, "White");
	})
	&&
	PieceFactory::registerPiece('q',
	[](const std::string& pos)->std::unique_ptr<Piece>
	{
		return std::make_unique<Queen>(pos, "Black");
	});

//=========================================================
/*
* Queen contructor get the same parameters as Piece class
*/

Queen::Queen(const std::string& position, const std::string& teamColor) :
	Piece(position, teamColor)
{
}

//=========================================================
/*
* override implementation of the base class this function return
* if the movment is legal or false if not
*/

bool Queen::canDoStep(const std::string& destinyPos, bool isEnemyThere)
{
	int curPosX = getPosition()[1]-'1';
	int curPosY = getPosition()[0]-'a';
	int desPosX = destinyPos[1]-'1';
	int desPosY = destinyPos[0]-'a';

	return (abs(desPosX - curPosX) == abs(desPosY - curPosY))||(desPosX-curPosX)==0||(desPosY-curPosY)==0;
	
}
