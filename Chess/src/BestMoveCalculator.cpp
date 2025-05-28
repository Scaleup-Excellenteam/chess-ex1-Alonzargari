#include "BestMovesCalculator.h"
#include "BoardManager.h"

BestMovesCalculator::BestMovesCalculator(const std::vector<Piece*>& pieces)
    : m_pieces(pieces)
{
    m_blackPieces = getPiecesOfColor("Black");
    m_whitePieces = getPiecesOfColor("White");
}

void BestMovesCalculator::calculateBestMoves(int depth,const std::string& currentColorTurn, const BoardContext& boardCtx) {
    //�� ����� ��� ����� �� ����� ������� �������� (��� �� ����) ����� ��� ����� ����� ����� ��� ����� ���� 
    // ����� ������ ���� ����� �� ����� �� ���� ��� �-5 ���� ����� ��� ����� ���� �� ����� �� ����� ������ ������
    auto pieces = currentColorTurn == "White" ? m_whitePieces : m_blackPieces;
    for (const auto& piece : pieces) {
       
        auto move = evaluateMove(piece, 0, depth, boardCtx);
        //m_priorityQueue.push(move);
    } 
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

Move BestMovesCalculator::evaluateMove(Piece* piece,int depth, int maxDepth,const BoardContext& boardCtx) {
    int score = 0;
    std::string from = piece->getPosition();

    for (int row = 0; row < 8; ++row) {
        for (int index = 0; index < 8; ++index) {
            std::string desPos = { char(row + 'a'),char(index + '1') };

            bool isEnemyinPosition = boardCtx.IsEnemyAtPositionFunc(desPos, piece->getTeamColor());
            // �� ���� ����� ��� �� ������ ��� 
            if (piece->canDoStep(desPos, isEnemyinPosition)) {
                if (piece->ignorePath() || boardCtx.PathIsClearFunc(from, desPos)) {

                    //�� ��� ����� ����� ��� ��� ����� �� ������ ��� �� �� ����� ������ 
                    const auto& enemyPieces = (piece->getTeamColor() == "White") ? m_blackPieces : m_whitePieces;
                    for (const auto& enemy : enemyPieces) {
                        if (enemy->canDoStep(desPos, true)) {
                            if (enemy->ignorePath() || boardCtx.PathIsClearFunc(enemy->getPosition(), desPos)) {
                                score -= 2;
                            }
                        }
                    }

                    //�� �� ����� ������ ���� ����� ��� ���� ���� ����� ������ ����� 
                    if (isEnemyinPosition) {
                        score += 2;
                    }

                    // ��� �� ���� ����� ��� ��� �� ��� ����� �� ������ �� ����� �� ����� ��� �� ����� ��� ���� ���� �� �� ����� ������ ����� 
                    for (const auto& enemy : enemyPieces) {
                        std::string enemyPos = enemy->getPosition();
                        if ((piece->canDoStep(enemyPos, true) && piece->ignorePath()) ||
                            (piece->canDoStep(enemyPos, true) && !piece->ignorePath() && boardCtx.PathIsClearFunc(desPos, enemyPos))) {

                            //���� �� ��� ���� ��� ����� ������� ������� �� ����� ��� ���� ��� �� �������� �� ����� ���� 
                            // 
                            //if (getPrimitiveValue(enemy.get()) > getPrimitiveValue(piece.get())) {
                            //    moveScore += 2; // ���� ����� �� 2 ������ �� ���� �� ��� ���
                            //}
                        }
                    }
                }
            }
        }

    }
}
