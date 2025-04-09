#pragma once
#include <iostream>


class Piece {
public:
	Piece(std::string position);
	virtual bool doMove(std::string destinyPos) = 0;
	std::string getPosition() const;
	std::string getLastPosition() const;
	void setLastPosition(std::string position);
	void setPosition(const std::string&);
private:
	std::string m_lastPosition;
	std::string m_currentPosition;
};