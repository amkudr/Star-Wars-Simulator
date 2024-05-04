
#ifndef HWFINAL_MIDIMPERIALFACTORY_H
#define HWFINAL_MIDIMPERIALFACTORY_H


#include "ImperialFactory.h"
#include "Midshipman.h"
#include "Spaceship.h"

class MidImperialFactory : public ImperialFactory {
    ImperialAgent *createAgent(const string &name) {
        return new Midshipman(name);
    }

    Spaceship *createSpaceShip(const string &name, const string &pilot, float x, float y) {
        return new Spaceship(name, pilot, x, y);
    }


};


#endif //HWFINAL_MIDIMPERIALFACTORY_H
