#include <iostream>
#include <sstream>
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
//        stations_ptr = make_shared<vector<shared_ptr<SpaceStation>>()>;
        viewObj  = unique_ptr<View>(new View());
        dest = unique_ptr<SpaceStation>(new SpaceStation("DS", 40, 10, 100000, 0));
        addStation("DS", 40, 10, 100000, 0);
    }

void Model::addStation(const string& name, float x, float y, int ContNum, int SupNum) {
    stations_ptr->emplace_back(make_shared<SpaceStation>(name, x, y, ContNum, SupNum));

    viewObj->setObject(name, static_cast<int>(round(x)), static_cast<int>(round(y)));
}

string Model::view() {
    return viewObj->show();
}

void Model::addShuttle(const string& name, const string& pilot, float x, float y) {
    shuttles.emplace_back(make_shared<Shuttle>(name, pilot, x, y));
    viewObj->setObject(name, static_cast<int>(round(x)), static_cast<int>(round(y)));
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
            for (auto &station : *stations_ptr) {
                if (station->getName() == sourSt) {
                    sourStPtr = station;
                }
                else if (station->getName() == destSt) {
                    destStPtr = station;
                }
            }
            if(sourStPtr != nullptr && destStPtr != nullptr){
                shuttle->start_supply(sourStPtr, destStPtr);
                return;
            }
        }
    }
}

void Model::go() {
    for(auto &shuttle : shuttles) {
        shuttle->go(1);
        viewObj->setObject(shuttle->getName(), static_cast<int>(round(shuttle->getX())), static_cast<int>(round(shuttle->getY())));
//        std::cout << shuttle->getName() << "X = " << shuttle->getX()<<" Y = " << shuttle->getY() << std::endl;
    }
    for(auto &bomber : bombers) {
        bomber->go(1);
        viewObj->setObject(bomber->getName(), static_cast<int>(round(bomber->getX())), static_cast<int>(round(bomber->getY())));
    }
    for(auto &station : *stations_ptr) {
        station->go();
    }
}

string Model::status() {
    ostringstream os;
    for(auto &station : *stations_ptr) {
        os<<station->getFullStatus()<<std::endl;
    }

    for(auto &bomber : bombers) {
        os<<bomber->getFullStatus()<<std::endl;
    }
    for(auto &shuttle : shuttles) {
        os<<shuttle->getFullStatus()<<std::endl;
    }
    return os.str();
}

void Model::addBomber(const string &name, const string &pilot, float x, float y) {
    bombers.emplace_back(make_shared<TIEBomber>(name, pilot, x, y, stations_ptr));
    viewObj->setObject(name, static_cast<int>(round(x)), static_cast<int>(round(y)));
}

void Model::setDest(const string &name, const string &destSt) {

    for (auto &bomber : bombers) {
        if (bomber->getName() == name) {
            shared_ptr<SpaceStation> destStPtr = nullptr;
            for (auto &station : *stations_ptr) {
                if (station->getName() == destSt) {
                    destStPtr = station;
                    break;
                }
            }
            if (destStPtr != nullptr) {
                bomber->destination(destStPtr);
                return;
            }
        }
    }

}

