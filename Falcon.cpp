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
    setSpeed(speed_);
    Spaceship::course(angle_);
}

void Falcon::position(float x_, float y_, float speed_) {
    setSpeed(speed_);
    Spaceship::position(x_, y_);
}

void Falcon::dead() {
    setStatus(DEAD);
}

