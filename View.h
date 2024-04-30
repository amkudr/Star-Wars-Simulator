#ifndef HWFINAL_VIEW_H
#define HWFINAL_VIEW_H

#include "string"
#include "map"


using namespace std;


class View {
public:
    View();
    string show();
    void setObject(const string& name, int x, int y);
//    void setZoom(int scale);
//    void setPan(float x, float y);
//

private:
    string field;
    map<string, pair<float, float>> objects;
    int size = 25;
    float scale = 2;
    float panX = 0;
    float panY = 0;
};


#endif //HWFINAL_VIEW_H
