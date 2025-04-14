#include "Queen.h"
#include "designPatterns/factory/PieceFactory.h"

bool Queen::m_register = PieceFactory::registerPiece('Q', 
	[](std::string position)->std::unique_ptr<Piece> 
	{
		return std::make_unique<Queen>(position, "White");
	})
	&&
	PieceFactory::registerPiece('q',
	[](std::string position)->std::unique_ptr<Piece>
	{
		return std::make_unique<Queen>(position, "Black");
	});


Queen::Queen(std::string position, std::string teamColor) :
	Piece(position, teamColor)
{
}

bool Queen::canDoStep(std::string destination)
{
	int curPosX = getPosition()[1]-'1';
	int curPosY = getPosition()[0]-'a';
	int desPosX = destination[1]-'1';
	int desPosY = destination[0]-'a';

	return (abs(desPosX - curPosX) == abs(desPosY - curPosY))||(desPosX-curPosX)==0||(desPosY-curPosY)==0;
	
}
