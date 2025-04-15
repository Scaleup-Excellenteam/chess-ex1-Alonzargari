#pragma once
#include "designPatterns/factory/PieceFactory.h"

//=========================================================
/*
* This function creates the desired piece based on the given symbol. 
*/
std::unique_ptr<Piece> PieceFactory::createPiece(const char pieceSymbole, const std::string& position) {
	auto it = getPieceMap().find(pieceSymbole);
	if (it != getPieceMap().end()) {
		return it->second(position);
	}
	return nullptr;
}

//=========================================================
/*
* Registers a piece creation function in the factory map 
using the given symbol that representing the type of piece.
and function that creates and returns a unique_ptr to a Piece
return true after inserting the pair into the map.
*/

bool PieceFactory::registerPiece(const char symbole, pieceFunc createPiecefunc) {
	getPieceMap().emplace(symbole, std::move(createPiecefunc));
	return true;
}

//=========================================================
/*
* This function Provides access to the static map that associates 
piece symbols with their creation functions.
return a reference to the static pieceMap used for registering and 
creating pieces.
*/

pieceMap& PieceFactory::getPieceMap() {
	static pieceMap map;
	return map;
}