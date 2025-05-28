//
// Created by harri on 19/05/2025.
//

#ifndef MAZE_BONUSPOINTS_H
#define MAZE_BONUSPOINTS_H

#include <iostream>
#include <thread>

using namespace std;

class BonusPoints {
public:

    BonusPoints();
    ~BonusPoints();
    void createTimerThead();
    void cancel();

    static std::shared_ptr<BonusPoints> instance(){
        static std::shared_ptr<BonusPoints> s{new BonusPoints};
        return s;
    }

private:
    BonusPoints(BonusPoints const&) = delete;
    BonusPoints& operator=(BonusPoints const&) = delete;
    void Process();

private:
    bool m_isActive = false;
    std::shared_ptr<std::thread> m_thread;
};


#endif //MAZE_BONUSPOINTS_H
