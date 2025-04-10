#include "BoardManager.h"
#include "designPatterns/factory/PieceFactory.h"

BoardManager::BoardManager(const std::string& board):
	m_board{ board }//, const std::string& piecePostionInput,
						   //const std::string& pieceDestinitionInput):
	//m_piecePositionInput{piecePostionInput},m_pieceDestinitionInput{pieceDestinitionInput}
{
	//initBoard(board);
	initPieceVector();
}

void BoardManager::manageMovment()
{
	for (const auto& piece : m_pieces) {
		std::cout << piece->getPosition() << std::endl;
	}
}

void BoardManager::initPieceVector()
{
	int row = 0;
	int index = 0;
	while(index < m_board.length()) {
		std::string curPos = { char(row + 'a'),char(index % 8 +'1')};
		if (auto piece = PieceFactory::createPiece(m_board[index],curPos)) {
			m_pieces.emplace_back(std::move(piece));
		}
		if ((index + 1) % 8 == 0) {
			row++;
		}
		index++;
	}
}

