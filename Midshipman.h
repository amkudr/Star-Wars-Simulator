#ifndef HWFINAL_MIDSHIPMAN_H
#define HWFINAL_MIDSHIPMAN_H


#include <utility>

#include "ImperialAgent.h"

class Midshipman : public ImperialAgent {

public:
    explicit Midshipman(string name) : ImperialAgent(std::move(name)) { (void)name;}
    int getClass() override { return MIDSHIPMAN; }
};


#endif //HWFINAL_MIDSHIPMAN_H
