#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <random>
#include <cassert>

using namespace std;

const int M = 8500000;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, M);

set<int> s;

void insert()
{
    int val = dis(gen);
    while (s.find(val) != s.end())
        val = dis(gen);
    printf("A %d\n", val);
    s.insert(val);
}

char buf[30];

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int typ = atoi(argv[2]);
    int no = atoi(argv[3]);
    assert(n % 2 == 0);
    sprintf(buf, "test%d%d.in", typ, no);
    freopen(buf, "w", stdout);
    printf("%d\n", n);
    if (typ == 1)
    {
        for (int i = 1; i <= n; i++)
        {
            unsigned int t = gen();
            if (t % 3 == 0)
                insert();
            if (t % 3 == 1)
            {
                if (s.empty())
                    insert();
                else
                {
                    auto it = s.begin();
                    advance(it, gen() % s.size());
                    printf("B %d\n", *it);
                    s.erase(it);
                }
            }
            if (t % 3 == 2)
            {
                int val = dis(gen);
                printf("C %d\n", val);
            }
        }
    }
    if (typ == 2)
    {
        // for(int i = 1; i <= (n >> 1); i++) insert();
        // int mx = -1;
        // for(auto it : s) mx = max(mx, it);
        // for(int i = 1; i <= (n >> 1); i++) printf("C %d\n", mx);
        for (int i = 1; i <= (n >> 1); i++)
            printf("A %d\n", i);
        for (int i = 1; i <= (n >> 1); i++)
            printf("C %d\n", (n >> 1));
    }
    if (typ == 3)
    {
        for (int i = 1; i <= (n >> 1); i++)
            insert();
        // vector<int> v;
        // for(auto it : s) v.push_back(it);
        // for(int i = 1, j = 0; i <= n; j = (j == 0 ? v.size() - 1 : 0), i++)
        //     printf("C %d\n", v[j]);
        for (int i = 1; i <= (n >> 1); i++)
        {
            int val = dis(gen);
            printf("C %d\n", val);
        }
    }
    return 0;
}