#ifndef HWFINAL_COMMANDER_H
#define HWFINAL_COMMANDER_H


#include "ImperialAgent.h"

class Commander: public ImperialAgent {

public:
    explicit Commander(string name) : ImperialAgent(std::move(name)) {}
    int getClass() override { return COMMANDER; }

};


#endif //HWFINAL_COMMANDER_H
