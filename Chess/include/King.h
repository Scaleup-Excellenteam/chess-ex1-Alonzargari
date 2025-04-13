#pragma once

#include "Piece.h"

class King :public Piece {
public:
	King(std::string position, std::string teamColor);
	bool canDoStep(std::string destinyPos);
	bool ignorePath() override;
private:
	static bool m_register;
};