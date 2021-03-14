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

void Traveling_Santa::readData(string file_name) {
    string tmpS;
    pair<float, float> tmpP;
    float x, y;
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

void Traveling_Santa::setBestWay(Path path) {
    if (path.size < this->best_way.size) {
        best_way = path;
    }
}

Path Traveling_Santa::runAlgorithm() {
    while (true) {
        for (int i = 0; i < this->ant_num; ++i) {
            this->first_points[i] = rand() % this->points_num;
        }
        this->paths.resize(0);
        for (int i : this->first_points) {
            while (!this->not_passed_points.empty()) {
                //this->goToNextPoint();
            }
            Path tmp_path(this->passed_points, this->data);
            this->paths.push_back(tmp_path);
            this->setBestWay(this->paths[this->paths.size() - 1]);
        }
        this->updatePheromone();
        break;
    }
    return this->best_way;
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

//// K

int Traveling_Santa::randomPoint(vector<float> probability_roulette) {
  int next_point = 0;
  float choice = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (1.0 - 0.0));
  while (probability_roulette[next_point] > choice) {
    ++next_point;
  }
  return next_point;
}

void Traveling_Santa::goToNextPoint(int current_point) {
  vector<float> probability_roulette;

  float overall_probability = 0;
  for (int i = 0; i < points_num; ++i) {
    if (current_point != i) {
      overall_probability += probabilityToPoints(current_point, i);
    }
  }

  for (int i = 0; i < points_num; ++i) {
    if (current_point != i) {
      float individual_probability = probabilityToPoints(current_point, i) / overall_probability;
      probability_roulette.push_back(individual_probability);
    }
  }

  int next_point = randomPoint(probability_roulette);
  passed_points.push_back(next_point);

  int index = 0;
  for (auto vector : all_points) {
    if (vector != next_point) {
      ++index;
    }
  }
  passed_points.erase(passed_points.begin() + index);
}

float Traveling_Santa::probabilityToPoints(int current_point, int next_point) {
  float probability_to_points;
  probability_to_points = pow(data[current_point][next_point].second, a)
                          * pow(data[current_point][next_point].first, b);
  return probability_to_points;
}