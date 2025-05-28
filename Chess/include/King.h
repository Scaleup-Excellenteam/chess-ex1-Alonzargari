#pragma once

#include "Piece.h"

class King :public Piece {
public:
	King(const std::string& position, const std::string& teamColor, int rank);
	bool canDoStep(const std::string& destinyPos, bool isEnemyThere)override;
	bool ignorePath() override;
};