#pragma once
#include <iostream>
#include <vector>
#include "Piece.h"

class BoardManager {
public:
	BoardManager(const std::string& board);//, const std::string& Input, const std::string& pieceDestinitionInput);
	void manageMovment();
private:
	void initPieceVector();
	std::string m_board;
	std::string m_pieceCurrentPosInput;
	std::string m_pieceDestinitionInput;
	std::vector<std::unique_ptr<Piece>>m_pieces;
};