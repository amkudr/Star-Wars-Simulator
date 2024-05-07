#include "StarDestroyer.h"

float StarDestroyer::getSpeed() const {
    return speed;
}

string StarDestroyer::getClassName() const {
    return "destroyer";
}


float StarDestroyer::shoot(float p_x, float p_y) { //return time to shot
    return float(findDist(p_x, p_y)/0.3);
}
