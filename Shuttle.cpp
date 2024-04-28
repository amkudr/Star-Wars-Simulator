//

#include "Shuttle.h"

#include <utility>
#include <cmath>

void Shuttle::setRoute(shared_ptr<SpaceStation> sourSt_, shared_ptr<SpaceStation> ds_) {
    routeQue.emplace(make_pair(sourSt_->getX(), sourSt_->getY()), sourSt_);
    routeQue.emplace(make_pair(ds_->getX(), ds_->getY()), ds_);
    status = MOVING;
}

void Shuttle::go() {
    float time = 1;
    switch (status) {
        case STOPPED:
            return;
        case MOVING:
            moving(time);
            break;

    }
}

void Shuttle::moving(float time) {
    if(routeQue.empty()) {
        status = STOPPED;
        return;
    }
//    shared_ptr<SpaceStation> dest;
//    dest = routeQue.front();
//    float dest_x = dest->getX();
//    float dest_y = dest->getY();
    float dest_x = routeQue.front().first.first;
    float dest_y = routeQue.front().first.second;

    auto dist = float(sqrt(pow(dest_x - x, 2) + pow(dest_y - y, 2)));

    float dist_time = dist/speed;

    if (dist_time > time) {
        x = x + (dest_x - x) / dist * speed * time; //new x
        y = y + (dest_y - y) / dist * speed * time; //new y
    }
    else{
        x = dest_x;
        y = dest_y;
        time = time - dist_time;
        return;
    }

}

const string &Shuttle::getName() const {
    return name;
}

int Shuttle::getStatus() const {
    return status;
}

void Shuttle::setStatus(int status) {
    Shuttle::status = status;
}

float Shuttle::getX() const {
    return x;
}

float Shuttle::getY() const {
    return y;
}
