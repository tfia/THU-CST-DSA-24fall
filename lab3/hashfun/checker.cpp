#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>

using namespace std;

vector<string> hs = {"0", "bad_hashing", "good_hashing"};
vector<string> cs = {"0", "linear_probe", "quadratic_probe", "overflow_strategy"};

int main()
{
    char buf[100];
    freopen("results.txt", "w", stdout);
    for (int i = 1; i <= 2; i++)
        for (int j = 1; j <= 3; j++)
            for (int k = 1; k <= 3; k++)
            {
                sprintf(buf, ".\\main.exe %d %d < test%d.in > test%d.out", i, j, k, k);
                double t = clock();
                system(buf);
                double t2 = clock();
                sprintf(buf, ".\\std.exe < test%d.in > test%d.ans", k, k);
                system(buf);
                sprintf(buf, "FC test%d.ans test%d.out > NUL", k, k);
                if (system(buf))
                    return -1;
                cout << "Case " << k << " took " << (t2 - t) / CLOCKS_PER_SEC << "s." << endl;
                cout << "\thashing strategy = " << hs[i] << ", collision strategy = " << cs[j] << endl;
            }
    return 0;
}