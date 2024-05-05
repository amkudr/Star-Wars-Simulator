#include <algorithm>
#include "TIEBomber.h"

float TIEBomber::getSpeed() const {
    return speed;
}

string TIEBomber::getClassName() const {
    return "bomber";
}

void TIEBomber::destination(const shared_ptr<SpaceStation> &dest) {

    destSt = dest;
    Spaceship::destination(dest);
    vector<shared_ptr<SpaceStation>> notVisitedSt;

    //Create patrol route
    for (auto &st: *stations_ptr) {
        notVisitedSt.emplace_back(st);
    }
    float min_dist = numeric_limits<float>::max();
    float dist;
    float curr_x = getX();
    float curr_y = getY();
    shared_ptr<SpaceStation> station;
    while (!notVisitedSt.empty()) {
        for (auto &st: notVisitedSt) {
            dist = st->findDist(curr_x, curr_y);
            if (dist < min_dist) {
                min_dist = dist;
                station = st;
            }
            else if (dist == min_dist && st->getName() < station->getName()) {
                station = st;
            }
        }
        notVisitedSt.erase(find(notVisitedSt.begin(), notVisitedSt.end(), station));
        routeQue.emplace(make_pair(station->getX(), station->getY()), station);
        curr_x = station->getX();
        curr_y = station->getY();
        min_dist = numeric_limits<float>::max();
    }
    routeQue.emplace(make_pair(dest->getX(), dest->getY()), dest);
}



//    priority_queue<pair<float, shared_ptr<SpaceStation>>> priorityQueue;
//    for (const auto &st: *stations_ptr) { //Sort by distance
//        priorityQueue.emplace(-findDist(st->getX(), st->getY()), st);
//    }
//    while (!priorityQueue.empty()) {
//        auto station = priorityQueue.top();
//        priorityQueue.pop();
//        routeQue.emplace(make_pair(station.second->getX(), station.second->getY()), station.second);
//    }
//    routeQue.emplace(make_pair(dest->getX(), dest->getY()), dest);


void TIEBomber::go(float restTime) {
    while (status != STOPPED && status != DEAD && status != DOCKED && restTime > 0) {
        switch (status) {
            case MOVING:
                restTime = moving(restTime);
                if (restTime != 0) {
//                    if(routeQue.front().second->getName().empty()) course(routeQue.front().second->getX());
                    routeQue.pop();
                }
//                    if (destSt != nullptr) {
//                        visitedSt.emplace_back(routeQue.front().second);
//                    }
//                    routeQue.pop();
//                    findNewDest();
//                }
                break;
        }
    }
}

void TIEBomber::findNewDest() {
    if (visitedSt.size() == stations_ptr->size()) {
        if (destSt == nullptr) {
            setStatus(DOCKED);
            return;
        } else {
            routeQue.emplace(make_pair(destSt->getX(), destSt->getY()), destSt);
            destSt = nullptr;
            return;
        }
    }
    float min_dist = numeric_limits<float>::max();
    float dist;
    shared_ptr<SpaceStation> station;
    for (const auto &st: *stations_ptr) {
        if (find(visitedSt.begin(), visitedSt.end(), st) == visitedSt.end()) {
            dist = findDist(st->getX(), st->getY());
            if (dist < min_dist) {
                station = st;
                min_dist = dist;
            } else if (dist == min_dist) {
                if (st->getName() < station->getName()) {
                    station = st;
                }
            }

        }
    }
    routeQue.emplace(make_pair(station->getX(), station->getY()), station);
}

//void TIEBomber::position(float x, float y) {
//    queue<pair<pair<float, float>, shared_ptr<SpaceStation>>> tempQue; //Priority for position course
//    while (!routeQue.empty()) {
//        tempQue.emplace(routeQue.front());
//        routeQue.pop();
//    }
//    Spaceship::position(x, y);
//    while (!tempQue.empty()) {
//        routeQue.emplace(tempQue.front());
//        tempQue.pop();
//    }
//}

