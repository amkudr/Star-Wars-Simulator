
#ifndef HWFINAL_COMIMPERALFACTORY_H
#define HWFINAL_COMIMPERALFACTORY_H
#include "Commander.h"
#include "ImperialFactory.h"

class ComImperialFactory : public ImperialFactory {
    /* This class is an abstract factory that creates a Commander object */
    shared_ptr<ImperialAgent> createAgent(string name) override {
        return make_shared<Commander>(name);
    }
};
#endif //HWFINAL_COMIMPERALFACTORY_H
