//
#include <iomanip>
#include <sstream>
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

string Spaceship::getFullStatus() const {
    ostringstream os;
    os << getClassName() << " " << name << " at " << "(" << std::fixed
       << std::setprecision(2) << x << "," << y << "), ";
    switch (status) {
        case STOPPED:
            os << "Stopped";
            break;
        case DOCKED:
            os << "Docked";
            break;
        case DEAD:
            os << "Dead";
            break;
        case MOVING:
            os << "Heading to " << routeQue.front().second->getName() << ", speed " << getSpeed() * 1000 << "km/h";
            break;
        case SUPPLYING:
            os << "Docked";
            break;
        case NOTEXIST:
            os << "Status does not exist";
            break;
    }
    return os.str();
}

string Spaceship::getClassName() const {
    return "Spaceship";
}

float Spaceship::getSpeed() const {
    return speed;
}

