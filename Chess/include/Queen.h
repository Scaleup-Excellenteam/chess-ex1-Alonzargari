#pragma once

#include "Piece.h"

class Queen :public Piece {
public:
	Queen(const std::string& position, const std::string& teamColor);
	bool canDoStep(const std::string& destination);
private:
	static bool m_register;
};