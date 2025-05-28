//
// Created by harri on 05/05/2025.
//
#include "Maze.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>

string ghost = "\U0001F47B";
string player = "\U0001F600";
string background_red = "\U0001F7E5";
string background_blue = "\U0001F7E6";
string background_orange = "\U0001F7E7";
string background_yellow = "\U0001F7E8";
string background_green = "\U0001F7E9";
string background_purple = "\U0001F7EA";
string background_brown = "\U0001F7EB";
string bonus = "\U0001F382";
string prize = "\U0001F352";
string newline = "\n";
auto rng = std::default_random_engine {};
const int amountOfBonusPoints = 5;


void Maze::newGame(int width, int height){

    if( width == 0 || height == 0)
        return;

    clearMap();
    setBackGroundColor();
    m_map.resize(height, vector<string>(width));
    m_height = height;
    m_width = width;
    paintBackground();
    m_map[0][0] = player;
    addPrizes();
    m_game_over = false;
    m_gameRound = 1;
    m_points = 0;

}

void Maze::paintBackground(){
    for(int i=0; i<m_height;i++){
        for(int j=0;j<m_width;j++)
        {
            if(j == m_width-1){
                m_map[i][j] = newline;
            }
            else{
                m_map[i][j] = m_backround;
            }
        }
    }
}

void Maze::nextLevel(pair<int,int> playerPos){
    setBackGroundColor();
    paintBackground();
    addPrizes();
    m_map[playerPos.first][playerPos.second] = player;
    m_gameRound++;
}

void Maze::setBackGroundColor()
{
    vector<string> allMapColors= {background_red, background_blue, background_orange, background_yellow,
                                  background_green, background_purple, background_brown};
    std::shuffle(std::begin(allMapColors), std::end(allMapColors), rng);
    m_backround = allMapColors.front();
}

void Maze::clearMap(){
    vector<vector<string>>::iterator it1;
    vector<string>::iterator it2;

    for(it1 = m_map.begin(); it1 != m_map.end(); it1++){
        for(it2 = it1->begin(); it2 != it1->end(); it2++){
            *it2 = "";
        }
    }
}

void Maze::addPrizes(){
 int amountOfBalls=10;
 for (int i=0; i < amountOfBalls+1; i++){
     int ballWidthCoordinate = rand() % m_width - 1;
     int ballHeightCoordinate = rand() % m_height;

     if(ballHeightCoordinate != -1 && ballWidthCoordinate != -1)
        m_map[ballHeightCoordinate][ballWidthCoordinate] = prize;
 }
}


string Maze::getMap(){
    string map;

    vector<vector<string>>::iterator it1;
    vector<string>::iterator it2;

    for(it1 = m_map.begin(); it1 != m_map.end(); it1++){
        for(it2 = it1->begin(); it2 != it1->end(); it2++){
          map.append(*it2);
        }
    }

    return map;
}


int Maze::moveItem(int aDirection){

    pair<int, int> playerPos = findPlayer(m_map, player);
    if(playerPos.first != -1 && playerPos.second != -1) {
        moveTo((direction) aDirection, playerPos);
        pair<int, int> prizeInMap = findPlayer(m_map, prize);
        if (prizeInMap.first == -1 && prizeInMap.second == -1) {
            nextLevel(playerPos);
        }
    }
    return m_points;
}

void Maze::moveTo(direction aDirection, pair<int,int>& playerPos){
    switch (aDirection) {
        case LEFT:{
            if(playerPos.second >=1){
                m_map[playerPos.first][playerPos.second] = m_backround;
                if(m_map[playerPos.first][playerPos.second-1] == prize){
                    m_points++;
                }else if(m_map[playerPos.first][playerPos.second-1] == bonus){
                    m_points += amountOfBonusPoints;
                }
                m_map[playerPos.first][playerPos.second-1] = player;
            }
            break;
        }
        case RIGHT:{
            if(playerPos.second < m_width-2){
                m_map[playerPos.first][playerPos.second] = m_backround;
                if(m_map[playerPos.first][playerPos.second+1] == prize){
                    m_points++;
                }else if(m_map[playerPos.first][playerPos.second+1] == bonus){
                    m_points += amountOfBonusPoints;
                }
                m_map[playerPos.first][playerPos.second+1] = player;
            }
            break;
        }
        case UP:{
            if(playerPos.first > 0){
                m_map[playerPos.first][playerPos.second] = m_backround;
                if(m_map[playerPos.first-1][playerPos.second] == prize){
                    m_points++;
                }else if(m_map[playerPos.first-1][playerPos.second] == bonus){
                    m_points += amountOfBonusPoints;
                }
                m_map[playerPos.first-1][playerPos.second] = player;
            }
            break;
        }
        case DOWN:{
            if(playerPos.first < m_height-1){
                m_map[playerPos.first][playerPos.second] = m_backround;
                if(m_map[playerPos.first+1][playerPos.second] == prize){
                    m_points++;
                }else if(m_map[playerPos.first+1][playerPos.second] == bonus){
                    m_points += amountOfBonusPoints;
                }
                m_map[playerPos.first+1][playerPos.second] = player;
            }
            break;
        }
        default:
            break;
    }
}


pair<int, int> Maze::findPlayer(const vector<vector<string>>& stringArr,
                               const string& keyString)
{
    vector<string> flattenedArr;
    for (const auto& row : stringArr) {
        flattenedArr.insert(flattenedArr.end(), row.begin(),
                            row.end());
    }

    auto it = find(flattenedArr.begin(), flattenedArr.end(),
                   keyString);
    if (it != flattenedArr.end()) {
        int index = distance(flattenedArr.begin(), it);
        int cols = stringArr[0].size();
        return { index / cols, index % cols };
    }

    return { -1, -1 };
}


pair<int,int> Maze::getPlayerPosition(){
    return findPlayer(m_map, player);
}

void Maze::setGhostPosition(pair<int, int>& newGhostPosition) {

    if(m_game_over){
        return;
    }

    if(newGhostPosition.first == -1 || newGhostPosition.second == -1)
        return;

    pair<int,int> currGhost = findPlayer(m_map,ghost);
    if(currGhost.first != -1 && currGhost.second != -1 ){
        m_map[currGhost.first][currGhost.second] = m_backround;
    }

    pair<int,int> currPlayer = findPlayer(m_map,player);
    checkCollision(newGhostPosition, currPlayer);
    checkCollision(currGhost, currPlayer);
    m_map[newGhostPosition.first][newGhostPosition.second] = ghost;
}

void Maze::checkCollision(pair<int,int>& ghostPosition, pair<int,int>& playerPosition){
    if( ghostPosition == playerPosition){
        m_game_over = true;
        m_gameRound = 1;
    }
}

void Maze::setBonus(){

    pair currentBonus = findPlayer(m_map, bonus);
    if(currentBonus.first != -1 && currentBonus.second != -1){
        m_map[currentBonus.first][currentBonus.second] = m_backround;
    }

    //set new bonus
    int bonusWidthCoordinate = rand() % m_width - 1;
    int bonusHeightCoordinate = rand() % m_height;

    if(bonusHeightCoordinate != -1 && bonusWidthCoordinate != -1)
        m_map[bonusHeightCoordinate][bonusWidthCoordinate] = bonus;
}