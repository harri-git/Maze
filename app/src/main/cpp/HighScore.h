//
// Created by harri on 22/05/2025.
//

#ifndef MAZE_HIGHSCORE_H
#define MAZE_HIGHSCORE_H

#include <iostream>
#include <vector>
using namespace std;

class HighScore {
public:
    HighScore(HighScore const&) = delete;
    HighScore& operator=(HighScore const&) = delete;

    static std::shared_ptr<HighScore> instance(){
        static std::shared_ptr<HighScore> s{new HighScore};
        return s;
    }

    void setHighScore(int points);
    int getHighScore();
private:
    HighScore(){m_highScores.push_back(0);}
private:
    vector<int> m_highScores;
};


#endif //MAZE_HIGHSCORE_H
