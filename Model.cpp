#include <iostream>
#include <sstream>
#include <algorithm>
#include "Model.h"

shared_ptr<Model> Model::instance = nullptr;


shared_ptr<Model> Model::getInstance() {
    if (!instance) {
        instance = shared_ptr<Model>(new Model());
    }
    return instance;
}

Model::Model() {
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
    if (checkIfAgentExist(pilot) != MIDSHIPMAN) throw invalid_argument("Agent does not exist! " + pilot);
    shuttles.emplace_back(make_shared<Shuttle>(name, pilot, x, y));
    viewObj->setObject(name, x, y);
}

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

    for (auto it = rockets.begin(); it != rockets.end();) { //Update rocket and get rocket that will explore now
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
        viewObj->setObject(destroyer->getName(), destroyer->getX(), destroyer->getY());
    }
    for (auto &falcon: falcons) { //Rocket attack
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
        falcon->go(1 - passTime);
        viewObj->setObject(falcon->getName(), falcon->getX(), falcon->getY());

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
    for (auto &falcon: falcons) {
        os << falcon->getFullStatus() << std::endl;
    }
    return os.str();
}

void Model::addBomber(const string &name, const string &pilot, float x, float y) {
    if (checkIfAgentExist(pilot) != COMMANDER) throw invalid_argument("Agent does not exist! " + pilot);
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

void Model::position(const string &name, float x, float y, float speed) {

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
            falcon->position(x, y, speed);
            return;
        }
    }
}

void Model::course(const string &name, float angle, float speed) {
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
    for (auto &falcon: falcons) {
        if (falcon->getName() == name) {
            falcon->course(angle, speed);
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

void Model::addDestroyer(const string &name, const string &pilot, float x, float y) {
    if (checkIfAgentExist(pilot) != ADMIRAL) throw invalid_argument("Admiral " + pilot + " does not exist");
    destroyers.emplace_back(make_shared<StarDestroyer>(name, pilot, x, y));
    viewObj->setObject(name, x, y);
}

void Model::attack(const string &falconName, const string &shuttleName) {
    /* Attack shuttle with falcon */
    //Check if exist
    shared_ptr<Falcon> falcon = nullptr;
    shared_ptr<Shuttle> shuttle = nullptr;
    for (auto &f: falcons) {
        if (f->getName() == falconName) {
            falcon = f;
        }
    }
    if (falcon == nullptr) return;
    for (auto &s: shuttles) {
        if (s->getName() == shuttleName) {
            shuttle = s;
        }
    }
    if (shuttle == nullptr) return;
    bool isSuccess = true; //Check if attack success
    // Check if less 100km
    float dist = falcon->findDist(shuttle->getX(), shuttle->getY());
    if (dist > 1) isSuccess = false;
    //Check if falcon have more pUnit
    if (falcon->getPUnit() < shuttle->getPUnit()) isSuccess = false;
    //Check if there are no bomber in radius 250 km
    if (isSuccess) {
        for (auto &b: bombers) {
            if (shuttle->findDist(b->getX(), b->getY()) < 2.5) isSuccess = false;
            if (!isSuccess) break;
        }
    }

    if (isSuccess) {
        shuttle->setPUnit(shuttle->getPUnit() - 1);
        shuttle->setCargo(0);
        shuttle->stop();
        if (falcon->getPUnit() < 20) falcon->setPUnit(falcon->getPUnit() + 1);
    } else {
        falcon->setPUnit(falcon->getPUnit() - 1);
        if (falcon->getPUnit() == 0) falcon->dead();
    }
    falcon->setX(shuttle->getX());
    falcon->setY(shuttle->getY());
    falcon->stop();
}

void Model::addImpSoldier(const string &name, int type) {
    if (name.size()>15) throw runtime_error("Name too long " + name);
    unique_ptr<ImperialFactory> impFactory_ptr;
    switch (type) {
        case MIDSHIPMAN:
            impFactory_ptr = unique_ptr<MidImperialFactory>(new MidImperialFactory());
            break;
        case COMMANDER:
            impFactory_ptr = unique_ptr<ComImperialFactory>(new ComImperialFactory());
            break;
        case ADMIRAL:
            impFactory_ptr = unique_ptr<AdmImperalFactory>(new AdmImperalFactory());
            break;

        default:
            throw runtime_error("Wrong type");

    }
    shared_ptr<ImperialAgent> impAgent = impFactory_ptr->createAgent(name);
    imperialAgents.emplace_back(impAgent);
}

int Model::checkIfAgentExist(const string &name) {
    for (auto &imperialAgent: imperialAgents) {
        if (imperialAgent->getName() == name) {
            return imperialAgent->getClass();
        }
    }
    return -1;
}

void Model::setDefaultView() {
    viewObj->setDefault();
}

void Model::size(int size) {
    /* change the size of the map */
    if (size < 7) throw invalid_argument("New map size is too small.");
    if (size > 30) throw invalid_argument("New map size is too big.");
    viewObj->setSize(size);

}

void Model::zoom(float scale) {
    if (scale<=0) throw invalid_argument("New map scale must be positive.");
    viewObj->setScale(scale);
}

void Model::pan(float x, float y) {
    viewObj->setPanX(x);
    viewObj->setPanY(y);
}

