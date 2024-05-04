#ifndef HWFINAL_IMPERIALFACTORY_H
#define HWFINAL_IMPERIALFACTORY_H
#include "ImperialAgent.h"
#include "Spaceship.h"
#include "string"
using namespace std;
class ImperialFactory {
    virtual ImperialAgent* createAgent(const string& name) = 0;
    virtual Spaceship* createSpaceShip(const string& name, const string& pilot, float x, float y) = 0;
};


#endif //HWFINAL_IMPERIALFACTORY_H
