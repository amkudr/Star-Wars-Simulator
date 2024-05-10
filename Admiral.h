#ifndef HWFINAL_ADMIRAL_H
#define HWFINAL_ADMIRAL_H


#include "ImperialAgent.h"

class Admiral: public ImperialAgent {

public:
    explicit Admiral(string name) : ImperialAgent(std::move(name)) {}
    int getClass() override { return ADMIRAL; }

};


#endif //HWFINAL_ADMIRAL_H
