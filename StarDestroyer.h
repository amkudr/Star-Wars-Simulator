#ifndef HWFINAL_STARDESTROYER_H
#define HWFINAL_STARDESTROYER_H


#include "Spaceship.h"

class StarDestroyer: public Spaceship {

public:
    StarDestroyer(string name, string pilot, float x, float y): Spaceship(std::move(name), std::move(pilot), x, y) {}
    float getSpeed() const override;
    string getClassName() const override;
    float shoot(float p_x, float p_y);
private:
    float speed = 2;
};


#endif //HWFINAL_STARDESTROYER_H
