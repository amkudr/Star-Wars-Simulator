#include "View.h"
#include "sstream"
#include <iomanip>
#include "cmath"


View::View() {
    objects = map<string, pair<float, float>>();
}

string View::show() { //TODO Need to update to float!

    //create empty field
    stringstream ss;
    float scaleSizeY = float(size - 1) * scale + panY;
    float yInd = scaleSizeY;
    float xInd = panX;
    for (int i = size - 1; i >= 0; i--) {
        if ( static_cast<int>(round(yInd - panY)) % static_cast<int>(round(3 * scale)) == 0) {
            ss << std::setw(3) << std::left << round(yInd);
        } else ss << "   ";
        yInd -= scale;
        for (int j = 0; j < size; j++) {
            ss << ". ";
        }
        ss << endl;
    }

    for (int i = size - 1; i >= 0; i--) {
        if (static_cast<int>(round(xInd - panX)) % static_cast<int>(round(3 * scale)) == 0) {
            ss << std::setw(4) << std::right << xInd;
        } else ss << " ";
        xInd += scale;
    }
    ss<<endl;

    // Add objects to field
    string out = ss.str(); //TODO Need to split to objects and shuttle
    for (const auto &obj: objects) {
        float x = obj.second.first;
        float y = obj.second.second;

//        int x = static_cast<int>(round(obj.second.first)); //X of object
//        int y = static_cast<int>(round(obj.second.second)); //Y of object

        if (x < xInd && y <= scaleSizeY && x >= panX && y >= panY) {

            float lineSize = float(size) * 2 + 4;
            float ind = lineSize * float(size - 1) -
                      floor((y - panY) / scale) * lineSize +
                      floor((x - panX) / scale) * 2 + 3;

            out.replace(static_cast<std::string::size_type>(ind), 2, obj.first.substr(0,2)); //Put subname of object to map
        }
    }
    //Print title
    std::ostringstream titleStream;
    titleStream << "Display size: " << size << ", scale: " << std::fixed << std::setprecision(2) << scale <<
                ", origin: (" << std::fixed << std::setprecision(2) << panX << ", " << panY << ")\n";
    std::string title = titleStream.str();
    return title + out;
}

void View::setObject(const string &name, float x, float y) {
    objects[name] = make_pair(x, y);
}
