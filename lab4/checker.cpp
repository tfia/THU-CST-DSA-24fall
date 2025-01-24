#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>

using namespace std;

vector<string> cases = {"0", "random", "good_locality", "bad_locality"};
char trees[3][20] = {"0", "splay", "avl"};

int main()
{
    char buf[100];
    freopen("results.txt", "w", stdout);
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 2; j++)
            for (int k = 1; k <= 4; k++)
            {
                sprintf(buf, ".\\%s.exe< test%d%d.in > test%d%d.out", trees[j], i, k, i, k);
                double t = clock();
                system(buf);
                double t2 = clock();
                sprintf(buf, ".\\std.exe < test%d%d.in > test%d%d.ans", i, k, i, k);
                system(buf);
                sprintf(buf, "FC test%d%d.ans test%d%d.out > NUL", i, k, i, k);
                if (system(buf))
                    return -1;
                cout << "Case " << k << " took " << (t2 - t) / CLOCKS_PER_SEC << "s." << endl;
                cout << "\tcase type = " << cases[i] << ", tree type = " << trees[j] << endl;
            }
    return 0;
}