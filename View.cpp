#include "View.h"
#include "sstream"
#include <iomanip>
#include "cmath"

const float EPSILON = 0.0001;

View::View() {
    objects = map<string, pair<float, float>>();
}

string View::show() {

    //create empty field
    stringstream ss;
    float scaleSizeY = float(size - 1) * scale + panY;
    float yInd = scaleSizeY;
    float xInd = panX;
    for (int i = size - 1; i >= 0; i--) {
        if (fabs((yInd - panY) - round((yInd - panY) / (3 * scale)) * (3 * scale)) < EPSILON) {
            if (fabs(yInd - round(yInd)) < 0.0001) { //if yInd is an integer
                ss << std::setw(3) << std::left << static_cast<int>(yInd);
            } else {
                string s = to_string(yInd);
                if (s.size() > 3) s = s.substr(0, 3);
                ss << std::setw(3) << std::fixed << std::left << s;
            }
        } else ss << "   ";
        yInd -= scale;
        for (int j = 0; j < size; j++) {
            ss << ". ";
        }
        ss << endl;
    }

    for (int i = size - 1; i >= 0; i--) {
        if (fabs(fmod(xInd - panX, 3 * scale)) < EPSILON) {
            if (fabs(xInd - round(xInd)) < 0.0001) { //If xInd is an integer
                ss << std::setw(4) << std::right << static_cast<int>(xInd);
            } else {
                string s = to_string(xInd);
                if (s.size() > 4) s = s.substr(0, 3);
                ss << std::setw(4) << std::right << s;
            }
        } else ss << " ";
        xInd += scale;
    }
    ss << endl;

    // Add objects to field
    string out = ss.str();
    for (const auto &obj: objects) {
        float x = obj.second.first;
        float y = obj.second.second;

        if (x < xInd && y <= scaleSizeY && x >= panX && y >= panY) {

            float lineSize = float(size) * 2 + 4;
            float ind = lineSize * float(size - 1) -
                        floor((y - panY) / scale) * lineSize +
                        floor((x - panX) / scale) * 2 + 3;

            out.replace(static_cast<std::string::size_type>(ind), 2,
                        obj.first.substr(0, 2)); //Put subname of object to map
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

void View::setDefault() {
    size = 25;
    scale = 2;
    panX = 0;
    panY = 0;
}

void View::setSize(int size_) {
    View::size = size_;
}

void View::setScale(float scale_) {
    View::scale = scale_;
}

void View::setPanX(float panX_) {
    View::panX = panX_;
}

void View::setPanY(float panY_) {
    View::panY = panY_;
}


