#include <cstdlib>
#include <iostream>
#include "temperature.h"

using namespace std;

typedef long long ll;

const int N = 2e5 + 5;
const ll INF = 1e18;

int cnt;

struct Point
{
    int x, y, w;
} P[N]; // 用于读取点的结构体

int ls[N], rs[N], val[N], siz[N], d[N][2], L[N][2], R[N][2];
// 分别为：左儿子、右儿子、当前节点的权值、子树大小、当前节点对应平面上点的坐标、子树管辖矩形的坐标范围
// L -> 左下角, R -> 右上角
ll ans_mx[N], ans_mn[N];
// 分别为：当前子树管辖矩形的最大值、最小值

// 自己实现的 nth_element，D 为处理的维度
int nth_elem(int l, int r, int x, int D) // 0 -> x, 1 -> y
{
    if (l == r)
        return ((D == 0) ? P[l].x : P[l].y);
    int i = l, j = r, pivot = ((D == 0) ? P[(rand() % (r - l + 1)) + l].x : P[(rand() % (r - l + 1)) + l].y);
    while (i <= j)
    {
        while (((D == 0) ? P[i].x : P[i].y) < pivot)
            i++;
        while (((D == 0) ? P[j].x : P[j].y) > pivot)
            j--;
        if (i <= j)
            swap(P[i++], P[j--]);
    }
    if (l <= x && x <= j)
        return nth_elem(l, j, x, D);
    if (i <= x && x <= r)
        return nth_elem(i, r, x, D);
    return ((D == 0) ? P[x].x : P[x].y);
}

void push_up(int u)
{
    // 上传子树大小
    siz[u] = siz[ls[u]] + siz[rs[u]] + 1;
    // 计算子树管辖矩形的最大值和最小值
    ans_mx[u] = max((ll)val[u], max(ans_mx[ls[u]], ans_mx[rs[u]]));
    ans_mn[u] = min((ll)val[u], min(ans_mn[ls[u]], ans_mn[rs[u]]));
    // 计算子树管辖矩形的坐标范围
    for (int k = 0; k <= 1; k++)
    {
        L[u][k] = R[u][k] = d[u][k];
        if (ls[u])
        {
            L[u][k] = min(L[u][k], L[ls[u]][k]);
            R[u][k] = max(R[u][k], R[ls[u]][k]);
        }
        if (rs[u])
        {
            L[u][k] = min(L[u][k], L[rs[u]][k]);
            R[u][k] = max(R[u][k], R[rs[u]][k]);
        }
    }
}

// 按照不同维度交替建树
void build(int u, int l, int r, int D = 0) // 0 -> x, 1 -> y
{
    int mid = (l + r) >> 1;
    nth_elem(l, r, mid, D); // 选择中位数，以此划分左右子树
    d[u][0] = P[mid].x, d[u][1] = P[mid].y;
    val[u] = P[mid].w;
    if (l < mid)
    {
        // 使得左孩子的编号相邻，提升空间局部性
        ++cnt;
        ls[u] = cnt;
        build(cnt, l, mid - 1, D ^ 1); // 切换维度
    }
    if (mid < r)
    {
        // 同上
        ++cnt;
        rs[u] = cnt;
        build(cnt, mid + 1, r, D ^ 1);
    }
    push_up(u); // 上传
}

ll g_mx = -1, g_mn = INF; // 全局最值，用于查询时剪枝

ll query_mx(int u, int qx1, int qx2, int qy1, int qy2)
{
    if (ans_mx[u] <= g_mx)
        return g_mx; // 剪枝
    if (!u)
        return -1; // 递归边界
    // 如果当前子树管辖矩形完全包含在查询矩形内，直接返回答案
    if ((qx1 <= L[u][0] && qx2 >= R[u][0]) && (qy1 <= L[u][1] && qy2 >= R[u][1]))
        return ans_mx[u];
    // 如果当前子树管辖矩形完全不在查询矩形内，直接返回 -1
    if (qx1 > R[u][0] || qx2 < L[u][0] || qy2 < L[u][1] || qy1 > R[u][1])
        return -1;
    // 查询矩形部分包含子树矩形
    // 如果当前节点包含在查询矩形内，则将其考虑进答案
    ll res = (qx1 <= d[u][0] && d[u][0] <= qx2 && qy1 <= d[u][1] && d[u][1] <= qy2) ? val[u] : -1;
    // 递归查询左右子树
    return g_mx = max(res, max(query_mx(ls[u], qx1, qx2, qy1, qy2), query_mx(rs[u], qx1, qx2, qy1, qy2)));
}

ll query_mn(int u, int qx1, int qx2, int qy1, int qy2) // 与 query_mx 相同
{
    if (ans_mn[u] >= g_mn)
        return g_mn;
    if (!u)
        return INF;

    if ((qx1 <= L[u][0] && qx2 >= R[u][0]) && (qy1 <= L[u][1] && qy2 >= R[u][1]))
        return ans_mn[u];

    if (qx1 > R[u][0] || qx2 < L[u][0] || qy2 < L[u][1] || qy1 > R[u][1])
        return INF;

    ll res = (qx1 <= d[u][0] && d[u][0] <= qx2 && qy1 <= d[u][1] && d[u][1] <= qy2) ? val[u] : INF;
    return g_mn = min(res, min(query_mn(ls[u], qx1, qx2, qy1, qy2), query_mn(rs[u], qx1, qx2, qy1, qy2)));
}

void init(int n, const int *x, const int *y, const int *t)
{
    srand(time(NULL)); // 初始化随机种子，用于 nth_elem
    for (int i = 0; i <= n; i++)
        ans_mx[i] = -1;
    for (int i = 0; i <= n; i++)
        ans_mn[i] = INF;
    for (int i = 0; i < n; i++)
    {
        P[i + 1].x = x[i];
        P[i + 1].y = y[i];
        P[i + 1].w = t[i];
    }
    build(++cnt, 1, n);
}

ll mn, mx;

void query(int x1, int x2, int y1, int y2, int *tmin, int *tmax)
{
    g_mn = INF;
    g_mx = -1; // 每轮查询，需要初始化全局最值
    mn = query_mn(1, x1, x2, y1, y2);
    mx = query_mx(1, x1, x2, y1, y2);
    *tmin = (int)(mn == INF ? -1 : mn);
    *tmax = (int)mx;
}
