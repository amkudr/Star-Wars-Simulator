#include <algorithm>
#include "TIEBomber.h"

float TIEBomber::getSpeed() const {
    return speed;
}

string TIEBomber::getClassName() const {
    return "bomber";
}

void TIEBomber::destination(const shared_ptr<SpaceStation> &dest) {

    Spaceship::destination(dest);
    vector<shared_ptr<SpaceStation>> notVisitedSt;

    //Create patrol route
    for (auto &st: *stations_ptr) {
        notVisitedSt.emplace_back(st);
    }
    float min_dist = numeric_limits<float>::max();
    float dist;
    float curr_x = dest->getX();
    float curr_y = dest->getY();
    shared_ptr<SpaceStation> station;
    while (!notVisitedSt.empty()) {
        for (auto &st: notVisitedSt) {
            dist = st->findDist(curr_x, curr_y);
            if (dist < min_dist) {
                min_dist = dist;
                station = st;
            } else if (dist == min_dist && st->getName() < station->getName()) {
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
