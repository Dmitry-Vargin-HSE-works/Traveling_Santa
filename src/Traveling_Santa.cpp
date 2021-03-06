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
        best_way.points = path.points;
        best_way.size = path.size;
        this->best_way.printPath();
    }
}

Path Traveling_Santa::runAlgorithm() {
    srand(time(NULL));
    while (true) {
        for (int i = 0; i < this->ant_num; ++i) {
            this->first_points[i] = rand() % this->points_num;
        }
        this->paths.resize(0);
        for (int i : this->first_points) {
            this->passed_points.resize(0);
            this->passed_points.push_back(i);

            this->not_passed_points = this->all_points;
            int j = 0;
            for (j = 0; j < this->not_passed_points.size(); ++j) {
                if (not_passed_points[j] == i) {
                    break;
                }
            }
            not_passed_points.erase(not_passed_points.begin() + j);
            while (!this->not_passed_points.empty()) {
                //Path(this->passed_points, this->data).printPath();
                //Path(this->not_passed_points, this->data).printPath();
                this->goToNextPoint(); //// TODO: fix
            }
            Path tmp_path(this->passed_points, this->data);
            this->paths.push_back(tmp_path);
            this->setBestWay(this->paths[this->paths.size() - 1]);
        }
        this->updatePheromone();
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

int Traveling_Santa::randomPoint(vector<float> probability_roulette) {
  int next_point = 0;
  float choice = 1.0 * rand() / RAND_MAX;

  float sum = 0;
  for (float i : probability_roulette) {
    if (sum < choice) {
      sum += i;
      ++next_point;
    }
  }

  return next_point;
}

void Traveling_Santa::goToNextPoint() {
    /// ???????????? ???? ??????????
    /// ???????????? ?????????????? ?????????????????? ?????????? ???? not_passed_points
    /// ?? ?????????????????? ???? ?? ?????????? passed_points
    int last_point = this->passed_points[this->passed_points.size()-1];

    vector<float> chances = this->getChances(last_point);
    int new_point = this->getRandomPoint(chances);

    this->passed_points.push_back(new_point);
    int i;
    for (i = 0; i < this->not_passed_points.size(); ++i) {
        if (this->not_passed_points[i] == new_point) {
            break;
        }
    }
    this->not_passed_points.erase(this->not_passed_points.begin() + i);
}

vector<float> Traveling_Santa::getChances(int last_point) {
    vector<float> chances; chances.resize(this->data.size());
    double sum = 0.0;
    for (auto i : this->passed_points) {
        chances[i] = 0.0f;
    }
    int c = 0;
    for (auto i : this->not_passed_points) {
        chances[i] = pow(this->data[last_point][i].second, this->a) / pow(this->data[last_point][i].first, this->b);
        sum += chances[i];
    }
    // double tmp_sum = 0.0; for (int i = 0; i < chances.size(); ++i) { cout << i << ") " << pow(this->data[last_point][i].second, this->b) << " / " <<  pow(this->data[last_point][i].first, this->b) << " = " << chances[i] << " " << tmp_sum << " " << sum << "\n"; }
    for (int i = 0; i < chances.size(); ++i) {
        chances[i] /= sum;
    }
    return chances;
}

int Traveling_Santa::getRandomPoint(vector<float> chances) {
    float rand_value = 1.0 * rand() / RAND_MAX;
    for (int i = chances.size()-1; i >= 0; --i) {
        for (int j = 0; j < i; ++j) {
            chances[i] += chances[j];
        }
    }

    for (int i = 0; i < chances.size(); ++i) {
        if (rand_value <= chances[i])
            return i;
    }
    return 0;
}

/*
void Traveling_Santa::goToNextPoint() {
  int current_point = passed_points[passed_points.size() - 1]; // ?????????????? ??????????
  vector<float> probability_roulette; // "?????????????? ????????????"

  // ?????????????? ?????????? ?????????????????????? ???? ?????????? ????????????????????????
  float overall_probability = 0;
  for (auto id : not_passed_points) {
    if (current_point != id) {
      overall_probability += probabilityToPoints(current_point, id);
    }
  }

  // ???????????????????? "?????????????? ????????????"
  float individual_probability;
  for (auto id : not_passed_points) {
    if (current_point != id) {
      individual_probability = probabilityToPoints(current_point, id) / overall_probability;
      probability_roulette.push_back(individual_probability);
    }
  }

  // ?????????????????? ?? ????????????????????
  int next_point = randomPoint(probability_roulette);
  passed_points.push_back(not_passed_points[next_point]);

  // ?????????????? ???? ????????????????????????
  int ind = 0;
    for (int j = 0; j < this->not_passed_points.size(); ++j) {
        if (passed_points[ind] == next_point)
            ind = j;
    }
    not_passed_points.erase(not_passed_points.begin() + ind);
}

float Traveling_Santa::probabilityToPoints(int current_point, int next_point) {
  float probability_to_points;
  probability_to_points = pow(data[current_point][next_point].second, a)
                          * pow(data[current_point][next_point].first, b);
  return probability_to_points;
}
 */