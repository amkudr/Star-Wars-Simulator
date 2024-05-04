#ifndef HWFINAL_TIEBOMBER_H
#define HWFINAL_TIEBOMBER_H


#include "Spaceship.h"

class TIEBomber: public Spaceship {

public:
    TIEBomber(string name, string pilot, float x, float y) : Spaceship(std::move(name), std::move(pilot), x, y) {}
private:
    int pUnit = 10;
    shared_ptr<SpaceStation> dest;
    int speed = 1000;



};


#endif //HWFINAL_TIEBOMBER_H
