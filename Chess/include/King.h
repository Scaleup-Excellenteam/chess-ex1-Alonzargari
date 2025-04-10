#pragma once

#include "Piece.h"

class King :public Piece {
public:
	King(std::string position, std::string teamColor);
	bool doMove(std::string destinyPos);
	//bool isThreating(const Piece&);
private:
	static bool m_register;
};