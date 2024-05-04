#include <sstream>
#include <iomanip>
#include "SpaceStation.h"

const string &SpaceStation::getName() const {
    return name;
}

float SpaceStation::getX() const {
    return x;
}

float SpaceStation::getY() const {
    return y;
}

int SpaceStation::getContNum() const {
    return ContNum;
}

int SpaceStation::getSupNum() const {
    return SupNum;
}

void SpaceStation::setX(float x_) {
    SpaceStation::x = x_;
}

void SpaceStation::setY(float y_) {
    SpaceStation::y = y_;
}

void SpaceStation::setContNum(int contNum) {
    ContNum = contNum;
}

void SpaceStation::go() {
    ContNum = ContNum + SupNum;
}

string SpaceStation::getFullStatus() const {
    ostringstream os;
    if (getName() == "DS") {
        os << "fortress ";
    } else {
        os << "station ";
    }
    os << name << " at position (" << std::fixed << std::setprecision(2)
       << x << "," << y << "), Inventory " << ContNum;

    return os.str();

}
