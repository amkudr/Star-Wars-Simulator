#include <iostream>
#include "Controller.h"
#include "fstream"
#include <sstream>

shared_ptr<Model> Controller::model = nullptr;

void Controller::createWorld(int argc, char **argv) {
    if (argc != 2) {
        throw invalid_argument("Wrong number of arguments!");
    }
    ifstream file(argv[1]);
    if (!file.is_open()) {
        throw invalid_argument("File not found!");
    }
    //Create stations
    string line, name, type;
    char comma;
    float x, y;
    int ContNum = -1, SupNum = -1;
    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, type, ',');
        iss >> ws;
        getline(iss, name, ',');
        iss >> comma >> x >> comma >> y >> comma >> comma >> ContNum >> comma >> SupNum;
        if (ContNum < 0 || SupNum < 0 || name.empty() || !iss.eof()) {
            cerr << "Wrong input for line:" + line << endl;
        } else model->addStation(name, x, y, ContNum, SupNum);
    }


}

void Controller::run(int argc, char **argv) {
    try {
        createWorld(argc, argv);
    }
    catch (invalid_argument &e) {
        cerr << e.what() << endl;
        return;
    }
    string command;
    int time = 0;
    while (true) {
        cout << "Time: " << time << " Enter command :";
        cin >> command;
        try {
            if (command == "exit") {
                break;
            } else if (command == "create") {
                createObject();
            } else if (command == "go") {
                model->go();
                time++;
            } else if (command == "status") {
                cout << model->status();
            } else if (command == "default")
                model->setDefaultView();
            else if (command == "size") {
                int size;
                cin >> size;
                if (cin.fail()) {
                    cin.clear();
                    throw invalid_argument("Expected an Integer.");
                }

                model->size(size);

            } else if (command == "show") {
                cout << model->view();
            } else if (command == "scale") {
                float scale;
                cin >> scale;
                if (cin.fail()) {
                    cin.clear();
                    throw invalid_argument("Expected a double.");
                }
                model->zoom(scale);
            } else if (command == "pan") {
                float x, y;
                cin >> x >> y;
                if (cin.fail()) {
                    cin.clear();
                    throw invalid_argument("Expected a double.");
                }
                model->pan(x, y);
            } else {
                shipCommands(command);
            }
        }
        catch (invalid_argument &e) {
            cerr << e.what() << endl;
        }
    }

}

Controller::Controller() {
    model = Model::getInstance();
}

void Controller::createObject() {
    string type, pilot;
    cin >> type;
    if (type == "admiral") {
        cin >> pilot;
        model->addImpSoldier(pilot, ADMIRAL);
    } else if (type == "commander") {
        cin >> pilot;
        model->addImpSoldier(pilot, COMMANDER);
    } else if (type == "midshipman") {
        cin >> pilot;
        model->addImpSoldier(pilot, MIDSHIPMAN);
    } else {
        string line;
        getline(cin, line);
        string word;
        vector<string> inputVec;
        istringstream iss(line);
        while (iss >> word) {
            inputVec.push_back(word);
        }
        if (inputVec.size() == 4) {
            if (inputVec[0].size() > 15) throw invalid_argument("Too long name " + inputVec[0]);
            float x = stof(inputVec[2].substr(1));
            float y = stof(inputVec[3].substr(0, inputVec[2].size() - 1));
            if (type == "shuttle") model->addShuttle(inputVec[0], inputVec[1], x, y);
            else if (type == "destroyer") model->addDestroyer(inputVec[0], inputVec[1], x, y);
            else if (type == "bomber") model->addBomber(inputVec[0], inputVec[1], x, y);
            else throw invalid_argument("Wrong type " + type);
        } else if (inputVec.size() == 3) {
            if (inputVec[0].size() > 15) throw invalid_argument("Too long name " + inputVec[0]);
            float x = stof(inputVec[1].substr(1));
            float y = stof(inputVec[2].substr(0, inputVec[2].size() - 1));
            if (type == "falcon") model->addFalcon(inputVec[0], x, y);
            else throw invalid_argument("Wrong type " + type);
        } else throw invalid_argument("Not enough arguments");
    }
}

void Controller::shipCommands(const string &name) {
    string line;
    getline(cin, line);
    string word;
    vector<string> inputVec;
    istringstream iss(line);
    while (iss >> word) {
        inputVec.push_back(word);
    }
    if (inputVec.size() == 1 && inputVec[0] == "stop") model->stop(name);
    else if (inputVec.size() == 2) {
        if (inputVec[0] == "attack") model->attack(name, inputVec[1]);
        else if (inputVec[0] == "course") {
            float angle = stof(inputVec[1]);
            model->course(name, angle);
        } else if (inputVec[0] == "destination") {
            model->destination(name, inputVec[1]);
        }
    } else if (inputVec.size() == 3) {
        if (inputVec[0] == "shoot") {
            float x = stof(inputVec[1]);
            float y = stof(inputVec[2]);
            model->shoot(name, x, y);
        } else if (inputVec[0] == "start_supply") model->start_supply(name, inputVec[1], inputVec[2]);
        else if (inputVec[0] == "position") {
            float x = stof(inputVec[1]);
            float y = stof(inputVec[2]);
            model->position(name, x, y);
        } else if (inputVec[0] == "course") {
            float angle = stof(inputVec[1]);
            float speed = stof(inputVec[2]);
            model->course(name, angle, speed);
        }
    } else if (inputVec.size() == 4 && inputVec[0] == "position") {
        float x = stof(inputVec[1]);
        float y = stof(inputVec[2]);
        float speed = stof(inputVec[3]);
        model->position(name, x, y, speed);
    } else throw invalid_argument("Wrong command for " + name);

}

