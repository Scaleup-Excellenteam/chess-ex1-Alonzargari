#pragma once 
#include "Piece.h"

class Rook :public Piece {
public:
	Rook(const std::string& position, const std::string& teamColor);
	bool canDoStep(const std::string& destinyPos);
private:
	static bool m_register;
};