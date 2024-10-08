#ifndef HWFINAL_SHUTTLE_H
#define HWFINAL_SHUTTLE_H

#include <utility>
#include "Spaceship.h"

using namespace std;

class Shuttle : public Spaceship {
public:
    Shuttle(string name, string pilot, float x, float y) : Spaceship(std::move(name), std::move(pilot), x, y) {};

    void go(float restTime) override;

    void start_supply(const shared_ptr<SpaceStation> &sourSt_, const shared_ptr<SpaceStation> &ds_);

    string getClassName() const override;

    float getSpeed() const override;

    int getPUnit() const override;

    void setPUnit(int pUnit_);

    void setCargo(int cargo_);


private:
    int pUnit = 10;
    float speed = 0.5;
    int cargo = 0;
    float leftTime = -1;

    float supplying(float time);

    void destination(const shared_ptr<SpaceStation> &dest) override {};

    void course(float angle) override {};

    void position(float x, float y) override {};
};


#endif //HWFINAL_SHUTTLE_H
