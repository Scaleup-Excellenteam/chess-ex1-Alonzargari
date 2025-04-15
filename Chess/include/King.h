#pragma once

#include "Piece.h"

class King :public Piece {
public:
	King(const std::string& position, const std::string& teamColor);
	bool canDoStep(const std::string& destinyPos)override;
	bool ignorePath() override;
};