#ifndef HWFINAL_CONTROLLER_H
#define HWFINAL_CONTROLLER_H

#include "Model.h"
#include "memory"
#include "string"

using namespace std;


class Controller {
    shared_ptr<Model> model;

public:
    void run(int argc, char *argv[]);

};


#endif //HWFINAL_CONTROLLER_H
