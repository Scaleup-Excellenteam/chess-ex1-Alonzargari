#include "BoardManager.h"
#include "designPatterns/factory/PieceFactory.h"

//=========================================================
/*
* Board Manager contructor
*/

BoardManager::BoardManager(const std::string& board):
	m_currentColorTurn{ "White" }
{
	m_blackKing = nullptr;
	m_whiteKing = nullptr;
	initPieceVector(board);
}

//=========================================================
/*
* This is the main function that manages piece movements
* based on user input.
* It verifies the move legality according to the game's rules and returns a response code
* representing the outcome of the move.
*/

int BoardManager::manageMovment(const std::string& input)
{
	int codeResponse = 0;
	std::string pieceCurrentPosInput = { input[0],input[1] };
	std::string  pieceDestinitionInput = { input[2],input[3] };

	//check if the destination is blocked by any of the player's pieces
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
			// Confirm that the selected piece belongs to the player whose turn it is
			if (piece->getTeamColor() == m_currentColorTurn) {

				bool isEnemy = isEnemyAtPosition(pieceDestinitionInput, piece->getTeamColor());

				if (piece->canDoStep(pieceDestinitionInput,isEnemy)){

					// If the path is not clear and the piece cannot ignore paths block the move
					if (!pathIsClear(piece->getPosition(),pieceDestinitionInput)&&!piece->ignorePath()) {
						return codeResponse = 13;
					}

					piece->setPosition(pieceDestinitionInput);// Temporarily move the piece to the new position 

					// Get the current player's king
					King* king = (m_currentColorTurn == "White") ? m_whiteKing : m_blackKing;

					if (exposeToCheck(king)) {
						piece->setPosition(piece->getLastPosition());
						return codeResponse = 31;
					}

					else {

						// Get the rival king to check if it's under threat
						King* king = (m_currentColorTurn == "White") ? m_blackKing : m_whiteKing;

						if (king && (
							(!piece->ignorePath() && pathIsClear(piece->getPosition(), king->getPosition())) ||
							(piece->ignorePath() && piece->canDoStep(king->getPosition(), isEnemy))))
						{
							piece->setLastPosition(pieceDestinitionInput);
							removePieceIfEaten();
							m_currentColorTurn = piece->getTeamColor() == "White" ? "Black" : "White";
							return codeResponse = 41;
						}
					}

					piece->setLastPosition(pieceDestinitionInput);// Update the last position after a valid move
					removePieceIfEaten();
					m_currentColorTurn = piece->getTeamColor()=="White" ? "Black": "White"; //switch turns
					return codeResponse = 42;
				}
				return codeResponse = 21;
			}
			return codeResponse = 12;
		}
	}
	return codeResponse = 11;
}

//=========================================================
/*
* This function removes a piece from the polymorphic vector
* if it has been captured by an opponent's piece.
*/

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

//=========================================================
/*
* This function initializes the polymorphic vector of pieces.
* It reads all the characters from the board and creates the 
* corresponding pieces at their respective positions using the 
* PieceFactory.
*/

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

//=========================================================
/*
* This function checks whether the king is exposed to a check.
* return true if there is a piece from the opposing team that 
* can reach and threaten the king; false otherwise.
*/

bool BoardManager::exposeToCheck(const King* king)
{
	for (const auto& piece : m_pieces) {
		if (king) {
			if (piece->getPosition() == king->getPosition()) {
				continue;
			}
			else if (piece->getTeamColor() != m_currentColorTurn
				&&piece->canDoStep(king->getPosition(),true) && 
				pathIsClear(piece->getPosition(), king->getPosition()))
			{
				return true;
			}
		}
	}
	return false;
}

//=========================================================
/*
* this function checks if the path is clear and ther is no another
* piece between the current piece position to the destination 
*/

bool BoardManager::pathIsClear(const std::string& curPos, const std::string& desPos) {

	char curPosY = curPos[0];
	char curPosX = curPos[1];
	char desPosX = desPos[1];
	char desPosY = desPos[0];

	int directionY = (desPosY > curPosY) ? 1 : (desPosY < curPosY) ? -1 : 0;
	int directionX = (desPosX > curPosX) ? 1 : (desPosX < curPosX) ? -1 : 0;

	int currentX = curPosX + directionX;
	int currentY = curPosY + directionY;

	while (currentX != desPosX || currentY != desPosY) {
		std::string pos = { char(currentY),char(currentX) };
		for (const auto& piece : m_pieces) {
			if (piece->getPosition()==pos) {
				return false;
			}
		}
		currentX += directionX;
		currentY += directionY;
	}
	return true;
}
//=========================================================
Piece* BoardManager::getPieceAt(const std::string& pos)
{
	for (const auto& piece : m_pieces) {
		if (piece->getPosition() == pos) {
			return piece.get();
		}
	}
	return nullptr;
}
//=========================================================
bool BoardManager::isEnemyAtPosition(const std::string& pos, const std::string& currentTeam)
{
	Piece* piece = getPieceAt(pos);
	return piece != nullptr && piece->getTeamColor() != currentTeam;
}