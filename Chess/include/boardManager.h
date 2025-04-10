#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include "Piece.h"

class BoardManager {
public:
	BoardManager(const std::string& board);
	int manageMovment(const std::string& input);
private:
	void initPieceVector(const std::string& board);
	std::string m_currentColorTurn;
	std::vector<std::unique_ptr<Piece>>m_pieces;
};