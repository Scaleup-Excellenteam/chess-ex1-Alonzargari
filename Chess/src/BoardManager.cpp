#include "BoardManager.h"
#include "designPatterns/factory/PieceFactory.h"

BoardManager::BoardManager(const std::string& board):
	m_currentColorTurn{ "White" }
{
	initPieceVector(board);
}

int BoardManager::manageMovment(const std::string& input)
{
	int codeResponse = 0;
	std::string pieceCurrentPosInput = { input[0],input[1] };
	std::string  pieceDestinitionInput = { input[2],input[3] };
	for (const auto& piece : m_pieces) {
		if (piece->getPosition() == pieceDestinitionInput &&
			piece->getTeamColor() == m_currentColorTurn)
		{
			return codeResponse = 13;
		}
	}
	for (const auto& piece : m_pieces) {
		if (piece->getPosition() == pieceCurrentPosInput)
		{
			if (piece->getTeamColor() == m_currentColorTurn) {
				if (piece->doMove(pieceDestinitionInput)){//בהמשך && KingNotThreat()) {
					piece->setPosition(pieceDestinitionInput);
					m_currentColorTurn = piece->getTeamColor()=="White" ? "Black": "White";
					return codeResponse = 42;
				}
				return codeResponse = 21;
			}
			return codeResponse = 12;
		}
	}
	return codeResponse = 11;
}

void BoardManager::initPieceVector(const std::string& board)
{
	int row = 0;
	int index = 0;
	while(index < board.length()) {
		std::string curPos = { char(row + 'a'),char(index % 8 +'1')};
		if (auto piece = PieceFactory::createPiece(board[index],curPos)) {
			m_pieces.emplace_back(std::move(piece));
		}
		if ((index + 1) % 8 == 0) {
			row++;
		}
		index++;
	}
}

