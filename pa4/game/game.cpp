#include <iostream>
#include <cstdio>
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;
typedef long long ll;

namespace tfia_ns
{
    struct Node
    {
        int v, w; // 边的终点、边权
    };

    template <typename T>
    class Vector // 简易 vector，继承自邓老师的代码包
    {
        using Rank = unsigned long long; // 秩
#define DEFAULT_CAPACITY 10              // 默认的初始容量
        Rank _size;
        Rank _capacity;
        T *_elem;
        void copyFrom(T const *A, Rank lo, Rank hi)
        {
            _elem = new T[_capacity = max(DEFAULT_CAPACITY, (hi - lo) * 2)];
            for (_size = 0; lo < hi; _size++, lo++)
                _elem[_size] = A[lo];
        } // 复制数组区间A[lo, hi)
        void expand()
        {
            if (_size < _capacity)
                return;
            T *oldElem = _elem;
            copyFrom(oldElem, 0, _capacity);
            delete[] oldElem;
        } // 空间不足时扩容
    public:
        Vector(Rank c = DEFAULT_CAPACITY)
        {
            _elem = new T[_capacity = c];
            _size = 0;
        }

        ~Vector() { delete[] _elem; }

        Rank size() const { return _size; }
        bool empty() const { return !_size; }

        T &operator[](Rank r) { return _elem[r]; }
        const T &operator[](Rank r) const { return _elem[r]; }
        Rank insert(Rank r, T const &e)
        {
            expand(); // 若有必要，扩容
            for (Rank i = _size; i > r; i--)
                _elem[i] = _elem[i - 1]; // 自后向前，后继元素顺次后移一个单元
            _elem[r] = e;
            _size++;  // 插入后向量规模增加
            return r; // 返回秩
        } // 插入元素
        Rank push_back(T const &e) { return insert(_size, e); }
    };

    template <typename T>
    class PriorityQueue // 用小根二叉堆实现的简易优先队列
    {
#define LC(x) (x << 1)
#define RC(x) ((x << 1) | 1)
        T heap[N << 1];
        int sz;

    public:
        PriorityQueue() { sz = 0; }
        void push(T x)
        {
            heap[++sz] = x; // 先插入到最后
            int cur = sz;
            while (cur) // 向上调整
            {
                int nxt = cur >> 1;
                if (heap[nxt] > heap[cur])
                    std::swap(heap[nxt], heap[cur]); // 如果新点的父亲比新点更小，则交换位置
                else
                    break;
                cur = nxt; // 继续向上跳
            }
        }
        T &top() { return heap[1]; }
        void pop() // 弹出队首
        {
            std::swap(heap[1], heap[sz]);
            sz--; // 把根和堆底交换，然后直接删除堆底
            int cur = 1;
            while ((cur << 1) <= sz) // 向下调整
            {
                int nxt;
                // 检查根要跟左儿子换还是跟右儿子换
                if (RC(cur) <= sz && heap[RC(cur)] < heap[LC(cur)])
                    nxt = RC(cur); // 右儿子更小，跟右儿子换
                else
                    nxt = LC(cur); // 跟左儿子换
                if (heap[nxt] < heap[cur])
                    swap(heap[nxt], heap[cur]); // 交换操作
                else
                    break;
                cur = nxt; // 继续向下跳
            }
            return;
        }
        bool empty() { return sz == 0; }
    };
}

using namespace std;

int n, m, t[N];
ll ans[N], dis[N]; // 最短路数量、最短路长度
bool vis[N];

tfia_ns::Vector<tfia_ns::Node> Adj[N];        // 邻接表存图
tfia_ns::PriorityQueue<pair<int, int>> q; // 已求出最短路的点，<答案, 点的编号>，按答案排序

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &t[i]);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        // 无向边，用两条有向边表示
        Adj[u].push_back(tfia_ns::Node{v, t[v]});
        Adj[v].push_back(tfia_ns::Node{u, t[u]}); // 点权转化为边权
    }
    // Dijkstra 求最短路
    // 初始化
    for (int i = 0; i <= n; i++)
        dis[i] = 1e9;
    dis[1] = 0;
    q.push(make_pair(0, 1));
    ans[1] = 1;
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop(); // 取出已求出最短路且值最小的点
        if (vis[u])
            continue;
        vis[u] = 1;
        for (int i = 0; i < Adj[u].size(); i++) // 遍历 u 的所有出边
        {
            int v = Adj[u][i].v, w = Adj[u][i].w;
            if (dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w; // 松弛
                ans[v] = ans[u];     // v 的最短路尚未被更新过，新的最短路为 u->v，因而 v 的最短路数量等于 u 的
                q.push(make_pair(dis[v], v));
            }
            else if (dis[u] + w == dis[v])
            {
                ans[v] += ans[u]; // v 的最短路已经被不是 u 的点更新过，但是 u->v 仍然为可行的最短路
                ans[v] %= MOD;
            }
        }
    }
    printf("%lld\n%lld", dis[n] + t[1], ans[n] % MOD); // 第一关也要挑战，加上第一关的点权
    return 0;
}