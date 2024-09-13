#include "Shuttle.h"

#include <utility>
#include <iostream>
#include <cmath>


void Shuttle::start_supply(const shared_ptr<SpaceStation> &sourSt_, const shared_ptr<SpaceStation> &ds_) {
    routeQue.emplace(make_pair(sourSt_->getX(), sourSt_->getY()), sourSt_);
    routeQue.emplace(make_pair(ds_->getX(), ds_->getY()), ds_);
    status = MOVING;
}

void Shuttle::go(float restTime) {
    while (status != STOPPED && status != DEAD && status != DOCKED && restTime > 0) {
        switch (status) {
            case MOVING:
                restTime = moving(restTime);
                break;
            case SUPPLYING:
                restTime = supplying(restTime);
                break;
        }
    }
}


float Shuttle::supplying(float time) {
    if (status != SUPPLYING) return time;
    if (routeQue.empty()) {
        status = DOCKED;
        return 0;
    }

    shared_ptr<SpaceStation> destSt = routeQue.front().second;
    if (destSt->getName() == "DS") {
        if (leftTime == -1) leftTime = 1;
        float leftTime2 = leftTime - time;
        if (leftTime2 <= 0) {
            destSt->setContNum(destSt->getContNum() - cargo);
            cargo = 0;
            pUnit++;
            leftTime = -1;
            routeQue.pop();
            if (routeQue.empty()) setStatus(DOCKED);
            else setStatus(MOVING);
            std::cout << " Fuck It was Hard but now i got " << this->pUnit << std::endl;
            return abs(leftTime2);
        } else {
            leftTime = leftTime2;
            return 0;
        }
    } else {
        int resCont = destSt->getContNum();
        if (leftTime == -1) leftTime = 1;
        float leftTime2 = leftTime - time;
        if (leftTime2 <= 0) {
            if (resCont > 5) cargo = 5;
            else cargo = resCont;
            destSt->setContNum(resCont - cargo);
            leftTime = -1;
            status = MOVING;
            routeQue.pop();
            return abs(leftTime2);
        } else {
            leftTime = leftTime2;
            return 0;
        }
    }
}

string Shuttle::getClassName() const {
    return "shuttle";
}

float Shuttle::getSpeed() const {
    return speed;
}


void Shuttle::setPUnit(int pUnit_) {
    Shuttle::pUnit = pUnit_;
}

void Shuttle::setCargo(int cargo_) {
    Shuttle::cargo = cargo_;
}

int Shuttle::getPUnit() const {
    return pUnit;
}
