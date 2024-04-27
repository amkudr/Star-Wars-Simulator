#ifndef HWFINAL_SHUTTLE_H
#define HWFINAL_SHUTTLE_H

#include "string"

using namespace std;

class Shuttle {
public:
    Shuttle(string name, string pilot, float x, float y) : name(std::move(name)), pilot(std::move(pilot)), x(x), y(y) {}

private:
    string name;
    string pilot;
    float x;
    float y;
};


#endif //HWFINAL_SHUTTLE_H
