#include "Move.h"

Move::Move(const std::string& from, const std::string& to, int score)
	: m_from(from), m_to(to), m_score(score) {}

int Move::getScore() const{ return m_score;}

