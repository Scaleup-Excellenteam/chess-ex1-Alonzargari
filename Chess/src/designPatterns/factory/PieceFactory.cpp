#pragma once
#include "designPatterns/factory/PieceFactory.h"

std::unique_ptr<Piece> PieceFactory::createPiece(char pieceSymbole, std::string position) {
	auto it = getPieceMap().find(pieceSymbole);
	if (it != getPieceMap().end()) {
		return it->second(position);
	}
	return nullptr;
}
bool PieceFactory::registerPiece(char symbole, pieceFunc createPiecefunc) {
	getPieceMap().emplace(symbole, std::move(createPiecefunc));
	return true;
}
pieceMap& PieceFactory::getPieceMap() {
	static pieceMap map;
	return map;
}