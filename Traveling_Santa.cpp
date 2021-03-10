#include "Traveling_Santa.h"
#include "filesystem"

#ifdef __unix__
string slash = "/";
#else
#if defined(_WIN64)
string slash = "\\";
#elif defined(_WIN32)
string slash = "\\";
#endif
#endif

namespace fs = std::filesystem;

void Traveling_Santa::readData(string file_name) {
    string tmpS;
    pair<float, float> tmpP;
    float x, y;
    string path = fs::current_path().string();
    path = path.substr(0, path.rfind(slash));
    path = path + slash + "data" + slash + file_name;
    cout << path;
    ifstream file(path);
    if (file.is_open()) {
        getline(file, tmpS);
        while (getline(file, tmpS)) {
            cout << tmpS;
            tmpP.first = stof(tmpS.substr(tmpS.find(',')+1, tmpS.rfind(',')));
            tmpP.second = stof(tmpS.substr(tmpS.rfind(',')+1, tmpS.size()));
            this->tmp.push_back(tmpP);
        }
    }
    file.close();
    this->points_num = this->tmp.size();
    this->convertDataToMatrix();
    for (int i = 0; i < this->tmp.size(); ++i) {
        this->all_points.push_back(i);
    }
}

void Traveling_Santa::convertDataToMatrix() {
    for (int i = 0; i < this->points_num; ++i) {
        vector<pair<float, float>> v;
        data.push_back(v);
        for (int j = 0; j < this->points_num; ++j) {
            pair<float, float> p;
            data[i].push_back(p);
            data[i][j].first = sqrt(abs(tmp[i].first * tmp[i].second - tmp[j].first * tmp[j].second));
            data[i][j].second = 1.0f;
        }
    }
}
