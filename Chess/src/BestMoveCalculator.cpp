#include "BestMovesCalculator.h"
#include "BoardManager.h"

BestMovesCalculator::BestMovesCalculator(const std::vector<Piece*>& pieces)
    : m_pieces(pieces)
{
}

void BestMovesCalculator::calculateBestMoves(int depth,const std::string& currentColor,const BoardContext& boardCtx)
{
    auto myPieces = getPiecesOfColor(currentColor);

    for (auto piece : myPieces) {
        Move* move = evaluateMove(piece, boardCtx);
        if (!move) continue;

        piece->setPosition(move->getDesPosition());

        std::string opponentColor = (currentColor == "White") ? "Black" : "White";

        int opponentScore = evaluateBestMoveRecursive(boardCtx, depth - 1, opponentColor);

        int netScore = move->getScore() - opponentScore;
        move->addScore(netScore); 

        if (m_priorityQueue.size() < 5) {
            m_priorityQueue.push(move);
        }
        else {
            m_priorityQueue.poll();
        }

    }

}

int BestMovesCalculator::evaluateBestMoveRecursive(
    const BoardContext& boardCtx,
    int depth,
    const std::string& currentColor)
{
    if (depth == 0) {
        int totalScore = 0;
        auto myPieces = getPiecesOfColor(currentColor);
        for (auto piece : myPieces) {
            Move* move = evaluateMove(piece, boardCtx);
            if (move) {
                totalScore += move->getScore();
                delete move;
            }
        }
        return totalScore;
    }

    int bestScore = 0;
    auto myPieces = getPiecesOfColor(currentColor);
    for (auto piece : myPieces) {

        Move* move = evaluateMove(piece, boardCtx);

        if (piece->toErase()||!move) continue;
        
        piece->setPosition(move->getDesPosition());
        std::string opponentColor = (currentColor == "White") ? "Black" : "White";
        int opponentScore = evaluateBestMoveRecursive(boardCtx, depth - 1, opponentColor);

        int netoScore = move->getScore() - opponentScore;
        bestScore = std::max(bestScore, netoScore);
        delete move;
    }

    return bestScore;
}

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

void BestMovesCalculator::restoreBoard()
{
    for (const auto& piece : m_pieces) {
        piece->setPosition(piece->getLastPosition());
        piece->setToErase(false);
    }
}

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
                                score -= enemy->getPieceRank();
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
