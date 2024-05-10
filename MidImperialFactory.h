
#ifndef HWFINAL_MIDIMPERIALFACTORY_H
#define HWFINAL_MIDIMPERIALFACTORY_H


#include "ImperialFactory.h"
#include "Midshipman.h"

class MidImperialFactory : public ImperialFactory {
public:

    ImperialAgent * createAgent(string name) override {
        return new Midshipman(name);
    }

};

#endif //HWFINAL_MIDIMPERIALFACTORY_H
