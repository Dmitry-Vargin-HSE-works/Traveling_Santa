#include <iomanip>
#include "../include/Traveling_Santa.h"

int main() {
    srand(static_cast <unsigned> (NULL));
    Traveling_Santa ts;
    ts.readData("cities.csv");
    ts.runAlgorithm();
    return 0;
}