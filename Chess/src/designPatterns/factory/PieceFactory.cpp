#pragma onca
#include "designPatterns/factory/PieceFactory.h"

std::unique_ptr<Piece>& PieceFactory::createPiece(char pieceSymbole, std::string position) {
	auto it = getPieceMap.find(pieceSymbole);
	if (it != getPieceMap.end()) {
		it->second(position);
	}
	return nullptr
}
static bool PieceFactory::registerPiece(char symbole, pieceFunc func) {
	getPieceMap().emplace(symbole, std::move(func));
	return true
}
static pieceMap& PieceFactory::getPieceMap() {
	static pieceMap map;
	return map;
}