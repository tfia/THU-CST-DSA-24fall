#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

set<int> s;

int query_maxle(int x)
{
    set<int>::iterator it = s.upper_bound(x);
    if (it == s.begin())
        return -1;
    return *(--it);
}

int n, x;
char op[5];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", op);
        scanf("%d", &x);
        if (op[0] == 'A')
            s.insert(x);
        if (op[0] == 'B')
            s.erase(x);
        if (op[0] == 'C')
            printf("%d\n", query_maxle(x));
    }
    return 0;
}