#pragma once

#include "Piece.h"

class Knight:public Piece {
public:
	Knight(std::string position, std::string teamColor);
	bool canDoStep(std::string destinyPos);
	bool ignorePath() override;
private:
	static bool m_register;
};