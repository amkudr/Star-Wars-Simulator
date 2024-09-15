
#ifndef HWFINAL_MIDIMPERIALFACTORY_H
#define HWFINAL_MIDIMPERIALFACTORY_H


#include "ImperialFactory.h"
#include "Midshipman.h"

class MidImperialFactory : public ImperialFactory {
    /* This class is an abstract factory that creates a Midshipman object */
public:

    shared_ptr<ImperialAgent> createAgent(string name) override {
        return make_shared<Midshipman>(name);
    }

};

#endif //HWFINAL_MIDIMPERIALFACTORY_H
