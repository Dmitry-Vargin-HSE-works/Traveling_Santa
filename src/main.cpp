#include <iomanip>
#include "../include/Traveling_Santa.h"

int main() {
    srand(static_cast <unsigned> (NULL));
    Traveling_Santa ts;
    ts.readData("cities.csv");
    Path path(ts.all_points, ts.data);
    ts.paths.push_back(path);
    ts.updatePheromone();

    for (auto & l : ts.data) {
        for (auto & c : l) {
            if (c.second > 0.64)
                cout << c.second << " ";
        }
        cout << "\n";
    }
    return 0;
}