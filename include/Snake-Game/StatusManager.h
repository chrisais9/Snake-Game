/* 
 * title: StatusManager.h
 * author: 윤상건 - ggj06281@kookmin.ac.kr
 */

#ifndef SNAKE_STATUS_MANAGER
#define SNAKE_STATUS_MANAGER

#include "Primitives/Score.h"
#include "Primitives/Mission.h"

class StatusManager{
private:
    Score score;
    Mission mission;
public:
    StatusManager(int maxBody=10, int goalBody=10, int goalGrowth=5, int goalPoison=2, int goalGate=1);

    void scoreBody();
    void descoreBody();
    void scoreGrowth();
    void scorePoison();
    void scoreGate();

    const Score& getScore();
    const Mission& getMission();
};

#endif