#ifndef HWFINAL_CONTROLLER_H
#define HWFINAL_CONTROLLER_H

#include "Model.h"
#include "memory"
#include "string"

using namespace std;


class Controller {
public:
    Controller();

    static void run(int argc, char *argv[]);

private:
    static shared_ptr<Model> model;

    static void createWorld(int argc, char **argv);

    static void createObject();
    static void shipCommands(const string& name);

};


#endif //HWFINAL_CONTROLLER_H
