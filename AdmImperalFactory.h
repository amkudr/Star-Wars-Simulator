#ifndef HWFINAL_ADMIMPERALFACTORY_H
#define HWFINAL_ADMIMPERALFACTORY_H
#include "Admiral.h"
#include "ImperialFactory.h"

class AdmImperalFactory: public ImperialFactory {
    /* This class is an abstract factory that creates an Admiral object */
    shared_ptr<ImperialAgent> createAgent(string name) override {
        return make_shared<Admiral>(name);
    }
};


#endif //HWFINAL_ADMIMPERALFACTORY_H
