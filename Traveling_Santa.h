#ifndef TRAVELING_SANTA_TRAVELING_SANTA_H
#define TRAVELING_SANTA_TRAVELING_SANTA_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>

using namespace std;

class Path;

class Traveling_Santa {
public:
    const int q = 4; // константа для формулы изменения ферамона
    const int a = 1; // константа для желания поити в точку в зависимости от ферамона
    const int b = 1; // константа для желания поити в точку в зависимости от близости
    const float p = 0.64; // множитель для уменьшения ферамона
    const int ant_num = 100; // количество проходов за одну итерацию
    int points_num; // количество точек // после считывания будет 197768

    Path best_way();

    vector<pair<float, float>> tmp;
    vector<vector<pair<float, float>>> data;

    void readData(int row_num);
    Path runAlgorithm();         //// TODO


private:
    vector<int> all_points; // чтоб копировать в непройденные точки

    vector<Path> paths; // пути пройденные за время итераций
    vector<int> first_points; // первые точки для в итерации

    vector<int> passed_points;
    vector<int> not_passed_points;

    void convertDataToMatrix();

    // Функции для прохождения в следующую точку
    void goToNextPoint(); //// TODO
    vector<pair<float, float>> getDistanceAndPheromone(); ////TODO
    vector<float> probabilityToPoints(vector<pair<float, float>> stats); ////TODO
    int randomPoint(vector<float>); ////TODO


    void setBestWay(Path path); //// TODO

    void updatePheromone(); ////TODO
};



class Path {
public:
    vector<int> points;
    double size = 1.0 / 0.0;

    Path() {
        this->points = {};
    }

    Path(vector<int> ps) {
        this->points = ps;
        this->size = this->getLength();
    }

    double getLength() {                //// TODO
        if (this->size == 1.0 / 0.0) {
            //
        }
        return this->size;
    };

};


#endif //TRAVELING_SANTA_TRAVELING_SANTA_H