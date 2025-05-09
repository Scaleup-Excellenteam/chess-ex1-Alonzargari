#pragma once

#include "Piece.h"

class Runner :public Piece {
public:
	Runner(const std::string& position, const std::string& teamColor);
	bool canDoStep(const std::string& destination);
private:
	static bool m_register;
};