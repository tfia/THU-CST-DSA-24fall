#include <cassert>
#include <cstdio>
#include <cstring>
#include "temperature.h"

using namespace std;

int main() {
    // in case of defined(NDEBUG), do not write `assert(1 == scanf("%d", &n))'
    int res; // store the return value of `scanf'
    int n;
    res = scanf("%d", &n);
    assert(1 == res);
    assert(1 <= n && n <= 200000);

    // init stations
    int *x = new int[n], *y = new int[n];
    int *t = new int[n];
    for (int i = 0; i < n; i++) {
        long long xi, yi, ti;
        res = scanf("%lld%lld%lld", &xi, &yi, &ti);
        assert(3 == res);
        x[i] = xi;
        y[i] = yi;
        t[i] = ti;
        assert(x[i] == xi && y[i] == yi && t[i] == ti); // check overflow
        assert(t[i] >= 0);
    }
    init(n, x, y, t);

    // after init(), forbid using x, y, and t
    memset(x, 0, n * sizeof(int));
    memset(y, 0, n * sizeof(int));
    memset(t, 0, n * sizeof(int));
    delete[] x;
    delete[] y;
    delete[] t;

    // do query
    long long x1, x2, y1, y2;
    int m = 0;
    while (EOF != (res = scanf("%lld%lld%lld%lld", &x1, &x2, &y1, &y2))) {
        assert(4 == res);
        assert(x1 == (int)x1 && x2 == (int)x2 && y1 == (int)y1 && y2 == (int)y2); // check overflow
        assert(x1 <= x2 && y1 <= y2);
        int tmin, tmax;
        query(x1, x2, y1, y2, &tmin, &tmax);
        printf("%d %d\n", tmin, tmax);
        m++;
    }

    assert(1 <= m && m <= 160000);

    return 0;
}
