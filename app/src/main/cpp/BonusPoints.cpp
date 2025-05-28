//
// Created by harri on 19/05/2025.
//

#include "BonusPoints.h"
#include "Maze.h"

BonusPoints::BonusPoints(){

}


BonusPoints::~BonusPoints(){

}


void BonusPoints::createTimerThead(){
    m_thread = std::shared_ptr<std::thread>(new thread(&BonusPoints::Process, this));
    m_thread->detach();
    m_isActive = true;
}

void BonusPoints::Process(){
    shared_ptr<Maze> maze = Maze::instance();
    while(m_isActive){
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        maze->setBonus();
    }
}

void BonusPoints::cancel(){
    m_isActive = false;
}
