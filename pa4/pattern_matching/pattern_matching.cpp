#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int N = 2e3 + 5;
const ull BASE_1 = 19260817;
const ull BASE_2 = 13331;

template <typename T>
void qsort(T *a, T l, T r)
{
    T i = l, j = r;
    T x = a[(l + r) >> 1];
    do
    {
        while (a[i] < x)
            i++;
        while (a[j] > x)
            j--;
        if (i <= j)
        {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (j > l)
        qsort(a, l, j);
    if (i < r)
        qsort(a, i, r);
} // 快速排序

template <typename T>
T *lower_bound(T *l, T *r, T x)
{
    while (l < r)
    {
        T *mid = l + ((r - l) >> 1);
        if (*mid < x)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
} // 二分查找，找到第一个大于等于x的数

template <typename T>
T *upper_bound(T *l, T *r, T x)
{
    while (l < r)
    {
        T *mid = l + ((r - l) >> 1);
        if (*mid <= x)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
} // 二分查找，找到第一个大于x的数

ull power_1[N], power_2[N], h[N][N], ans[N * N];
char s[N][N];

int n, m, a, b, k, cnt;

int main()
{
    scanf("%d%d%d%d%d", &m, &n, &a, &b, &k);
    for (int i = 1; i <= m; i++)
        scanf("%s", s[i] + 1);
    // 预处理 BASE 的幂次
    // 二维哈希对行和列应用不同的 BASE
    power_1[0] = power_2[0] = 1;
    for (int i = 1; i <= m; i++)
        power_1[i] = power_1[i - 1] * BASE_1;
    for (int i = 1; i <= n; i++)
        power_2[i] = power_2[i - 1] * BASE_2;
    // 计算目标矩阵的二维哈希
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            h[i][j] = h[i - 1][j] * BASE_1 + h[i][j - 1] * BASE_2 + s[i][j] - h[i - 1][j - 1] * BASE_1 * BASE_2;
    // 预处理目标矩阵的所有 a*b 大小子矩阵的哈希
    for (int i = 1; i <= m - a + 1; i++)
        for (int j = 1; j <= n - b + 1; j++)
            ans[++cnt] = h[i + a - 1][j + b - 1] - h[i - 1][j + b - 1] * power_1[a] - h[i + a - 1][j - 1] * power_2[b] + h[i - 1][j - 1] * power_1[a] * power_2[b];
    // 排序所有子矩阵的哈希
    qsort(ans, (ull)1, (ull)cnt);
    while (k--)
    {
        for (int i = 1; i <= a; i++)
            scanf("%s", s[i] + 1);
        // 计算询问矩阵的二位哈希
        for (int i = 1; i <= a; i++)
            for (int j = 1; j <= b; j++)
                h[i][j] = h[i - 1][j] * BASE_1 + h[i][j - 1] * BASE_2 + s[i][j] - h[i - 1][j - 1] * BASE_1 * BASE_2;
        // 二分查找询问矩阵的哈希在所有子矩阵哈希中的出现次数
        printf("%llu\n", upper_bound(ans + 1, ans + cnt + 1, h[a][b]) - lower_bound(ans + 1, ans + cnt + 1, h[a][b]));
    }
    return 0;
}