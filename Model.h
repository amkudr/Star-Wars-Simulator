#ifndef HWFINAL_MODEL_H
#define HWFINAL_MODEL_H

#include "memory"
#include "SpaceStation.h"
#include "View.h"
#include <vector>
#include "Shuttle.h"
#include "TIEBomber.h"

using namespace std;

class Model {
public:
    static shared_ptr<Model> getInstance();
    void addStation(const string& name, float x, float y, int ContNum, int SupNum);
    void addShuttle(const string& name, const string& pilot, float x, float y);
    void addBomber(const string &name, const string &pilot, float x, float y);
    int getShStatus(const string& name);
    void setSupply(const string& name, const string& sourSt, const string& destSt);
    void setDest(const string& name, const string& destSt);
    void setPos(const string& name, float x, float y);
    void setCourse(const string& name, float angle);
    void go(); //Update all objects in one hour
    string view();
    string status();

private:
    Model();
    static shared_ptr<Model> instance;
    shared_ptr<vector<shared_ptr<SpaceStation>>> stations_ptr = make_shared<vector<shared_ptr<SpaceStation>>>();
    vector<shared_ptr<Shuttle>> shuttles;
    vector<shared_ptr<TIEBomber>> bombers;
    unique_ptr<View> viewObj;
    unique_ptr<SpaceStation> dest;
};


#endif //HWFINAL_MODEL_H
