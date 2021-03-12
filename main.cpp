#include <iomanip>
#include "Traveling_Santa.h"

int main() {

    Traveling_Santa ts;
    ts.readData("cities.csv");
    for (auto a: ts.data) {
        for (auto c : a) {
            cout << c.first << " ";
        }
        cout << "\n";
    }
    return 0;
}