//
// Created by harri on 05/05/2025.
//

#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace  std;

enum direction{
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
};

class Maze{
public:
    Maze(Maze const&) = delete;
    Maze& operator=(Maze const&) = delete;
    string getMap();
    int getGameRound(){return m_gameRound;}

    static std::shared_ptr<Maze> instance(){
        static std::shared_ptr<Maze> s{new Maze};
        return s;
    }
    void newGame(int width, int height);
    int moveItem(int aDirection);
    pair<int,int> getPlayerPosition();
    void setGhostPosition(pair<int, int> &newGhostPosition);
    bool isGameOver(){return m_game_over;}
    void setBonus();
    int getPoints(){return m_points;}
private:
    Maze(){}
    void moveTo(direction aDirection, pair<int,int>& playerPos);
    void addPrizes();
    void clearMap();
    void setBackGroundColor();
    void nextLevel(pair<int,int> playerPos);
    void paintBackground();
    void checkCollision(pair<int,int>& ghostPosition, pair<int,int>& playerPosition);
    pair<int, int> findItemFromMap(const string& keyString);

private:
    vector<vector<string>> m_map;
    int m_height = 0;
    int m_width = 0;
    bool m_game_over = 0;
    int m_points = 0;
    int m_gameRound = 0;
    string m_backround;
};

#endif //MAZE_MAZE_H
