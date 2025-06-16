//
// Created by harri on 09/05/2025.
//

#include "Ghost.h"
#include "Maze.h"


struct ThreadMessage
{
    ThreadMessage(std::shared_ptr<newGhostPosition> m) { msg = m; }
    std::shared_ptr<newGhostPosition> msg;
};


Ghost::Ghost(){

}

Ghost::~Ghost(){
}

void Ghost::createThread() {
    if (!m_thread)
        m_thread = std::unique_ptr<std::thread>(new thread(&Ghost::Process, this));
}

void Ghost::Process()
{
    shared_ptr<Maze> maze = Maze::instance();
    while (1)
    {
        setTimeOutForGhost(maze->getGameRound());
        bool gameOver = maze->isGameOver();
        int skipMessages = 0;
        if(gameOver)
            skipMessages = 2;

        std::this_thread::sleep_for(std::chrono::milliseconds(m_timeOutInMilliseconds));
        std::shared_ptr<ThreadMessage> msg;
        {
            // Wait for a message to be added to the queue
            std::unique_lock<std::mutex> lk(m_mutex);
            while (m_queue.empty())
                m_cv.wait(lk);

            if (m_queue.empty())
                continue;

            msg = m_queue.front();
            m_queue.pop();
            if(skipMessages){
                skipMessages--;
                continue;
            }
        }
        auto newPos = std::static_pointer_cast<newGhostPosition>(msg->msg);
        maze->setGhostPosition(newPos->pos);
    }
}

void Ghost::setTimeOutForGhost(int gameRound){
    switch(gameRound){
        case 1: {
            m_timeOutInMilliseconds = 1000;
            break;
        }
        case 2: {
            m_timeOutInMilliseconds = 750;
            break;
        }
        case 3: {
            m_timeOutInMilliseconds = 500;
            break;
        }
        case 4: {
            m_timeOutInMilliseconds = 300;
            break;
        }
        case 5: {
            m_timeOutInMilliseconds = 250;
            break;
        }
        case 6: {
            m_timeOutInMilliseconds = 200;
            break;
        }
        default:
            break;
    }
}

void Ghost::PostMsg(std::shared_ptr<newGhostPosition> data)
{

    std::shared_ptr<ThreadMessage> threadMsg(new ThreadMessage(data));

    // Add user data msg to queue and notify worker thread
    std::unique_lock<std::mutex> lk(m_mutex);
    m_queue.push(threadMsg);
    m_cv.notify_one();
}

