#include "Piece.h"

//=========================================================
/*
* Every piece recived current position on the board and its team color
*/

Piece::Piece(const std::string& position, const std::string& teamColor):
	m_currentPosition{position},m_lastPosition{position},m_teamColor{teamColor},m_toErase{false}
{
}

//=========================================================
/*
* this function return the current position on the board
*/

std::string Piece::getPosition() const
{
	return m_currentPosition;
}

//=========================================================
/*
* this function return the last position, its importent when 
* when the movment of current piece cause check
*/

std::string Piece::getLastPosition()const {
	return m_lastPosition;
}

//=========================================================
/*
* this function return the team color
*/

std::string Piece::getTeamColor()const{
	return m_teamColor;
}

//=========================================================
/*
* this function set the last position to the destiny position
*/

void Piece::setLastPosition(const std::string& position) {
	m_lastPosition = position;
}

//=========================================================
/*
* this function set the current position to the destiny position
*/

void Piece::setPosition(const std::string& position)
{
	m_currentPosition = position;
}

//=========================================================
/*
* set the to erase bolean member that response to signal 
that this object need to erased from the vector
*/

void Piece::setToErase()
{
	m_toErase = true;
}

//=========================================================
/*
* this function return the erase bolean member signal
*/

bool Piece::toErase() const
{
	return m_toErase;
}

//=========================================================
/*
* most of the pieces in the board need to check if the path 
is clear and some of them can ignore the path (like the knight) 
*/

bool Piece::ignorePath()
{
	return false;
}
