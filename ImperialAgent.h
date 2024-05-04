#ifndef HWFINAL_IMPERIALAGENT_H
#define HWFINAL_IMPERIALAGENT_H
#include <utility>

#include "string"
using namespace std;
class ImperialAgent {
public:
    ImperialAgent(string  name) : name(std::move(name)) {}
private:
    string name;

};


#endif //HWFINAL_IMPERIALAGENT_H
