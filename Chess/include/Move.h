#pragma once
#include <string>
#include <iostream>

class Move {
   
public:
    struct MoveComparator {
        bool operator()(const std::unique_ptr<Move>& a, const std::unique_ptr<Move>& b) const {
            return a->getScore() < b->getScore();
        }
    };
    Move(const std::string& from, const std::string& to, int score);
    int getScore()const;
    void setDesPosition(const std::string& to);
    void setScore(const int newScore);
    std::string getDesPosition()const;
    std::string getFromPosition()const;

    friend std::ostream& operator<<(std::ostream& os, const Move& move);

private:
    std::string m_from;
    std::string m_to;
    int m_score;
};



