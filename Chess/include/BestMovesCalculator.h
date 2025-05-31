#pragma once

#include <string>
#include "PriorityQueue.h"
#include "EmptyQueuExeption.h"
#include "Move.h"
#include <functional>
#include "Piece.h"



class BestMovesCalculator {
public:
  
    struct BoardContext {
        std::function<bool(const std::string&, const std::string&)>PathIsClearFunc;
        std::function<bool(const std::string&)>BlockedByOwnedPieceFunc;
    };
    BestMovesCalculator() = default;
    void setPieces(const std::vector<std::unique_ptr<Piece>>& pieces);
    void calculateBestMoves(int maxDepth,const std::string& currentColorTurn,const BoardContext& boardCtx,bool isMyTurn);
    void printPriorityQueue();
    

private:
    void clearQueue();
    int evaluateBestMoveRecursive(const BoardContext& boardCtx, int depth, int maxDepth, const std::string& currentColor, bool isMyTurn);
    std::vector<std::unique_ptr<Move>> evaluateAllMoves(Piece* piece, const BoardContext& boardCtx);
    std::vector<Piece*> getPiecesOfColor(const std::string& color);
    void restoreBoard();
    int evaluateRiskFromWeakerEnemies(Piece* piece, const std::vector<Piece*>& enemyPieces, const BoardContext& boardCtx);
    int evaluateThreatToStrongerEnemies(Piece* piece, const std::vector<Piece*>& enemyPieces, const BoardContext& boardCtx, const std::string& desPos);
    int evaluateIfCaptureEnemy(Piece* piece, const std::vector<Piece*>& enemyPieces, const std::string& desPos);
    void updatePriorityQueue(std::unique_ptr<Move> move);
    std::vector<Piece*> m_pieces;
    PriorityQueue<std::unique_ptr<Move>, Move::MoveComparator> m_priorityQueue;
};
