#include "BoardManager.h"
#include "designPatterns/factory/PieceFactory.h"
#include "EmptyQueuExeption.h"
#include "InvalidMoveException.h"

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
	m_bmc = std::make_unique<BestMovesCalculator>();
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
	
	if (blockedByOwnPlayer(pieceDestinitionInput))
	{
		return codeResponse = 13;
	}

	for (const auto& piece : m_pieces) {
		if (piece->getPosition() == pieceCurrentPosInput)
		{
			// Confirm that the selected piece belongs to the player whose turn it is
			if (piece->getTeamColor() == m_currentColorTurn) {

				// here its working only for the pawn if the user want to eat enemy in diagnole
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
				piece1->getTeamColor() == m_currentColorTurn ? piece2->setToErase(true) : piece1->setToErase(true);
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
	while (index < board.length()) {
		std::string curPos = { char(row + 'a'),char(index % 8 + '1') };
		if (auto piece = PieceFactory::createPiece(board[index], curPos)) {
			m_pieces.emplace_back(std::move(piece));
		}
		if (board[index] == 'K') {
			auto king = std::make_unique<King>(curPos, "White", 100);
			m_whiteKing = king.get();
			m_pieces.emplace_back(std::move(king));
		}
		if (board[index] == 'k') {
			auto king = std::make_unique<King>(curPos, "Black", 100);
			m_blackKing = king.get();
			m_pieces.emplace_back(std::move(king));
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
/**
 * Returns a pointer to the piece located at the given position.
 * If no piece exists at that position, returns nullptr.
 */

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
/**
 * Checks if there is an enemy piece at the specified position,
 * relative to the current player's team color.
 * Returns true if an enemy piece is found, otherwise false.
 */

bool BoardManager::isEnemyAtPosition(const std::string& pos, const std::string& currentTeam)
{
	auto piece = getPieceAt(pos);
	return piece != nullptr && piece->getTeamColor() != currentTeam;
}

//========================================================
/**
 * Checks if the given destination position is occupied by a piece
 * from the current player's team.
 * Returns true if blocked by own piece, otherwise false.
 */

bool BoardManager::blockedByOwnPlayer(const std::string& pieceDestinitionInput)
{
	auto piece = getPieceAt(pieceDestinitionInput);
	return piece != nullptr && piece->getTeamColor() == m_currentColorTurn;
}

//========================================================
/**
 * Calculates the best moves for the current player using the specified depth.
 * Sets up context functions used by BestMovesCalculator.
 */

void BoardManager::calculateBestMoves(int depth)
{
	m_bmc->setPieces(m_pieces);
	BestMovesCalculator::BoardContext boardCtx = {
		[this](const std::string& from, const std::string& to) {return this->pathIsClear(from,to);},
		[this](const std::string& pieceDesPos) {return this->blockedByOwnPlayer(pieceDesPos);}

	};
	m_bmc->calculateBestMoves(depth,m_currentColorTurn , boardCtx,true);
}

//========================================================
/**
 * Prints the best moves calculated by BestMovesCalculator.
 * Catches and handles exceptions if the priority queue is empty or if an invalid move is found.
 */

void BoardManager::printBestMovesOfDepth()
{
	try
	{
		m_bmc->printPriorityQueue();
	}
	catch (const InvalidMoveException& e) {
		std::cout << e.what() << std::endl;
	}
	catch (const EmptyQueuExeption& e)
	{
		std::cout<<e.what()<<std::endl;
	}
	
}