#pragma once
#include <string>

class Move {
   
public:
    Move(const std::string& from, const std::string& to, int score);
    int getScore()const;
    void setDesPosition(const std::string& to);
    void addScore(const int newScore);
    std::string getDesPosition()const;
private:
    std::string m_from;
    std::string m_to;
    int m_score;
};

struct MoveComparator {
    bool operator()(const Move& a, const Move& b) const {
        return a.getScore() < b.getScore();
    }
};