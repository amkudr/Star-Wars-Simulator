#include "StarDestroyer.h"

float StarDestroyer::getSpeed() const {
    return speed;
}

string StarDestroyer::getClassName() const {
    return "destroyer";
}

void StarDestroyer::go(float restTime) {
    while (status != STOPPED && status != DEAD && status != DOCKED && restTime > 0) {
        switch (status) {
            case MOVING:
                restTime = moving(restTime);
                if (restTime != 0 && getStatus()!=STOPPED) {
                    routeQue.pop();
                }
                break;
        }
    }
}

float StarDestroyer::shoot(float p_x, float p_y) { //return time to shot
    return float(findDist(p_x, p_y)/0.3);
}
