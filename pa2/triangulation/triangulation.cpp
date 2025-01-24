#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 1e6 + 5;

struct Point
{
    ll x, y;
    bool is_up;
    bool operator<(const Point &p) const
    {
        if (x == p.x)
            return y < p.y;
        return x < p.x;
    } // 重载operator<，用于直接比较两个点的x坐标
}; // 点类，包含坐标和是否在靠上的单调链上

bool to_left(const Point &a, const Point &b, const Point &c)
{
    return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) > 0);
}

int n, st, ed;
Point a[N];
vector<Point> s;        // 用于模拟栈
vector<Point> up, down; // 分别存储靠上和靠下的单调链

int main()
{
    scanf("%d", &n);
    int mn = 1e9, mx = -1e9;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld %lld", &a[i].x, &a[i].y);
        if (a[i].x < mn)
        {
            mn = a[i].x;
            st = i;
        }
        if (a[i].x > mx)
        {
            mx = a[i].x;
            ed = i;
        }
    }
    if (st < ed)
    {
        for (int i = st; i < ed; i++)
            a[i].is_up = false, down.push_back(a[i]);
        for (int i = st - 1; i >= 1; i--)
            a[i].is_up = true, up.push_back(a[i]);
        for (int i = n; i >= ed; i--)
            a[i].is_up = true, up.push_back(a[i]);
    }
    else
    {
        for (int i = st - 1; i >= ed; i--)
            a[i].is_up = true, up.push_back(a[i]);
        for (int i = st; i <= n; i++)
            a[i].is_up = false, down.push_back(a[i]);
        for (int i = 1; i < ed; i++)
            a[i].is_up = false, down.push_back(a[i]);
    } // 分类讨论，将按序输入的点分为靠上和靠下的两个单调链
    int pup = 0, pdown = 0;
    int sz1 = up.size(), sz2 = down.size();
    s.push_back(down[pdown++]);
    while (1) // 模拟题面给出的算法
    {
        Point cur;
        if (pup == sz1 && pdown == sz2)
            break;
        else if (pup == sz1)
            cur = down[pdown++];
        else if (pdown == sz2)
            cur = up[pup++];
        else
        {
            if (up[pup] < down[pdown])
                cur = up[pup++];
            else
                cur = down[pdown++];
        }
        // cout << "***" << cur.x << " " << cur.y << " " << (cur.is_up ? "up" : "down") << endl;
        // cout << s.size() << endl;
        if (s.back().is_up != cur.is_up) // 如果当前点和栈顶点不在同一单调链上
        {
            Point t = s.back();
            while (s.size() != 1)
            {
                printf("%lld %lld %lld %lld %lld %lld\n", cur.x, cur.y, s.back().x, s.back().y, s[s.size() - 2].x, s[s.size() - 2].y);
                s.pop_back();
            }
            t.is_up = cur.is_up;
            s.pop_back();
            s.push_back(t);
            s.push_back(cur);
        }
        else // 如果当前点和栈顶点在同一单调链上
        {
            while (s.size() != 1 && to_left(cur, s[s.size() - 2], s.back()) ^ s.back().is_up)
            {
                printf("%lld %lld %lld %lld %lld %lld\n", cur.x, cur.y, s.back().x, s.back().y, s[s.size() - 2].x, s[s.size() - 2].y);
                s.pop_back();
            }
            s.push_back(cur);
        }
    }
    return 0;
}