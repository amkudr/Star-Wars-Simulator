
#ifndef HWFINAL_MIDIMPERIALFACTORY_H
#define HWFINAL_MIDIMPERIALFACTORY_H


#include "ImperialFactory.h"
#include "Midshipman.h"

class MidImperialFactory : public ImperialFactory {
public:

    shared_ptr<ImperialAgent> createAgent(string name) override {
        return make_shared<Midshipman>(name);
    }

};

#endif //HWFINAL_MIDIMPERIALFACTORY_H
