#ifndef HWFINAL_TIEBOMBER_H
#define HWFINAL_TIEBOMBER_H


#include <utility>

#include "Spaceship.h"

class TIEBomber : public Spaceship {

public:
    TIEBomber(string name, string pilot, float x, float y, shared_ptr<vector<shared_ptr<SpaceStation>>> stations_ptr) :
    Spaceship(std::move(name), std::move(pilot), x, y) { this->stations_ptr = std::move(stations_ptr); }

    float getSpeed() const override;

    string getClassName() const override;

    void destination(const shared_ptr<SpaceStation>& dest) override;

    void go(float restTime) override;

//    void position(float x, float y) override;

//    void course(float angle) override {};

    void findNewDest();

private:
    shared_ptr<SpaceStation> destSt;
    float speed = 1;
    shared_ptr<vector<shared_ptr<SpaceStation>>> stations_ptr;
    vector<shared_ptr<SpaceStation>> visitedSt; //vector of visited stations
};


#endif //HWFINAL_TIEBOMBER_H
