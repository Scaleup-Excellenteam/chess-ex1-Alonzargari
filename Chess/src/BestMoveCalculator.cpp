#include "BestMovesCalculator.h"
#include "BoardManager.h"



void BestMovesCalculator::setPieces(const std::vector<std::unique_ptr<Piece>>& pieces) {
    m_pieces.clear();
    for (const auto& p : pieces) {
        m_pieces.push_back(p.get()); 
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

void BestMovesCalculator::calculateBestMoves(int maxDepth, const std::string& currentColor, const BoardContext& boardCtx,bool isMyTurn)
{
    auto myPieces = getPiecesOfColor(currentColor);
    clearQueue();
    for (auto piece : myPieces) {
        auto moves = evaluateAllMoves(piece, boardCtx);
        for (auto& move : moves) {
            std::string originalPos = piece->getPosition();
            piece->setPosition(move->getDesPosition());

            std::string opponentColor = (currentColor == "White") ? "Black" : "White";
            int calculatedDepthesScore=0;
            if (maxDepth > 0) {
                calculatedDepthesScore = evaluateBestMoveRecursive(boardCtx, 1, maxDepth, opponentColor, !isMyTurn);

            }
            move->setScore(move->getScore() + calculatedDepthesScore);
            try
            {
                updatePriorityQueue(std::move(move));
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
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
int BestMovesCalculator::evaluateBestMoveRecursive(const BoardContext& boardCtx, int depth, int maxDepth, const std::string& currentColor,bool isMyTurn)
{
    //like in instructions when we get to base of the recursive we return the biggest score of the opponent 
    //in the folds we substract this score 
    if (depth >= maxDepth) {
        int bestAtLeaf = isMyTurn ? INT_MIN : INT_MAX;
        auto myPieces = getPiecesOfColor(currentColor);
        for (auto piece : myPieces) {
            auto moves = evaluateAllMoves(piece, boardCtx);
            for (auto& move : moves) {
                int score = move->getScore();
                bestAtLeaf = isMyTurn
                    ? std::max(bestAtLeaf, score)
                    : std::min(bestAtLeaf, score);
            }
        }
        return bestAtLeaf == INT_MIN || bestAtLeaf == INT_MAX ? 0 : bestAtLeaf;
    }

    int bestScore = isMyTurn ? INT_MIN : INT_MAX;

    auto myPieces = getPiecesOfColor(currentColor);
    std::string opponentColor = (currentColor == "White") ? "Black" : "White";

    for (auto piece : myPieces) {
        auto moves = evaluateAllMoves(piece, boardCtx);
        for (auto& move : moves) {
            std::string originalPos = piece->getPosition();
            piece->setPosition(move->getDesPosition());

            int totalScore = move->getScore();

            int futureScore = evaluateBestMoveRecursive(boardCtx, depth + 1, maxDepth, opponentColor, !isMyTurn);

            int eval = isMyTurn
                ? totalScore + futureScore
                : totalScore - futureScore;

            if (isMyTurn)
                bestScore = std::max(bestScore, eval);
            else
                bestScore = std::min(bestScore, eval);

            piece->setPosition(originalPos);
            restoreBoard();
        }
    }

    return bestScore;
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

std::vector<std::unique_ptr<Move>> BestMovesCalculator::evaluateAllMoves(Piece* piece, const BoardContext& boardCtx)
{
    std::vector<std::unique_ptr<Move>> moves;
    std::string from = piece->getPosition();

    const auto& enemyPieces = (piece->getTeamColor() == "White") ? getPiecesOfColor("Black") : getPiecesOfColor("White");

    for (int row = 0; row < 8; ++row) {
        for (int index = 0; index < 8; ++index) {

            std::string desPos = { char(row + 'a'), char(index + '1') };

            if (from == desPos) continue;

            bool isEnemyInTarget = false;
            for (const auto& enemy : enemyPieces) {
                if (enemy->getPosition() == desPos) {
                    isEnemyInTarget = true;
                }
            }

            if (!piece->canDoStep(desPos, isEnemyInTarget)) continue;
            if (boardCtx.BlockedByOwnedPieceFunc(desPos)) continue;
            if (!piece->ignorePath() && !boardCtx.PathIsClearFunc(from, desPos)) continue;

            int score = 0;

            
            score += evaluateThreatToStrongerEnemies(piece, enemyPieces, boardCtx,desPos);
            score += evaluateIfCaptureEnemy(piece, enemyPieces,desPos);
            score = score > 0 ? score - evaluateRiskFromWeakerEnemies(piece, enemyPieces, boardCtx): score;

            moves.push_back(std::make_unique<Move>(from, desPos, score));
        }
    }
    return moves;
}
//=========================================================

void BestMovesCalculator::printPriorityQueue()
{
    if (m_priorityQueue.size() > 0) {
        std::cout << "Recommended moves: \n" << m_priorityQueue;
    }
    else {
        throw EmptyQueuExeption("Cannot print the queue : priority queue is empty.");
    }
    
}
//=========================================================
int BestMovesCalculator::evaluateRiskFromWeakerEnemies(Piece* piece, const std::vector<Piece*>& enemyPieces, const BoardContext& boardCtx)
{
    int penalty = 0;

    for (const auto& enemy : enemyPieces) {
        if (enemy->getPieceRank() >= piece->getPieceRank()) continue;

        if (enemy->canDoStep(piece->getPosition(), true)) {
            if (enemy->ignorePath() || boardCtx.PathIsClearFunc(enemy->getPosition(), piece->getPosition())) {
                penalty = enemy->getPieceRank();  
            }
        }
    }

    return penalty;
}
//=========================================================
int BestMovesCalculator::evaluateThreatToStrongerEnemies(Piece* piece, const std::vector<Piece*>& enemyPieces,
                                                        const BoardContext& boardCtx,const std::string& desPos)
{
    int reward = 0;

    std::string originalPos = piece->getPosition();
    piece->setPosition(desPos);

    for (const auto& enemy : enemyPieces) {
        if (enemy->getPieceRank() <= piece->getPieceRank()) continue;
        if (enemy->toErase()) continue;

        std::string enemyPos = enemy->getPosition();

        if (piece->canDoStep(enemyPos, true)) {
            if (piece->ignorePath() || boardCtx.PathIsClearFunc(desPos, enemyPos)) {
                reward += enemy->getPieceRank();
            }
        }
    }

    piece->setPosition(originalPos);

    return reward;
}
//=========================================================
int BestMovesCalculator::evaluateIfCaptureEnemy(Piece* piece, const std::vector<Piece*>& enemyPieces, const std::string& desPos)
{
    for (const auto& enemy : enemyPieces) {
        if (enemy->getPosition() == desPos) {
            enemy->setToErase(true);
            return 15;  
        }
    }
    return 0;
}
//========================================================
void BestMovesCalculator::updatePriorityQueue(std::unique_ptr<Move> move) {
    if (m_priorityQueue.size() < 5) {
        m_priorityQueue.push(std::move(move));
    }
    else {
        m_priorityQueue.poll();
        m_priorityQueue.push(std::move(move));
    }
}