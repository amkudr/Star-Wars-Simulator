//

#include "View.h"
#include "sstream"
#include <iomanip>
#include "cmath"


View::View() {
    objects = map<string, pair<float, float>>();
}

string View::show() { //Need to update to float!

    //create empty field
    stringstream ss;
    int scaleSizeY = (size - 1) * scale + panY;
    int yInd = scaleSizeY;
    int xInd = panX;
    for (int i = size - 1; i >= 0; i--) {
        if ((yInd - panY) % (3 * scale) == 0) {
            ss << std::setw(3) << std::left << yInd;
        } else ss << "   ";
        yInd -= scale;
        for (int j = 0; j < size; j++) {
            ss << ". ";
        }
        ss << endl;
    }

    for (int i = size - 1; i >= 0; i--) {
        if ((xInd - panX) % (3 * scale) == 0) {
            ss << std::setw(4) << std::right << xInd;
        } else ss << " ";
        xInd += scale;
    }
    // Add objects to field
    string out = ss.str();
    for (const auto &obj: objects) {

        int x = static_cast<int>(round(obj.second.first)); //X of object
        int y = static_cast<int>(round(obj.second.second)); //Y of object

        if (x < xInd && y <= scaleSizeY && x >= panX && y >= panY) {
            int lineSize = size * 2 + 4;
            int ind = lineSize * (size - 1) -
                      (y - panY) / scale * lineSize +
                      (x - panX) / scale * 2 + 3;
            out.replace(ind, 2, obj.first);
        }
    }
    //Print title
    std::ostringstream titleStream;
    titleStream << "Display size: " << size << ", scale: " << std::fixed << std::setprecision(2) << scale <<
                ", origin: (" << std::fixed << std::setprecision(2) << panX << ", " << panY << ")\n";
    std::string title = titleStream.str();
    return title + out;
}

void View::setObject(const string &name, int x, int y) {
    objects[name] = make_pair(x, y);
}
