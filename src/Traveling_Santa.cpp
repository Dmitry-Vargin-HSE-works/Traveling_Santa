#include "../include/Traveling_Santa.h"

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

void Traveling_Santa::readData(const string& file_name) {
    string tmpS;
    pair<float, float> tmpP;
    string path = fs::current_path().string();
    path = path.substr(0, path.rfind(slash)) + slash + "data" + slash + file_name;
    ifstream file(path);
    if (file.is_open()) {
        getline(file, tmpS);
        while (getline(file, tmpS)) {
            tmpP.first = stof(tmpS.substr(tmpS.find(',')+1, tmpS.rfind(',')));
            tmpP.second = stof(tmpS.substr(tmpS.rfind(',')+1, tmpS.size()));
            this->tmp.push_back(tmpP);
        }
    }
    file.close();
    this->points_num = this->tmp.size();
    this->all_points.resize(this->points_num);
    this->first_points.resize(this->ant_num);
    for (int i = 0; i < this->points_num; ++i) {
        this->all_points[i] = i;
    }
    this->convertDataToMatrix();
    this->tmp.resize(0);
}

void Traveling_Santa::convertDataToMatrix() {
    data.resize(this->points_num);
    for (int i = 0; i < this->points_num; ++i) {
        data[i].resize(this->points_num);
        for (int j = 0; j < this->points_num; ++j) {
            data[i][j].first = sqrt(pow(tmp[i].first - tmp[j].first, 2) + pow(tmp[i].second - tmp[j].second, 2));
            data[i][j].second = 1.0f;
        }
    }
    vector<pair<float, float>> f;
    this->tmp = f;
}

void Traveling_Santa::setBestWay(const Path& path) {
    if (path.size < this->best_way.size) {
        best_way.points = path.points;
        best_way.size = path.size;
        this->best_way.printPath();
    }
}

[[noreturn]] Path Traveling_Santa::runAlgorithm() {
    srand(time(nullptr));
    while (true) {
        for (int i = 0; i < this->ant_num; ++i) {
            this->first_points[i] = rand() % this->points_num;
        }
        this->paths.resize(0);
        for (int i : this->first_points) {
            this->passed_points.resize(1);
            this->passed_points[0] = i;

            this->not_passed_points = this->all_points;
            int ind = 0;
            for (int j = 0; j < this->not_passed_points.size(); ++j) {
                if (not_passed_points[j] == passed_points[0]) {
                  ind = j;
                  break;
                }
            }
            not_passed_points.erase(not_passed_points.begin() + ind);
            while (!this->not_passed_points.empty()) {
                this->goToNextPoint();
            }
            Path tmp_path(this->passed_points, this->data);
            this->paths.push_back(tmp_path);
            this->setBestWay(this->paths[this->paths.size() - 1]);
        }
        this->updatePheromone();
    }
    // return this->best_way;
}

void Traveling_Santa::updatePheromone() {
    for (auto & i : this->data) {
        for (auto & j : i) {
            j.second *= this->p;
        }
    }

    for (Path& path : this->paths) {
        float add = (float) this->q / (float) path.size;
        for (int i = 0; i < path.points.size()-1; ++i) {
            this->data[i][i+1].second += add;
        }
    }

}

void Traveling_Santa::goToNextPoint() {
  int current_point = passed_points[passed_points.size() - 1]; // текущая точка

  // считаем общую вероятность из числа НЕПРОЙДЕННЫХ
  float overall_probability = 0;
  for (int next_point : not_passed_points) {
    overall_probability += probabilityToPoints(current_point, next_point);
  }

  // генерируем "рулетку выбора"
  vector<float> probability_roulette; // "рулетка выбора"
  probability_roulette.reserve(not_passed_points.size());
  for (int next_point : not_passed_points) {
    probability_roulette.push_back(probabilityToPoints(current_point, next_point) / overall_probability);
  }

  // добавляем в пройденные
  int next_point = randomPoint(probability_roulette);
  passed_points.push_back(not_passed_points[next_point]);

  // удаляем из непройденных
  not_passed_points.erase(not_passed_points.begin() + next_point);
}

int Traveling_Santa::randomPoint(const vector<float>& probability_roulette) {
  int next_point = 0;
  float choice = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (1.0 - 0.0));
  float sum = 0;

  for (float value : probability_roulette) {
    if (sum < choice) {
      sum += value;
      ++next_point;
    } else break;
  }

  return next_point == probability_roulette.size() ? --next_point : next_point;
}

float Traveling_Santa::probabilityToPoints(int current_point, int next_point) {
  return pow(data[current_point][next_point].second, a)
          * pow(data[current_point][next_point].first, b);
}