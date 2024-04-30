//

#include "Shuttle.h"

#include <utility>
#include <cmath>
#include <iostream>

void Shuttle::setRoute(const shared_ptr<SpaceStation>& sourSt_, const shared_ptr<SpaceStation>& ds_) {
    routeQue.emplace(make_pair(sourSt_->getX(), sourSt_->getY()), sourSt_);
    routeQue.emplace(make_pair(ds_->getX(), ds_->getY()), ds_);
    status = MOVING;
}

void Shuttle::go(float restTime) {
    if (status == STOPPED || status == DEAD || restTime == 0 || routeQue.empty())
        return;

    switch (status) {
        case MOVING:
            restTime = moving(restTime);
            break;
        case DOCKED:
            restTime = docking(restTime);
            break;
    }

    go(restTime);
}
float Shuttle::moving(float time) {
    if (routeQue.empty()) {
        status = STOPPED;
        return time;
    }
//    shared_ptr<SpaceStation> dest;
//    dest = routeQue.front();
//    float dest_x = dest->getX();
//    float dest_y = dest->getY();
    float dest_x = routeQue.front().first.first;
    float dest_y = routeQue.front().first.second;

    auto dist = float(sqrt(pow(dest_x - x, 2) + pow(dest_y - y, 2)));

    float dist_time = dist / speed;

    if (dist_time > time) {
        x = x + (dest_x - x) / dist * speed * time; //new x
        y = y + (dest_y - y) / dist * speed * time; //new y
    } else {
        x = dest_x;
        y = dest_y;
        time = time - dist_time;
        status = DOCKED;
        return time;
    }
    return 0;
}

const string &Shuttle::getName() const {
    return name;
}

int Shuttle::getStatus() const {
    return status;
}

void Shuttle::setStatus(int status_) {
    Shuttle::status = status_;
}

float Shuttle::getX() const {
    return x;
}

float Shuttle::getY() const {
    return y;
}

float Shuttle::docking(float time) {
    if (routeQue.empty()) {
        status = STOPPED;
        return 0;
    }
    shared_ptr<SpaceStation> destSt = routeQue.front().second;
    if (destSt->getName() == "DS") {
        if (leftTime == -1) leftTime = 1;
        float leftTime2 = leftTime - time;
        if (leftTime2 <= 0) {
            destSt->setContNum(destSt->getContNum() + cargo);
            cargo = 0;
            pUnit++;
            leftTime = -1;
            status = MOVING;
            routeQue.pop();
            std::cout<<" Fuck It was Hard but now i got "<<this->pUnit<<std::endl;
            return abs(leftTime2);
        } else {
            leftTime = leftTime2;
            return 0;
        }
    } else if (destSt != nullptr) {
        int resCont = destSt->getContNum();
        if(leftTime == -1) leftTime = 1;
        float leftTime2 = leftTime - time;
        if (leftTime2 <= 0) {
            if(resCont > 5) cargo = 5;
            else cargo = resCont;
            destSt->setContNum(resCont - cargo);
            leftTime = -1;
            status = MOVING;
            routeQue.pop();
            return abs(leftTime2);
        }
        else {
            leftTime = leftTime2;
            return 0;
        }
    }
    else {
        routeQue.pop();
        status = STOPPED;
        return 0;
    }
}
