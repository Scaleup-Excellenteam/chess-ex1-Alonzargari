#include "BestMovesCalculator.h"
#include "BoardManager.h"


void BestMovesCalculator::setPieces(const std::vector<std::unique_ptr<Piece>>& pieces) {
    m_pieces.clear();
    for (const auto& p : pieces) {
        m_pieces.push_back(p.get()); // מצביעים פשוטים, אתה לא מעתיק אלא רק מצביע
    }
}
//=========================================================
/**
 * Calculates the best moves for the current player and stores them in a priority queue.
 *
 * This function iterates over all the pieces of the current player and evaluates the best move
 * for each. It uses a recursive minimax-like evaluation to simulate possible future turns up to
 * a specified max depth. After evaluating, it adds the total score of each move (current move score
 * + expected outcome from deeper levels) into a priority queue of best moves.
 */

void BestMovesCalculator::calculateBestMoves(int maxDepth, const std::string& currentColor, const BoardContext& boardCtx)
{
    auto myPieces = getPiecesOfColor(currentColor);
    clearQueue();
    for (auto piece : myPieces) {
        auto moves = evaluateAllMoves(piece, boardCtx);
        for (auto move : moves) {
            std::string originalPos = piece->getPosition();
            piece->setPosition(move->getDesPosition());

            std::string opponentColor = (currentColor == "White") ? "Black" : "White";
            int calculatedDepthesScore = evaluateBestMoveRecursive(boardCtx, 1, maxDepth, opponentColor);

            int totalMoveScore = move->getScore() - calculatedDepthesScore;
            move->setScore(totalMoveScore);

            if (m_priorityQueue.size() < 5) {
                m_priorityQueue.push(move);
            }
            else {
                m_priorityQueue.poll();
                m_priorityQueue.push(move);
            }

            piece->setPosition(originalPos);
            restoreBoard(); 
        }
    }
}



//=========================================================
/**
 * Recursively evaluates future moves and returns the best cumulative score from this point.
 * This function simulates moves recursively by alternating turns between the player and opponent.
 * Each level of depth simulates one move (either yours or the opponent's). The function adds or
 * subtracts move scores based on whether it's your turn or the opponent's turn:
 * - If it's your turn (`isMyTurn == true`): Add the move score to the recursive result.
 * - If it's the opponent's turn: Subtract your move score from the recursive result.
 * This approach estimates the net impact of a move considering opponent responses up to maxDepth.
 */
int BestMovesCalculator::evaluateBestMoveRecursive(const BoardContext& boardCtx, int depth, int maxDepth, const std::string& currentColor)
{
    //like in instructions when we get to base of the recursive we return the biggest score of the opponent 
    //in the folds we substract this score 
    if (depth >= maxDepth) {
        int curHighestScore = 0;
        auto myPieces = getPiecesOfColor(currentColor);
        for (auto piece : myPieces) {
            auto moves = evaluateAllMoves(piece, boardCtx);
            for (auto move : moves) {
                curHighestScore = std::max(curHighestScore, move->getScore());
                delete move;
            }
        }
        return curHighestScore;
    }

    int bestScore = 0;
    auto myPieces = getPiecesOfColor(currentColor);

    for (auto piece : myPieces) {
        auto moves = evaluateAllMoves(piece, boardCtx);
        for (auto move : moves) {
            std::string originalPos = piece->getPosition();
            piece->setPosition(move->getDesPosition());

            std::string opponentColor = (currentColor == "White") ? "Black" : "White";
            int curDepthScore = evaluateBestMoveRecursive(boardCtx, depth + 1, maxDepth, opponentColor);

            int scoreCalc = move->getScore() - curDepthScore;

            bestScore = std::max(bestScore, scoreCalc);

            piece->setPosition(originalPos);
            restoreBoard();
            delete move;
        }
    }

    return bestScore < 0 ? 0 : bestScore;
}
//=========================================================
std::vector<Piece*> BestMovesCalculator::getPiecesOfColor(const std::string& color)
{
    std::vector<Piece*> piecesOfColor;
    for (const auto& piecePtr : m_pieces) {
        if (piecePtr->getTeamColor() == color) {
            piecesOfColor.emplace_back(piecePtr);
        }
    }
    return piecesOfColor;
}
//=========================================================

void BestMovesCalculator::restoreBoard()
{
    for (const auto& piece : m_pieces) {
        piece->setToErase(false);
    }
}
//=========================================================
void BestMovesCalculator::clearQueue()
{
    while (m_priorityQueue.size() != 0) {
        m_priorityQueue.poll();
    }
}
//=========================================================

std::vector<Move*> BestMovesCalculator::evaluateAllMoves(Piece* piece, const BoardContext& boardCtx)
{
    std::vector<Move*> moves;
    std::string from = piece->getPosition();

    const auto& enemyPieces = (piece->getTeamColor() == "White") ? getPiecesOfColor("Black") : getPiecesOfColor("White");

    for (int row = 0; row < 8; ++row) {
        for (int index = 0; index < 8; ++index) {

            int score = 0;
            std::string desPos = { char(row + 'a'), char(index + '1') };

            if (from == desPos) continue;

            bool isEnemyinPosition = boardCtx.IsEnemyAtPositionFunc(desPos, piece->getTeamColor());

            if (piece->canDoStep(desPos, isEnemyinPosition) && !boardCtx.BlockedByOwnedPieceFunc(desPos)) {
                if (piece->ignorePath() || boardCtx.PathIsClearFunc(from, desPos)) {

                    for (const auto& enemy : enemyPieces) {
                        if (enemy->canDoStep(desPos, true)) {
                            if (enemy->ignorePath() || boardCtx.PathIsClearFunc(enemy->getPosition(), desPos)) {
                                score > 0 ? score -= enemy->getPieceRank() : score;
                            }
                        }
                    }

                    if (isEnemyinPosition) {
                        for (const auto& enemy : enemyPieces) {
                            if (enemy->getPosition() == desPos) {
                                enemy->setToErase(true);
                            }
                        }
                        score += 10;
                    }

                    std::string originalPos = piece->getPosition();
                    piece->setPosition(desPos); 

                    for (const auto& enemy : enemyPieces) {
                        if (enemy->toErase()) continue;
                        std::string enemyPos = enemy->getPosition();
                        if ((piece->canDoStep(enemyPos, true) && piece->ignorePath()) ||
                            (piece->canDoStep(enemyPos, true) && !piece->ignorePath() &&
                                boardCtx.PathIsClearFunc(piece->getPosition(), enemyPos))) {
                            if (enemy->getPieceRank() > piece->getPieceRank()) {
                                score += enemy->getPieceRank();
                            }
                        }
                    }

                    piece->setPosition(originalPos);

                    moves.push_back(new Move(from, desPos, score));
                }
            }
        }
    }

    return moves;
}
//=========================================================

void BestMovesCalculator::printPriorityQueue()
{
     std::cout<<"Recommended moves: \n" << m_priorityQueue;
}
