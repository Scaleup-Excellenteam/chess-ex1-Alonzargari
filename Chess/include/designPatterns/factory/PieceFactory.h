#pragma once
#include "Piece.h"
#include <map>
#include <memory>
#include <functional>

using pieceFunc = std::function<std::unique_ptr<Piece>(std::string pos)>;
using pieceMap = std::map<char, pieceFunc>;

class PieceFactory {
public:
	static std::unique_ptr<Piece> createPiece(const char pieceSymbole, const std::string& position);
	static bool registerPiece(const char, pieceFunc);
private:
	static pieceMap& getPieceMap();
};