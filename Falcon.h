#ifndef HWFINAL_FALCON_H
#define HWFINAL_FALCON_H


#include "Spaceship.h"
#include "Shuttle.h"

class Falcon: public Spaceship {

public:
    Falcon(const string& name, float x, float y) :
    Spaceship(name, "", x, y) {}

    void course(float angle_, float speed_);

    void position(float x_, float y_, float speed_);

//    bool attack(shared_ptr<Shuttle> shuttle);

//    void go(float restTime, float targetX, float targetY, float targTime);
    float getSpeed() const override;

    string getClassName() const override;

    int getPUnit() const;

    void setPUnit(int pUnit_);

    void setSpeed(float speed_) ;

    void dead();


private:
    float speed = 3;
    int pUnit = 5;
};


#endif //HWFINAL_FALCON_H
