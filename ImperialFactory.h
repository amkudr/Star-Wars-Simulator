#ifndef HWFINAL_IMPERIALFACTORY_H
#define HWFINAL_IMPERIALFACTORY_H

#include <memory>
#include "ImperialAgent.h"
#include "string"
using namespace std;
class ImperialFactory {
    virtual ImperialAgent* createAgent(string name) = 0;
};


#endif //HWFINAL_IMPERIALFACTORY_H
