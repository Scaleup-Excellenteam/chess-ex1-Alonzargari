#include "BestMovesCalculator.h"
#include "BoardManager.h"

BestMovesCalculator::BestMovesCalculator(const std::vector<Piece*>& pieces)
    : m_pieces(pieces)
{
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

void BestMovesCalculator::calculateBestMoves(int maxDepth,const std::string& currentColor,const BoardContext& boardCtx)
{
    auto myPieces = getPiecesOfColor(currentColor);

    for (auto piece : myPieces) {
        Move* move = evaluateMove(piece, boardCtx);
        if (!move) continue;

        piece->setPosition(move->getDesPosition());

        std::string opponentColor = (currentColor == "White") ? "Black" : "White";

        int calculatedDepthesScore = evaluateBestMoveRecursive(boardCtx,1,maxDepth, opponentColor,false);

        int totalMoveScore = move->getScore() + calculatedDepthesScore;
        move->setScore(totalMoveScore);

        if (m_priorityQueue.size() < 5) {
            m_priorityQueue.push(move);
        }
        else {
            m_priorityQueue.poll();
        }
        restoreBoard();
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
int BestMovesCalculator::evaluateBestMoveRecursive(const BoardContext& boardCtx,int depth,int maxDepth,const std::string& currentColor, bool isMyTurn)
{
    if (depth == maxDepth) {
        int curHighestScore = 0;
        auto myPieces = getPiecesOfColor(currentColor);
        for (auto piece : myPieces) {
            Move* move = evaluateMove(piece, boardCtx);
            if (move) {
                curHighestScore = move->getScore();
                delete move;
            }
        }
        return curHighestScore;
    }

    int bestScore = 0;
    auto myPieces = getPiecesOfColor(currentColor);
    for (auto piece : myPieces) {

        Move* move = evaluateMove(piece, boardCtx);

        if (piece->toErase()||!move) continue;
        
        std::string originalPos = piece->getPosition();
        piece->setPosition(move->getDesPosition());
        std::string opponentColor = (currentColor == "White") ? "Black" : "White";
        isMyTurn = !isMyTurn;
        int curDepthScore = evaluateBestMoveRecursive(boardCtx, depth + 1,maxDepth, opponentColor,isMyTurn);

        int netScore = isMyTurn? move->getScore() + curDepthScore : curDepthScore - move->getScore();

        bestScore = std::max(bestScore, curDepthScore);
        piece->setPosition(originalPos);
        delete move;
    }

    return bestScore;
}
//=========================================================
std::vector<Piece*> BestMovesCalculator::getPiecesOfColor(const std::string& color)
{
    std::vector<Piece*> piecesOfColor;
    for (const auto& piecePtr : m_pieces) {
        if (piecePtr->getTeamColor() == color) {
            piecesOfColor.push_back(piecePtr); 
        }
    }
    return piecesOfColor;
}
//=========================================================

void BestMovesCalculator::restoreBoard()
{
    for (const auto& piece : m_pieces) {
        piece->setPosition(piece->getLastPosition());
        piece->setToErase(false);
    }
}
//=========================================================

Move* BestMovesCalculator::evaluateMove(Piece* piece,const BoardContext& boardCtx) {
    int bestScore = 0;
    std::string from = piece->getPosition();
    std::string bestDesPos = "";

    for (int row = 0; row < 8; ++row) {
        for (int index = 0; index < 8; ++index) {

            int score = 0;
            std::string desPos = { char(row + 'a'),char(index + '1') };

            if (from == desPos) continue;

            bool isEnemyinPosition = boardCtx.IsEnemyAtPositionFunc(desPos, piece->getTeamColor());
            // אם אפשר לעשות צעד אל המיקום הזה 
            if (piece->canDoStep(desPos, isEnemyinPosition)) {
                if (piece->ignorePath() || boardCtx.PathIsClearFunc(from, desPos)) {

                    //אז לכל אוייב תבדוק האם הוא מאיים על המיקום הזה אם כן תוריד נקודות 
                    const auto& enemyPieces = (piece->getTeamColor() == "White") ? getPiecesOfColor("Black") : getPiecesOfColor("White");
                    for (const auto& enemy : enemyPieces) {
                        if (enemy->canDoStep(desPos, true)) {
                            if (enemy->ignorePath() || boardCtx.PathIsClearFunc(enemy->getPosition(), desPos)) {
                                score>0 ? score -= enemy->getPieceRank():score;
                            }
                        }
                    }

                    //אם יש אוייב במיקום היעד כלומר אתה תאכל אותו תוסיף נקודות למהלך 
                    if (isEnemyinPosition) {
                        for (const auto& enemy : enemyPieces) {
                            if (enemy->getPosition()==desPos) {
                                enemy->setToErase(true);
                            }
                        }
                        score += 10;
                    }

                    //  אם אתה מאיים על האוייב אז תבדוק מה הראנק שלו אם הראנק שלו גבוה משלך אז זה הוספת נקודות 
                    for (const auto& enemy : enemyPieces) {
                        std::string enemyPos = enemy->getPosition();
                        if ((piece->canDoStep(enemyPos, true) && piece->ignorePath()) ||
                            (piece->canDoStep(enemyPos, true) && !piece->ignorePath() && boardCtx.PathIsClearFunc(desPos, enemyPos))) {
                            if (enemy->getPieceRank() > piece->getPieceRank()) {
                                score += enemy->getPieceRank(); 
                            }
                        }
                    }
                }
            }
            if (bestScore <= score) {
                bestScore = score;
                bestDesPos = desPos;
            }
        }
    }
    return new Move(from, bestDesPos, bestScore);
}
