#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

const int N = 500000;

struct Entry
{
    int v1;
    string name;
} a[N + 5];

int n, m, num;
char filename[20];

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    n = atoi(argv[1]);
    m = atoi(argv[2]);
    num = atoi(argv[3]);
    sprintf(filename, "test%d.in", num);
    freopen("poj.txt", "r", stdin);
    int _;
    for (int i = 0; i < N; i++)
        cin >> _ >> a[i].name >> a[i].v1 >> _;

    freopen(filename, "w", stdout);
    shuffle(a, a + N + 1, default_random_engine(rand()));
    for (int i = 0; i < n; i++)
        cout << 0 << " " << a[i].name << " " << a[i].v1 << endl;
    shuffle(a, a + N + 1, default_random_engine(rand()));
    for (int i = 0; i < m; i++)
        cout << 1 << " " << a[i].name << endl;
    cout << 2 << endl;
    return 0;
}