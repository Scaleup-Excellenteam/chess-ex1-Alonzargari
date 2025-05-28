#pragma once

#include "Piece.h"

class Runner :public Piece {
public:
	Runner(const std::string& position, const std::string& teamColor, int rank);
	bool canDoStep(const std::string& destinyPos, bool isEnemyThere) override;
private:
	static bool m_register;
};