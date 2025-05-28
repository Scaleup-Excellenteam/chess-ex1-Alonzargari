#include "BestMovesCalculator.h"
#include "BoardManager.h"

BestMovesCalculator::BestMovesCalculator(const std::vector<Piece*>& pieces)
    : m_pieces(pieces)
{
    m_blackPieces = getPiecesOfColor("Black");
    m_whitePieces = getPiecesOfColor("White");
}

void BestMovesCalculator::calculateBestMoves(int depth,const std::string& currentColorTurn, const BoardContext& boardCtx) {
    //פה המטרה היא שעבור כל חתיכה בווקטור הרלוונטי (לבן או שחור) תבדוק מהו המהלך התקין עבורו ואז תוסיף לתור 
    // כמובן שבהמשך צריך לבדוק אם הגודל של התור קטן מ-5 פשוט תדחוף ואם גבוהה יותר אז תוציא את האיבר האחרון ותדחוף
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
            // אם אפשר לעשות צעד אל המיקום הזה 
            if (piece->canDoStep(desPos, isEnemyinPosition)) {
                if (piece->ignorePath() || boardCtx.PathIsClearFunc(from, desPos)) {

                    //אז לכל אוייב תבדוק האם הוא מאיים על המיקום הזה אם כן תוריד נקודות 
                    const auto& enemyPieces = (piece->getTeamColor() == "White") ? m_blackPieces : m_whitePieces;
                    for (const auto& enemy : enemyPieces) {
                        if (enemy->canDoStep(desPos, true)) {
                            if (enemy->ignorePath() || boardCtx.PathIsClearFunc(enemy->getPosition(), desPos)) {
                                score -= 2;
                            }
                        }
                    }

                    //אם יש אוייב במיקום היעד כלומר אתה תאכל אותו תוסיף נקודות למהלך 
                    if (isEnemyinPosition) {
                        score += 2;
                    }

                    // עוד לא מומש לגמרי אבל כאן אם אתה מאיים על האוייב אז תבדוק מה הראנק שלו אם הראנק שלו גבוה משלך אז זה הוספת נקודות טובות 
                    for (const auto& enemy : enemyPieces) {
                        std::string enemyPos = enemy->getPosition();
                        if ((piece->canDoStep(enemyPos, true) && piece->ignorePath()) ||
                            (piece->canDoStep(enemyPos, true) && !piece->ignorePath() && boardCtx.PathIsClearFunc(desPos, enemyPos))) {

                            //אלון יא גבר תממש לכל חתיכה פונקציה שמחזירה את הראנק שלה וככה תדע אם אתהמאיים על חתיכה שווה 
                            // 
                            //if (getPrimitiveValue(enemy.get()) > getPrimitiveValue(piece.get())) {
                            //    moveScore += 2; // נניח בונוס של 2 נקודות על איום על כלי חזק
                            //}
                        }
                    }
                }
            }
        }

    }
}
