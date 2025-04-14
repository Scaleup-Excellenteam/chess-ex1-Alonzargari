#pragma once

#include "Piece.h"

class Runner :public Piece {
public:
	Runner(std::string position, std::string teamColor);
	bool canDoStep(std::string destination);
private:
	static bool m_register;
};