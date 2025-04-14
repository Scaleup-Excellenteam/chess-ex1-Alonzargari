#pragma once

#include "Piece.h"

class Queen :public Piece {
public:
	Queen(std::string position, std::string teamColor);
	bool canDoStep(std::string destination);
private:
	static bool m_register;
};