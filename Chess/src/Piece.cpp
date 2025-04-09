#include "Piece.h"

Piece::Piece(std::string position):
	m_currentPosition{position},m_lastPosition{position}
{
}

std::string Piece::getPosition() const
{
	return m_currentPosition;
}
std::string Piece::getLastPosition()const {
	return m_lastPosition;
}
void Piece::setLastPosition(std::string position) {
	m_lastPosition = position;
}
void Piece::setPosition(const std::string& position)
{
	m_currentPosition = position;
}
