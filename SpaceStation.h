#ifndef HWFINAL_SPACESTATION_H
#define HWFINAL_SPACESTATION_H


#include <utility>

#include "string"

using namespace std;

class SpaceStation {
public:
    SpaceStation(string name, float x, float y, int ContNum, int SupNum) : name(std::move(name)), x(x), y(y),
                                                                           ContNum(ContNum), SupNum(SupNum) {}
    const string &getName() const;

    float getX() const;

    float getY() const;

    int getContNum() const;

    void go();

    int getSupNum() const;

    void setContNum(int contNum);

    float findDist(float p_x, float p_y) const;


    string getFullStatus() const;

private:
    string name;
    float x;
    float y;
    int ContNum; //Number of containers
    const int SupNum; //Number of supplies
};


#endif //HWFINAL_SPACESTATION_H
