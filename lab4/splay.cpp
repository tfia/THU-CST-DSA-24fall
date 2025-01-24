#include <iostream>
#include <cstdio>

using namespace std;

const int N = 1e7 + 5;

int root, tot, fa[N], ch[N][2], val[N];

bool get_which(int x) { return x == ch[fa[x]][1]; } // lc -> 0, rc -> 1

void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = val[x] = 0; }

void rotate(int x) // x is lc -> right, x is rc -> left
{
    int f = fa[x], gf = fa[f];
    bool which = get_which(x);
    ch[f][which] = ch[x][which ^ 1];
    if (ch[x][which ^ 1])
        fa[ch[x][which ^ 1]] = f;
    ch[x][which ^ 1] = f;
    fa[f] = x;
    fa[x] = gf;
    if (gf)
        ch[gf][f == ch[gf][1]] = x;
} // 将 x 转到其父的位置

void splay(int x)
{
    for (int f = fa[x]; f = fa[x]; rotate(x)) // 有祖父，先把父亲转上去，转完父亲之后再转 x
        if (fa[f])
            rotate(get_which(x) == get_which(f) ? f : x);
    root = x; // x 已经转到顶了
}

int pre() // 找 root 的前驱，即左子树的最右节点
{
    int cur = ch[root][0];
    if (!cur)
        return cur;
    while (ch[cur][1])
        cur = ch[cur][1];
    splay(cur);
    return cur;
}

void query_and_splay(int k)
{
    int cur = root;
    while (1)
    {
        if (k < val[cur])
            cur = ch[cur][0]; // 搜索左子树
        else                  // 答案在右子树
        {
            if (!cur)
                return;        // 空节点，不至于旋转到根
            if (k == val[cur]) // 找到
            {
                splay(cur);
                return;
            }
            cur = ch[cur][1]; // 未找到，搜索右子树
        }
    }
}

int query_maxle(int k)
{
    int res = 0, cur = root, t = 0;
    while (cur)
    {
        if (val[cur] == k)
        {
            splay(cur);
            return val[cur];
        }
        if (val[cur] < k)
        {
            res = cur;
            cur = ch[cur][1];
        }
        else
        {
            t = cur;
            cur = ch[cur][0];
        }
    }
    if (res)
    {
        splay(res);
        return val[res];
    }
    if (t)
        splay(t);
    return -1;
}

void insert(int k)
{
    if (!root) // 树为空
    {
        val[++tot] = k;
        root = tot;
        return;
    }
    int cur = root, f = 0;
    while (1)
    {
        if (val[cur] == k)
        {
            splay(cur);
            break;
        }
        f = cur;
        cur = ch[cur][val[cur] < k]; // 如果当前值 < k，则查找右子树
        if (!cur)                    // 空节点
        {
            val[++tot] = k;
            fa[tot] = f;
            ch[f][val[f] < k] = tot;
            splay(tot);
            break;
        }
    }
}

void del(int k)
{
    query_and_splay(k);               // 此时 k 已经 splay 到根
    if (!ch[root][0] && !ch[root][1]) // 唯一节点
    {
        clear(root);
        root = 0;
        return;
    }
    if (!ch[root][0]) // 只有右子树
    {
        int cur = root;
        root = ch[root][1];
        fa[root] = 0;
        clear(cur);
        return;
    }
    if (!ch[root][1]) // 只有左子树
    {
        int cur = root;
        root = ch[root][0];
        fa[root] = 0;
        clear(cur);
        return;
    }
    int cur = root, x = pre();
    fa[ch[cur][1]] = x; // 与前驱交换
    ch[x][1] = ch[cur][1];
    clear(cur);
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
            insert(x);
        if (op[0] == 'B')
            del(x);
        if (op[0] == 'C')
            printf("%d\n", query_maxle(x));
    }
    return 0;
}