#include <iostream>
#include "Model.h"
#include "cmath"

shared_ptr<Model> Model::instance = nullptr;


shared_ptr<Model> Model::getInstance() {
    if (!instance) {
        instance = shared_ptr<Model>(new Model());
    }
    return instance;
}

Model::Model() {
    stations = vector<shared_ptr<SpaceStation>>();
    viewObj  = unique_ptr<View>(new View());
    dest = unique_ptr<SpaceStation>(new SpaceStation("DS", 40, 10, 100000, 0));
    addStation("DS", 40, 10, 100000, 0);
}

void Model::addStation(const string& name, float x, float y, int ContNum, int SupNum) {
    stations.emplace_back(make_shared<SpaceStation>(name, x, y, ContNum, SupNum));

    viewObj->setObject(name, static_cast<int>(round(x)), static_cast<int>(round(y)));
}

string Model::view() {
    return viewObj->show();
}

void Model::addShuttle(const string& name, const string& pilot, float x, float y) {
    shuttles.emplace_back(make_shared<Shuttle>(name, pilot, x, y));
//    viewObj->setObject(name, static_cast<int>(round(x)), static_cast<int>(round(y)));

}

int Model::getShStatus(const string &name) {
    for (auto &shuttle : shuttles) {
        if (shuttle->getName() == name) {
            return shuttle->getStatus();
        }
    }
    return NOTEXIST;
}

void Model::setSupply(const string &name, const string &sourSt, const string &destSt) {
    shared_ptr<SpaceStation> sourStPtr = nullptr;
    shared_ptr<SpaceStation> destStPtr = nullptr;
    for (auto &shuttle : shuttles) {
        if (shuttle->getName() == name) {
            for (auto &station : stations) {
                if (station->getName() == sourSt) {
                    sourStPtr = station;
                }
                else if (station->getName() == destSt) {
                    destStPtr = station;
                }
            }
            if(sourStPtr != nullptr && destStPtr != nullptr){
                shuttle->setRoute(sourStPtr, destStPtr);
                return;
            }
        }
    }
}

void Model::go() {
    for(auto &shuttle : shuttles) {
        shuttle->go();
        viewObj->setObject(shuttle->getName(), static_cast<int>(round(shuttle->getX())), static_cast<int>(round(shuttle->getY())));
//        std::cout << shuttle->getName() << "X = " << shuttle->getX()<<" Y = " << shuttle->getY() << std::endl;
    }
}

