#ifndef HWFINAL_MODEL_H
#define HWFINAL_MODEL_H

#include "memory"
#include "SpaceStation.h"
#include "View.h"
#include <vector>
#include "Shuttle.h"
#include "TIEBomber.h"
#include "StarDestroyer.h"
#include "Falcon.h"

using namespace std;

class Model {
public:
    static shared_ptr<Model> getInstance();
    void addStation(const string& name, float x, float y, int ContNum, int SupNum);
    void addShuttle(const string& name, const string& pilot, float x, float y);
    void addBomber(const string &name, const string &pilot, float x, float y);
    void addFalcon(const string &name, float x, float y);
    void addDestroyer(const string &name, const string& pilot, float x, float y);
//    int getShStatus(const string& name);
    void start_supply(const string& name, const string& sourSt, const string& destSt);
    void destination(const string& name, const string& destSt);
    void position(const string &name, float x, float y, float speed = 0);
    void course(const string &name, float angle, float speed = 0);
    void shoot(const string& name, float x, float y);
    void attack(const string& falconName, const string& shuttleName);
    void stop(const string& name);
    void go(); //Update all objects in one hour
    string view();
    string status();

private:
    Model();
    static shared_ptr<Model> instance;
    shared_ptr<vector<shared_ptr<SpaceStation>>> stations_ptr = make_shared<vector<shared_ptr<SpaceStation>>>();
    vector<shared_ptr<Shuttle>> shuttles;
    vector<shared_ptr<TIEBomber>> bombers;
    vector<shared_ptr<StarDestroyer>> destroyers;
    vector<shared_ptr<Falcon>> falcons;
    vector<pair<pair<float, float>, float>> rockets; // <(x,y), rest time to target>
    unique_ptr<View> viewObj;
    unique_ptr<SpaceStation> dest;
};


#endif //HWFINAL_MODEL_H
