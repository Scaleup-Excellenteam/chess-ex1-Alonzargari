#pragma once
#include <iostream>


class Piece {
public:
	Piece(std::string position,std::string teamColor);
	virtual bool doMove(std::string destinyPos) = 0;
	std::string getPosition() const;
	std::string getLastPosition() const;
	std::string getTeamColor() const;
	void setLastPosition(std::string position);
	void setPosition(const std::string&);
private:
	static bool m_register;
	std::string m_lastPosition;
	std::string m_currentPosition;
	std::string m_teamColor;
};