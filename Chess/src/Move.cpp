#include "Move.h"

Move::Move(const std::string& from, const std::string& to, int score)
	: m_from(from), m_to(to), m_score(score) {}

int Move::getScore() const{ return m_score;}

void Move::setDesPosition(const std::string& to)
{
	m_to = to;
}

void Move::setScore(const int newScore)
{
	m_score = newScore;
}

std::string Move::getDesPosition() const
{
	return m_to;
}

