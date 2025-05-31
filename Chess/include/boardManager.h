#pragma once
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include "Piece.h"
#include "King.h"
#include "BestMovesCalculator.h"
#include "PriorityQueue.h"

class BoardManager {
public:
	BoardManager(const std::string& board);
	int manageMovment(const std::string& input);
	void removePieceIfEaten();
	bool pathIsClear(const std::string&, const std::string&);
	bool isEnemyAtPosition(const std::string& pos, const std::string& currentTeam);
	void printBestMovesOfDepth();
	bool blockedByOwnPlayer(const std::string& pieceDestinitionInput);
	void calculateBestMoves(int depth);



private:
	void initPieceVector(const std::string& board);
	bool exposeToCheck(const King* king);
	Piece* getPieceAt(const std::string& pos);
	std::string m_currentColorTurn;
	std::vector<std::unique_ptr<Piece>>m_pieces;
	King* m_whiteKing;
	King* m_blackKing;
	std::unique_ptr<BestMovesCalculator> m_bmc;
};

