//

#include "Spaceship.h"

float Spaceship::getX() const {
    return x;
}

float Spaceship::getY() const {
    return y;
}

const string &Spaceship::getName() const {
    return name;
}

int Spaceship::getStatus() const {
    return status;
}


void Spaceship::setStatus(int status_) {
    Spaceship::status = status_;
}

