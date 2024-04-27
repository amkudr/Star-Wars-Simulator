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

void Model::addStation(string name, float x, float y, int ContNum, int SupNum) {
    stations.emplace_back(make_shared<SpaceStation>(name, x, y, ContNum, SupNum));
    string subname;
    if (name.length() < 2) {
        subname = " " + name;
    } else {
        subname = name.substr(0, 2);
    }
    viewObj->setObject(subname, static_cast<int>(round(x)), static_cast<int>(round(y)));
}

string Model::view() {
    return viewObj->show();
}

