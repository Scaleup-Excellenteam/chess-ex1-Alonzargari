#pragma once 
#include "Piece.h"

class Rook :public Piece {
public:
	Rook(std::string position);
	bool doMove(std::string destinyPos);
private:
	
};