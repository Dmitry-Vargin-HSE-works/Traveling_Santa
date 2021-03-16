#ifndef TRAVELING_SANTA_PATH_H
#define TRAVELING_SANTA_PATH_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <fstream>
#include <filesystem>

using namespace std;

class Path {
public:
    vector<int> points;
    double size = 1.0 / 0.0;

    Path() {
        this->points = {};
    }

    Path(vector<int> ps, vector<vector<pair<float, float>>> data) {
        this->points = ps;
        this->size = this->getLength(data);
    }

    double getLength(vector<vector<pair<float, float>>> data) {                //// D
        if (this->size == 1.0 / 0.0) {
            double tmp_size = 0.0;
            for (int i = 0; i < this->points.size() - 1; ++i) {
                tmp_size += data[points[i]][points[i+1]].first;
            }
            this->size = tmp_size;
        }
        return this->size;
    };

    void printPath() {
        cout << std::fixed << this->size << "\n[";
        for (auto x: this->points) { cout << x << ", "; }

        cout << "]\n\n";
    };
};

#endif //TRAVELING_SANTA_PATH_H
