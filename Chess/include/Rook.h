#pragma once 
#include "Piece.h"

class Rook :public Piece {
public:
	Rook(std::string position,std::string teamColor);
	bool canDoStep(std::string destinyPos);
private:
	static bool m_register;
};