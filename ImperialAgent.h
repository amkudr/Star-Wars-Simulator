#ifndef HWFINAL_IMPERIALAGENT_H
#define HWFINAL_IMPERIALAGENT_H
#include <utility>

#include "string"

enum {MIDSHIPMAN, COMMANDER, ADMIRAL};

using namespace std;
class ImperialAgent {
public:
    explicit ImperialAgent(string  name) : name(std::move(name)) {}
    virtual int getClass() = 0;

private:
    string name;

};


#endif //HWFINAL_IMPERIALAGENT_H
