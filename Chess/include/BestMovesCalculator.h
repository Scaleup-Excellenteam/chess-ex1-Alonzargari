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
    };
    BestMovesCalculator(const std::vector<Piece*>& pieces);
    void calculateBestMoves(int maxDepth,const std::string& currentColorTurn,const BoardContext& boardCtx);
    int evaluateBestMoveRecursive(const BoardContext& boardCtx, int depth, int maxDepth, const std::string& currentColor, bool isMyTurn);
    Move* evaluateMove(Piece* piece,const BoardContext& boardCtx);
    std::vector<Piece*> getPiecesOfColor(const std::string& color);
    void restoreBoard();
private:
    std::vector<Piece*> m_pieces;
    PriorityQueue<Move, MoveComparator> m_priorityQueue;
};
