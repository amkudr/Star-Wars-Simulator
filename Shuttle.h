#ifndef HWFINAL_SHUTTLE_H
#define HWFINAL_SHUTTLE_H

#include <utility>
#include "Spaceship.h"

#define MAX_PUnit 20

using namespace std;

class Shuttle: public Spaceship {
public:
//    Shuttle(string name, string pilot, float x, float y) : name(std::move(name)), pilot(std::move(pilot)), x(x), y(y) {}
    Shuttle(string name, string pilot, float x, float y): Spaceship(std::move(name), std::move(pilot), x, y) {};
    void go(float restTime) override;
    void start_supply(const shared_ptr<SpaceStation>& sourSt_, const shared_ptr<SpaceStation>& ds_);


private:
    int pUnit = 10;
    float speed = 0.5;
    int cargo = 0;
    float leftTime = -1;
//    shared_ptr<SpaceStation> sourSt = nullptr;
//    shared_ptr<SpaceStation> ds = nullptr;
//
    float moving(float time);
    float docking(float time);
};


#endif //HWFINAL_SHUTTLE_H
