#include <iomanip>
#include "../include/Traveling_Santa.h"

int main() {
    srand(time(nullptr));
    Traveling_Santa ts;
    ts.readData("cities.csv");
    Path path(ts.all_points, ts.data);
    /*
    for (auto a : path.points) {
        cout << a << "\n";
    }
    cout << path.getLength(ts.data);
     */
    return 0;
}