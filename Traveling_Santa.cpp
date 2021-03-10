#include "Traveling_Santa.h"

void Traveling_Santa::readData(int row_num) {
    string tmpS;
    pair<float, float> tmpP;
    float x, y;
    for (int i = 0; i < row_num; ++i) {
        cin >> tmpS;
        tmpP.first = stof(tmpS.substr(tmpS.find(',')+1, tmpS.rfind(',')));
        tmpP.second = stof(tmpS.substr(tmpS.rfind(',')+1, tmpS.size()));
        this->tmp.push_back(tmpP);
    }
    this->points_num = row_num;
    this->convertDataToMatrix();
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
