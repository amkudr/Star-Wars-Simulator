#include <iostream>
#include <sstream>
#include <algorithm>
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
    viewObj = unique_ptr<View>(new View());
    dest = unique_ptr<SpaceStation>(new SpaceStation("DS", 40, 10, 100000, 0));
    addStation("DS", 40, 10, 100000, 0);
}

void Model::addStation(const string &name, float x, float y, int ContNum, int SupNum) {
    stations_ptr->emplace_back(make_shared<SpaceStation>(name, x, y, ContNum, SupNum));

    viewObj->setObject(name, x, y);
}

string Model::view() {
    return viewObj->show();
}

void Model::addShuttle(const string &name, const string &pilot, float x, float y) {
    shuttles.emplace_back(make_shared<Shuttle>(name, pilot, x, y));
    viewObj->setObject(name, x, y);
}

//int Model::getShStatus(const string &name) {
//    for (auto &shuttle : shuttles) {
//        if (shuttle->getName() == name) {
//            return shuttle->getStatus();
//        }
//    }
//    return NOTEXIST;
//}

void Model::start_supply(const string &name, const string &sourSt, const string &destSt) {
    shared_ptr<SpaceStation> sourStPtr = nullptr;
    shared_ptr<SpaceStation> destStPtr = nullptr;
    for (auto &shuttle: shuttles) {
        if (shuttle->getName() == name) {
            for (auto &station: *stations_ptr) {
                if (station->getName() == sourSt) {
                    sourStPtr = station;
                } else if (station->getName() == destSt) {
                    destStPtr = station;
                }
            }
            if (sourStPtr != nullptr && destStPtr != nullptr) {
                shuttle->start_supply(sourStPtr, destStPtr);
                return;
            }
        }
    }
}

void Model::go() {
    vector<pair<pair<float, float>, float>> fresh_rockets;

    for (auto it = rockets.begin(); it != rockets.end();) {
        if (it->second <= 1) {
            fresh_rockets.push_back(*it);
            it = rockets.erase(it);
        } else {
            it->second -= 1;
            ++it;
        }
    }

    sort(fresh_rockets.begin(), fresh_rockets.end(), //sort rockets by rest time
         [](const std::pair<std::pair<float, float>, float> &left,
            const std::pair<std::pair<float, float>, float> &right) {
             return left.second < right.second;
         });

    for (auto &shuttle: shuttles) {
        shuttle->go(1);
        viewObj->setObject(shuttle->getName(), shuttle->getX(), shuttle->getY());
//        std::cout << shuttle->getName() << "X = " << shuttle->getX()<<" Y = " << shuttle->getY() << std::endl;
    }
    for (auto &bomber: bombers) {
        bomber->go(1);
        viewObj->setObject(bomber->getName(), bomber->getX(), bomber->getY());
    }
    for (auto &station: *stations_ptr) {
        station->go();
    }
    for (auto &destroyer: destroyers) {
        destroyer->go(1);
    }
    for (auto &falcon: falcons) {
        float passTime = 0;
        float rocket_time;
        for (auto &rocket: fresh_rockets) {
            rocket_time = rocket.second;
            falcon->go(rocket_time - passTime);
            passTime = rocket_time;
            if (falcon->getX() == rocket.first.first && falcon->getY() == rocket.first.second) {
                falcon->dead();
                break;
            }
        }
        falcon->go(1-passTime);
    }
}

string Model::status() {
    ostringstream os;
    for (auto &station: *stations_ptr) {
        os << station->getFullStatus() << std::endl;
    }
    for (auto &bomber: bombers) {
        os << bomber->getFullStatus() << std::endl;
    }
    for (auto &shuttle: shuttles) {
        os << shuttle->getFullStatus() << std::endl;
    }
    for (auto &destroyer: destroyers) {
        os << destroyer->getFullStatus() << std::endl;
    }
    for(auto &falcon: falcons) {
        os << falcon->getFullStatus() << std::endl;
    }
    return os.str();
}

void Model::addBomber(const string &name, const string &pilot, float x, float y) {
    bombers.emplace_back(make_shared<TIEBomber>(name, pilot, x, y, stations_ptr));
    viewObj->setObject(name, x, y);
}

void Model::destination(const string &name, const string &destSt) {
    shared_ptr<SpaceStation> destStPtr = nullptr;
    for (auto &station: *stations_ptr) {
        if (station->getName() == destSt) {
            destStPtr = station;
            break;
        }
    }
    if (destStPtr == nullptr) {
        return;
    }
    for (auto &bomber: bombers) {
        if (bomber->getName() == name) {
            bomber->destination(destStPtr);
            return;
        }
    }
    for (auto &destroyer: destroyers) {
        if (destroyer->getName() == name) {
            destroyer->destination(destStPtr);
            return;
        }
    }

}

void Model::position(const string &name, float x, float y) {

    for (auto &bomber: bombers) {
        if (bomber->getName() == name) {
            bomber->position(x, y);
            return;
        }
    }
    for (auto &destroyer: destroyers) {
        if (destroyer->getName() == name) {
            destroyer->position(x, y);
            return;
        }
    }
    for (auto &falcon: falcons) {
        if (falcon->getName() == name) {
            falcon->position(x, y, 7);
            return;
        }
    }
}

void Model::course(const string &name, float angle) {
    for (auto &bomber: bombers) {
        if (bomber->getName() == name) {
            bomber->course(angle);
            return;
        }
    }
    for (auto &destroyer: destroyers) {
        if (destroyer->getName() == name) {
            destroyer->course(angle);
            return;
        }
    }

}

void Model::shoot(const string &name, float x, float y) {
    float rest_time; //Rest time to target
    for (auto &destroyer: destroyers) {
        if (destroyer->getName() == name) {
            rest_time = destroyer->shoot(x, y);
            rockets.emplace_back(make_pair(x, y), rest_time);

        }
    }
}

void Model::stop(const string &name) {
    for (auto &bomber: bombers) {
        if (bomber->getName() == name) {
            bomber->stop();
            return;
        }
    }
    for (auto &shuttle: shuttles) {
        if (shuttle->getName() == name) {
            shuttle->stop();
            return;
        }
    }
    for (auto &destroyer: destroyers) {
        if (destroyer->getName() == name) {
            destroyer->stop();
            return;
        }
    }
    for (auto &falcon: falcons) {
        if (falcon->getName() == name) {
            falcon->stop();
            return;
        }
    }

}

void Model::addFalcon(const string &name, float x, float y) {
    falcons.emplace_back(make_shared<Falcon>(name, x, y));
    viewObj->setObject(name, x, y);

}

void Model::addDestroyer(const string &name, const string& pilot, float x, float y) {
    destroyers.emplace_back(make_shared<StarDestroyer>(name, pilot, x, y));
    viewObj->setObject(name, x, y);
}

