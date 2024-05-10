
#ifndef HWFINAL_COMIMPERALFACTORY_H
#define HWFINAL_COMIMPERALFACTORY_H
#include "Commander.h"
#include "ImperialFactory.h"

class ComImperialFactory : public ImperialFactory {
    ImperialAgent * createAgent(string name) override {
        return new Commander(name);
    }
}
#endif //HWFINAL_COMIMPERALFACTORY_H
