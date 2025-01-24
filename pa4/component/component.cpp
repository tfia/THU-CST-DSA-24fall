#include <iostream>
#include <cstdio>
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;

const int N = 1e6 + 5;

namespace tfia_ns
{
    class DSU // 并查集
    {
        int f[N];

    public:
        void init(int x)
        {
            for (int i = 0; i <= x; i++)
                f[i] = i;
        }

        int find(int x) // 查找 x 的祖先，带路径压缩
        {
            if (x == f[x])
                return x;
            return f[x] = find(f[x]);
        }

        void join(int c1, int c2) // 将 c1 合并到 c2
        {
            int f1 = find(c1), f2 = find(c2);
            if (f1 != f2)
                f[f1] = f2;
        }
    };

    template <typename T>
    class PriorityQueue // 用小根二叉堆实现的简易优先队列
    {
        typedef unsigned long long ull;
#define LC(x) (x << 1)
#define RC(x) ((x << 1) | 1)
#define DEFAULT_CAPACITY 5 // 默认的初始容量
        T *heap;
        ull sz, capacity;

        void expand() // 动态扩容
        {
            if (sz < capacity)
                return;
            T *old_heap = heap;
            heap = new T[(capacity << 1) + 1];
            capacity = (capacity << 1) + 1;
            // memset(heap, 0, sizeof(T) * capacity);
            for (int i = 0; i <= sz; i++)
                heap[i] = old_heap[i];
            delete[] old_heap;
        }

    public:
        PriorityQueue(ull c = DEFAULT_CAPACITY)
        {
            heap = new T[capacity = c];
            // memset(heap, 0, sizeof(T) * capacity);
            sz = 0;
        }
        ~PriorityQueue() { delete[] heap; }
        void push(T x)
        {
            ++sz;
            expand();
            heap[sz] = x; // 先插入到最后
            ull cur = sz;
            while (cur > 1) // 向上调整
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
            ull cur = 1;
            while ((cur << 1) <= sz) // 向下调整
            {
                ull nxt;
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
        ull size() { return sz; }
    };
}

void merge(tfia_ns::PriorityQueue<int> *u, tfia_ns::PriorityQueue<int> *v, int k) // 将 u 合并到 v
{
    while (!u->empty())
    {
        int w = u->top();
        u->pop();
        if (v->size() >= k && w <= v->top())
            continue; // 常数优化，如果当前堆已经满了且当前元素比堆顶还小，直接跳过
        v->push(w);
    }
    while (v->size() > k)
        v->pop(); // 保证堆的大小不超过 k
    delete u;     // 删除 u 以释放空间
}

tfia_ns::DSU dsu;
tfia_ns::PriorityQueue<int> *pqs[N];
int n, m, k, q;

int main()
{
    scanf("%d%d%d%d", &n, &m, &k, &q);
    dsu.init(n);
    for (int i = 1; i <= n; i++)
    {
        int w;
        scanf("%d", &w);
        pqs[i] = new tfia_ns::PriorityQueue<int>; // 初始化，对每个节点都建一个堆
        pqs[i]->push(w);
    }
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        if (dsu.find(u) == dsu.find(v))
            continue; // 如果已经在同一个连通分量中，直接跳过
        if (pqs[dsu.find(u)]->size() > pqs[dsu.find(v)]->size())
            swap(u, v); // 确保一定是把小的合并到大的
        int fau = dsu.find(u), fav = dsu.find(v);
        dsu.join(u, v);               // 维护并查集
        merge(pqs[fau], pqs[fav], k); // 合并两个堆
    }
    for (int i = 1; i <= q; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if (dsu.find(u) == dsu.find(v))
                continue; // 如果已经在同一个连通分量中，直接跳过
            if (pqs[dsu.find(u)]->size() > pqs[dsu.find(v)]->size())
                swap(u, v); // 确保一定是把小的合并到大的
            int fau = dsu.find(u), fav = dsu.find(v);
            dsu.join(u, v);               // 维护并查集
            merge(pqs[fau], pqs[fav], k); // 合并两个堆
        }
        else if (op == 2)
        {
            int u;
            scanf("%d", &u);
            if (pqs[dsu.find(u)]->size() < k)
                printf("-1\n");
            else
                printf("%d\n", pqs[dsu.find(u)]->top()); // 堆顶就是第 k 大
        }
    }
    return 0;
}