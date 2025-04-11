#include "BoardManager.h"
#include "designPatterns/factory/PieceFactory.h"


BoardManager::BoardManager(const std::string& board):
	m_currentColorTurn{ "White" }
{
	m_blackKing = nullptr;
	m_whiteKing = nullptr;
	initPieceVector(board);
}

int BoardManager::manageMovment(const std::string& input)
{
	int codeResponse = 0;
	std::string pieceCurrentPosInput = { input[0],input[1] };
	std::string  pieceDestinitionInput = { input[2],input[3] };
	for (const auto& piece : m_pieces) {
		if (piece->getPosition() == pieceDestinitionInput &&
			piece->getTeamColor() == m_currentColorTurn|| 
			!pathIsClear(pieceCurrentPosInput, pieceDestinitionInput))
		{
			return codeResponse = 13;
		}
	}
	for (const auto& piece : m_pieces) {
		if (piece->getPosition() == pieceCurrentPosInput)
		{
			if (piece->getTeamColor() == m_currentColorTurn) {
				if (piece->canMoveTo(pieceDestinitionInput)){
					piece->setPosition(pieceDestinitionInput);
					King* king = (m_currentColorTurn == "White") ? m_whiteKing : m_blackKing;
					if (exposeToCheck(king)) {
						piece->setPosition(piece->getLastPosition());
						return codeResponse = 31;
					}
					else {
						King* king = (m_currentColorTurn == "White") ? m_blackKing : m_whiteKing;
						if (king && pathIsClear(piece->getPosition(), king->getPosition())) {
							return codeResponse = 41;
						}
					}
					piece->setLastPosition(pieceDestinitionInput);
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

void BoardManager::removePieceIfEaten()
{
	for (const auto& piece1 : m_pieces) {
		for (const auto& piece2 : m_pieces) {
			if(piece1->getPosition()==piece2->getPosition() && 
				piece1->getTeamColor() != piece2->getTeamColor())
			{
				piece1->getTeamColor() == m_currentColorTurn ? piece2->setToErase() : piece1->setToErase();
			}
		}
	}
	m_pieces.erase(std::remove_if(m_pieces.begin(),m_pieces.end(), 
		[](const auto& piece) { return piece->toErase();}),m_pieces.end());
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
		if (board[index] == 'K') {
			m_whiteKing=new King(curPos, "White");
			m_pieces.emplace_back(std::make_unique<King>(curPos, "White"));
		}
		if (board[index] == 'k') {
			m_blackKing = new King(curPos, "Black");
			m_pieces.emplace_back(std::make_unique<King>(curPos, "Black"));
		}
		if ((index + 1) % 8 == 0) {
			row++;
		}
		index++;
	}
}

bool BoardManager::exposeToCheck(const King* king)
{
	for (const auto& piece : m_pieces) {
		if (king) {
			if (piece->getPosition() == king->getPosition()) {
				continue;
			}
			else if (piece->getTeamColor() != m_currentColorTurn
				&& pathIsClear(piece->getPosition(), king->getPosition()))
			{
				return true;
			}
		}
	}
	return false;
}

bool BoardManager::pathIsClear(const std::string& curPos, const std::string& desPos) {

	char curPosY = curPos[0];
	char curPosX = curPos[1];
	char desPosX = desPos[1];
	char desPosY = desPos[0];

	int direcrtionY = (desPosY > curPosY) ? 1 : (desPosY <curPosY) ? -1 : 0;
	int direcrtionX = (desPosX > curPosX) ? 1 : (desPosX < curPosX) ? -1 : 0;

	int currentX = curPosX + direcrtionX;
	int currentY = curPosY + direcrtionY;

	while (currentX != desPosX || currentY != desPosY) {
		std::string pos = { char(currentY),char(currentX) };
		for (const auto& piece : m_pieces) {
			if (piece->getPosition()==pos) {
				return false;
			}
		}
		currentX += direcrtionX;
		currentY += direcrtionY;
	}
	return true;
}

