#ifndef HWFINAL_SHUTTLE_H
#define HWFINAL_SHUTTLE_H

#include <memory>
#include "string"
#include "SpaceStation.h"
#include <queue>

#define MAX_PUnit 20
#define STOPPED 0
#define DOCKED 1
#define DEAD -1
#define MOVING 2
#define NOTEXIST -2
using namespace std;

class Shuttle {
public:
    Shuttle(string name, string pilot, float x, float y) : name(std::move(name)), pilot(std::move(pilot)), x(x), y(y) {}

    void go(float restTime = 1);

    const string &getName() const;

    int getStatus() const;

    void setStatus(int status_);

    void setRoute(const shared_ptr<SpaceStation>& sourSt, const shared_ptr<SpaceStation>& ds_);

    float getX() const;

    float getY() const;

private:
    string name;
    string pilot;
    float x;
    float y;
    int pUnit = 10;
    float speed = 0.5;
    int cargo = 0;
    int status = STOPPED;
    queue<pair<pair<float, float>, shared_ptr<SpaceStation>>> routeQue{}; // queue of pair coordinates + ptr
    float leftTime = -1;
//    shared_ptr<SpaceStation> sourSt = nullptr;
//    shared_ptr<SpaceStation> ds = nullptr;
//
    float moving(float time);
    float docking(float time);
};


#endif //HWFINAL_SHUTTLE_H
