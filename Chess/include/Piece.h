#pragma once
#include <iostream>


class Piece {
public:
	Piece(const std::string& position,const std::string& teamColor,int rank);
	virtual ~Piece() = default;
	virtual bool canDoStep(const std::string& destinyPos, bool isEnemyThere) = 0;
	int getPieceRank();
	std::string getPosition() const;
	std::string getLastPosition() const;
	std::string getTeamColor() const;
	void setLastPosition(const std::string& position);
	void setPosition(const std::string&);
	void setToErase(bool erase);
	bool toErase()const;
	virtual bool ignorePath() ;
private:
	int m_rank;
	static bool m_register;
	std::string m_lastPosition;
	std::string m_currentPosition;
	std::string m_teamColor;
	bool m_toErase;
};