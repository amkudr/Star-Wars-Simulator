//

#include "Falcon.h"

float Falcon::getSpeed() const {
    return speed;
}

string Falcon::getClassName() const {
    return "falcon";
}

void Falcon::setSpeed(float speed_) {
    speed = speed_;
}

void Falcon::course(float angle_, float speed_) {
    setSpeed(speed_/1000);
    Spaceship::course(angle_);
}

void Falcon::position(float x_, float y_, float speed_) {
    setSpeed(speed_/1000);
    Spaceship::position(x_, y_);
}

void Falcon::dead() {
    setStatus(DEAD);
}


void Falcon::setPUnit(int pUnit_) {
    Falcon::pUnit = pUnit_;
}

int Falcon::getPUnit() const {
    return pUnit;
}

