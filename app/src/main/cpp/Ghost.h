//
// Created by harri on 09/05/2025.
//

#ifndef MAZE_GHOST_H
#define MAZE_GHOST_H

#include <iostream>
#include <queue>
#include <utility>
#include <thread>
#include "Maze.h"
using namespace std;

struct newGhostPosition
{
    pair<int,int> pos;
};

struct ThreadMessage;

class Ghost {
public:
    Ghost();
    ~Ghost();
    void PostMsg(std::shared_ptr<newGhostPosition> data);
    void createThread();
private:
    Ghost(Ghost const&) = delete;
    Ghost& operator=(Ghost const&) = delete;
    void Process();
    void setTimeOutForGhost(int gameRound);
private:
   std::unique_ptr<std::thread> m_thread;
   std::queue<std::shared_ptr<ThreadMessage>> m_queue;
   mutex m_mutex;
   condition_variable m_cv;
   int m_timeOutInMilliseconds = 1000;
};


#endif //MAZE_GHOST_H
