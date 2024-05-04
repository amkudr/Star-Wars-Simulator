#include <algorithm>
#include "TIEBomber.h"

float TIEBomber::getSpeed() const {
    return speed;
}

string TIEBomber::getClassName() const {
    return "bomber";
}

void TIEBomber::destination(const shared_ptr<SpaceStation> &dest) {
    routeQue.emplace(make_pair(dest->getX(), dest->getY()), dest);
    destSt = dest;
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
    setStatus(MOVING);
}

void TIEBomber::go(float restTime) {
    while (status != STOPPED && status != DEAD && status != DOCKED && restTime > 0) {
        switch (status) {
            case MOVING:
                restTime = moving(restTime);
                if (restTime != 0) {
                    if (destSt != nullptr) {
                        visitedSt.emplace_back(routeQue.front().second);
                    }
                    routeQue.pop();
                    findNewDest();
                }
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

