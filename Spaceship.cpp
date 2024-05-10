#include <iomanip>
#include <sstream>
#include "Spaceship.h"
#include <cmath>


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
    status = status_;
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

            if (routeQue.empty() && isCourse()) os << "Heading on course " << getAngle() << " deg";
            else if (routeQue.front().second != nullptr) os << "Heading to " << routeQue.front().second->getName();
            else os << "Moving to (" << routeQue.front().first.first << "," << routeQue.front().first.second << ")";
            os << ", speed " << getSpeed() * 1000 << "km/h";
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

float Spaceship::findDist(float p_x, float p_y) const {

    return float(sqrt(pow(p_x - x, 2) + pow(p_y - y, 2)));
}

float Spaceship::moving(float time) {
    if (status != MOVING) {
        return time;
    }
    if (isCour) { //If moving on course
        auto radians = float(getAngle() * M_PI / 180.0);
        x = x + cos(radians) * getSpeed() * time;
        y = y + sin(radians) * getSpeed() * time;
        return 0;
    }
    if (routeQue.empty()) {
        setStatus(STOPPED);
        return time;
    }

    float dest_x = routeQue.front().first.first;
    float dest_y = routeQue.front().first.second;

    auto dist = findDist(dest_x, dest_y);

    float dist_time = dist / getSpeed();

    if (dist_time > time) { //Check if time is enough to get the destination
        x = x + (dest_x - x) / dist * getSpeed() * time; //new x
        y = y + (dest_y - y) / dist * getSpeed() * time; //new y
    } else {
        x = dest_x;
        y = dest_y;
        time = time - dist_time;

        //Spaceship got destination, have to change status
        if (routeQue.front().second != nullptr) {
            if (getClassName() == "shuttle") setStatus(SUPPLYING);
            else {
                if (routeQue.size() == 1) {
                    status = DOCKED;
                }
                routeQue.pop();
            }
        } else {
            if (routeQue.size() == 1) {
                setStatus(STOPPED);
            }
            routeQue.pop();
        }
        return time;
    }
    return 0;
}

void Spaceship::position(float x_, float y_) {
    while (!routeQue.empty()) routeQue.pop();
    routeQue.emplace(make_pair(x_, y_), nullptr);
    setStatus(MOVING);

}

void Spaceship::destination(const shared_ptr<SpaceStation> &dest) {
    while (!routeQue.empty()) routeQue.pop();
    routeQue.emplace(make_pair(dest->getX(), dest->getY()), dest);
    setStatus(MOVING);
}

void Spaceship::course(float angle_) {
    while (!routeQue.empty()) routeQue.pop();
    angle = angle_;
    isCour = true;
    setStatus(MOVING);

}

float Spaceship::getAngle() const {
    return angle;
}

bool Spaceship::isCourse() const {
    return isCour;
}

void Spaceship::stop() {
    if (status != DEAD) setStatus(STOPPED);
    while (!routeQue.empty()) routeQue.pop();
    isCour = false;
}

void Spaceship::go(float restTime) {
    while (status != STOPPED && status != DEAD && status != DOCKED && restTime > 0) {
        switch (getStatus()) {
            case MOVING:
                restTime = moving(restTime);
                break;
        }
    }
}

void Spaceship::setX(float x_) {
    Spaceship::x = x_;
}

void Spaceship::setY(float y_) {
    Spaceship::y = y_;
}

