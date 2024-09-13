#ifndef HWFINAL_ADMIMPERALFACTORY_H
#define HWFINAL_ADMIMPERALFACTORY_H
#include "Admiral.h"
#include "ImperialFactory.h"

class AdmImperalFactory: public ImperialFactory {
    shared_ptr<ImperialAgent> createAgent(string name) override {
        return make_shared<Admiral>(name);
    }
};


#endif //HWFINAL_ADMIMPERALFACTORY_H
