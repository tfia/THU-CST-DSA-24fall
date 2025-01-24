#include <cstdio>

long long matrix[2005][2005];

int main()
{
    int n, m, q;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            scanf("%lld", &matrix[i][j]);
        }
    }
    scanf("%d", &q);
    long long sum = 0;
    for (int i = 1; i <= q; ++i)
    {
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        for (int j = 0; j < a; ++j)
        {
            for (int k = 0; k < b; ++k)
            {
                sum += matrix[x + j][y + k];
            }
        }
        printf("%d\n", sum);
        sum = 0;
    }
    return 0;
}