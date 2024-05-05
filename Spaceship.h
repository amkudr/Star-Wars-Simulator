#ifndef HWFINAL_SPACESHIP_H
#define HWFINAL_SPACESHIP_H

#include "string"
#include <memory>
#include <queue>
#include "SpaceStation.h"

enum Status {
    STOPPED,
    DOCKED,
    DEAD,
    MOVING,
    SUPPLYING,
    NOTEXIST
};

using namespace std;

class Spaceship {

public:
    Spaceship(string name, string pilot, float x, float y) : name(std::move(name)), pilot(std::move(pilot)), x(x),
                                                             y(y) {}

    const string &getName() const;

    int getStatus() const;

    float getX() const;

    float getY() const;

    float getAngle() const;

    bool isCourse() const;


    virtual string getClassName() const;

    virtual float getSpeed() const;

    void setStatus(int status_);

    string getFullStatus() const;

    virtual void go(float restTime) = 0;

    virtual void destination(const shared_ptr<SpaceStation>& dest);

    virtual void course(float angle_);

    virtual void position(float x_, float y_);

    float findDist(float p_x, float p_y) const;

    float moving(float time);

protected:
    string name;
    string pilot;
    float x;
    float y;
    int status = STOPPED;
    float speed = 0;
    float angle = 0;
    bool isCour = false;
    queue<pair<pair<float, float>, shared_ptr<SpaceStation>>> routeQue; // queue of pair coordinates + ptr


};


#endif //HWFINAL_SPACESHIP_H
