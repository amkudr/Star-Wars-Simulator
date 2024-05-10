#ifndef HWFINAL_ADMIMPERALFACTORY_H
#define HWFINAL_ADMIMPERALFACTORY_H
#include "Admiral.h"
#include "ImperialFactory.h"

class AdmImperalFactory: public ImperialFactory {

    ImperialAgent * createAgent(string name) override {
        return new Admiral(name);
    }
};


#endif //HWFINAL_ADMIMPERALFACTORY_H
