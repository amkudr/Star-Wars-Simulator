#ifndef HWFINAL_MODEL_H
#define HWFINAL_MODEL_H

#include "memory"
#include "SpaceStation.h"
#include "View.h"
#include <vector>
#include "Shuttle.h"

using namespace std;

class Model {
public:
    static shared_ptr<Model> getInstance();
    void addStation(string name, float x, float y, int ContNum, int SupNum);
    void addShuttle(const string& name, const string& pilot, float x, float y);
    string view();

private:
    Model();
    static shared_ptr<Model> instance;
    vector<shared_ptr<SpaceStation>> stations;
    vector<shared_ptr<Shuttle>> shuttles;
    unique_ptr<View> viewObj;
    unique_ptr<SpaceStation> dest;
};


#endif //HWFINAL_MODEL_H
