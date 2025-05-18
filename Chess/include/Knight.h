#pragma once

#include "Piece.h"

class Knight:public Piece {
public:
	Knight(const std::string& position, const std::string& teamColor);
	bool canDoStep(const std::string& destinyPos, bool isEnemyThere)override;
	bool ignorePath() override;
private:
	static bool m_register;
};