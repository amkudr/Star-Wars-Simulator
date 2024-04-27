#include <iostream>
#include "Controller.h"
#include "fstream"
#include <sstream>

void Controller::run(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Wrong number of arguments!" << endl;
        return;
    }
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "File not found!" << endl;
        return;
    } else {
        //Create stations
        model = Model::getInstance();
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
    cout<<model->view();
}
