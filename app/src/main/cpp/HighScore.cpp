//
// Created by harri on 22/05/2025.
//

#include "HighScore.h"


void HighScore::setHighScore(int points){
    m_highScores.push_back(points);
}


int HighScore::getHighScore(){
    stable_sort(m_highScores.begin(), m_highScores.end());
    return m_highScores.back();
}