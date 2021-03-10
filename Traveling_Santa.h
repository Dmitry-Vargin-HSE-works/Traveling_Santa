#ifndef TRAVELING_SANTA_TRAVELING_SANTA_H
#define TRAVELING_SANTA_TRAVELING_SANTA_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>

const unsigned int DIM = 197769;

using namespace std;

class Traveling_Santa {
public:
    vector<pair<float, float>> tmp;
    vector<vector<pair<float, float>>> data;

    void readData(int row_num);
    void convertDataToMatrix();

    float main();

    int getDataLength();
};


#endif //TRAVELING_SANTA_TRAVELING_SANTA_H