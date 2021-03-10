#include <iomanip>
#include "Traveling_Santa.h"

int main() {

    Traveling_Santa ts;
    //ts.readData("cities.csv");
    const int n = 200000;
    vector<vector<pair<float, float>>> qwe;
    qwe.resize(n);
    for (int i = 0; i < n; ++i) {
        qwe[i].resize(n);
        for (int j = 0; j < n; ++j) {
            qwe[i][j].first = 1.0;
            qwe[i][j].second = 2.0;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << qwe[i][j].first << " ";
        }
        cout << "\n";
    }

    /*
    Path path(ts.all_points, ts.data);
    for (auto a : path.points)
        cout << a << " ";
*/
    /*
    srand(time(nullptr));
    vector<vector<float>> v;
    for (int i = 0; i < 197768; ++i) {
        vector<float> t;
        v.push_back(t);
        for (int j = 0; j < 197768; ++j) {
            v[i].push_back((rand()));
            cout << v[i][j] << " ";
        }
        cout << "\n";
    }
    for (vector<float> a : v) {
        for (double c : a) {
            cout << c << " ";
        }
        cout << "\n";
    }
     */
    /*
    Traveling_Santa ts;
    ts.readData(5);
    for (auto x : ts.data) {
        for (auto y : x) {
            cout << y.second << " ";
        }
        cout << "\n";
    }
    ts[x][y]
     */
    /*
    ts.data["X"].push_back(12.1f);
    ts.data["X"].push_back(1.1f);
    ts.data["Y"].push_back(1.1f);
    for (auto & it : ts.data) {
        cout << it.first << ": ";
        for (float f : it.second) {
            cout << f << ", ";
        }
        cout << "\n";
    }
     */
    return 0;
}