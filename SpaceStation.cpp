#include <sstream>
#include <iomanip>
#include <cmath>

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

float SpaceStation::findDist(float p_x, float p_y) const {
    return float(sqrt(pow(p_x - x, 2) + pow(p_y - y, 2)));
}
