#pragma once

#include "Piece.h"

class Knight:public Piece {
public:
	Knight(std::string position, std::string teamColor);
	bool canMoveTo(std::string destinyPos);
	bool ignorePath() const override;
private:
	static bool m_register;
};