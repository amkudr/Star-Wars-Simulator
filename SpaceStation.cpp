#include "SpaceStation.h"

const string &SpaceStation::getName() const {
    return name;
}

float SpaceStation::getX() const {
    return x;
}

float SpaceStation::getY() const {
    return y;
}

int SpaceStation::getContNum() const {
    return ContNum;
}

int SpaceStation::getSupNum() const {
    return SupNum;
}

void SpaceStation::setX(float x_) {
    SpaceStation::x = x_;
}

void SpaceStation::setY(float y_) {
    SpaceStation::y = y_;
}

void SpaceStation::setContNum(int contNum) {
    ContNum = contNum;
}
