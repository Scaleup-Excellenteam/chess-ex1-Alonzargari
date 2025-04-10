#include "Piece.h"

Piece::Piece(std::string position,std::string teamColor):
	m_currentPosition{position},m_lastPosition{position},m_teamColor{teamColor},m_toErase{false}
{
}

std::string Piece::getPosition() const
{
	return m_currentPosition;
}
std::string Piece::getLastPosition()const {
	return m_lastPosition;
}
std::string Piece::getTeamColor()const{
	return m_teamColor;
}
void Piece::setLastPosition(std::string position) {
	m_lastPosition = position;
}
void Piece::setPosition(const std::string& position)
{
	m_currentPosition = position;
}

void Piece::setToErase()
{
	m_toErase = true;
}

bool Piece::toErase() const
{
	return m_toErase;
}
