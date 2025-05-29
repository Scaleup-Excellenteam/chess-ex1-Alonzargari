#pragma once

#include <string>
#include "PriorityQueue.h"
#include "Move.h"
#include <functional>
#include "Piece.h"



class BestMovesCalculator {
public:
  
    struct BoardContext {
        std::function<bool(const std::string&, const std::string&)>IsEnemyAtPositionFunc;
        std::function<bool(const std::string&, const std::string&)>PathIsClearFunc;
        std::function<bool(const std::string&)>BlockedByOwnedPieceFunc;
    };
    BestMovesCalculator() = default;
    void setPieces(const std::vector<std::unique_ptr<Piece>>& pieces);
    void calculateBestMoves(int maxDepth,const std::string& currentColorTurn,const BoardContext& boardCtx);
    void printPriorityQueue();
    

private:
    void clearQueue();
    int evaluateBestMoveRecursive(const BoardContext& boardCtx, int depth, int maxDepth, const std::string& currentColor);
    std::vector<Move*> evaluateAllMoves(Piece* piece, const BoardContext& boardCtx);
    std::vector<Piece*> getPiecesOfColor(const std::string& color);
    void restoreBoard();
    std::vector<Piece*> m_pieces;
    PriorityQueue<Move*, Move::MoveComparator> m_priorityQueue;
};
