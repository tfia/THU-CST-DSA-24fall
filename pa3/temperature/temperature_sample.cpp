#include <cstdlib>
#include "temperature.h"

using namespace std;

void init(int n, const int *x, const int *y, const int *t) {
    // nothing to init
}

void query(int x1, int x2, int y1, int y2, int *tmin, int *tmax) {
    *tmin = rand();
    *tmax = rand();
}
