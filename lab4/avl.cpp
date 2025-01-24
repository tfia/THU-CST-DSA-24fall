#include <iostream>
#include <cstdio>

using namespace std;

const int N = 1e7 + 5;

int root, tot, fa[N], ch[N][2], val[N], h[N];

void push_up(int x) { h[x] = max(h[ch[x][0]], h[ch[x][1]]) + 1; } // 维护树高

bool get_which(int x) { return x == ch[fa[x]][1]; } // lc -> 0, rc -> 1

void rotate(int x) // x is lc -> right, x is rc -> left
{
    int f = fa[x], gf = fa[f];
    bool which = get_which(x);
    ch[f][which] = ch[x][which ^ 1]; // 将 x 的左子树挂到 f 的右子树，或对称
    if (ch[x][which ^ 1])
        fa[ch[x][which ^ 1]] = f;
    ch[x][which ^ 1] = f;
    fa[f] = x;
    fa[x] = gf; // 更新父亲
    if (gf)
        ch[gf][f == ch[gf][1]] = x; // 更新祖父的儿子
    push_up(f);
    push_up(x); // 更新高度
    if (!fa[x])
        root = x; // 需要更新根节点
} // 将 x 转到其父的位置

void balance_ins(int x)
{
    while (x)
    {
        if (h[ch[x][0]] - h[ch[x][1]] > 1) // 失衡，且左子树更高
        {
            if (h[ch[ch[x][0]][1]] > h[ch[ch[x][0]][0]]) // 左子树的右子树更高
                rotate(ch[ch[x][0]][1]);                 // 旋转更高的子树
            rotate(ch[x][0]);
            break;
        }
        else if (h[ch[x][1]] - h[ch[x][0]] > 1)
        {
            if (h[ch[ch[x][1]][0]] > h[ch[ch[x][1]][1]]) // 右子树的左子树更高
                rotate(ch[ch[x][1]][0]);
            rotate(ch[x][1]);
            break;
        }
        push_up(x);
        x = fa[x];
    }
}

void balance_del(int x) // 区别在于，要一路维护平衡到根
{
    while (x)
    {
        if (h[ch[x][0]] - h[ch[x][1]] > 1) // 失衡，且左子树更高
        {
            if (h[ch[ch[x][0]][1]] > h[ch[ch[x][0]][0]]) // 左子树的右子树更高
                rotate(ch[ch[x][0]][1]);
            rotate(ch[x][0]);
        }
        else if (h[ch[x][1]] - h[ch[x][0]] > 1)
        {
            if (h[ch[ch[x][1]][0]] > h[ch[ch[x][1]][1]]) // 右子树的左子树更高
                rotate(ch[ch[x][1]][0]);
            rotate(ch[x][1]);
        }
        push_up(x);
        x = fa[x];
    }
}

void insert(int k)
{
    if (!root) // 树为空
    {
        val[++tot] = k;
        root = tot;
        push_up(root);
        return;
    }
    int cur = root, f = 0;
    while (1)
    {
        f = cur;
        cur = ch[cur][val[cur] < k]; // 如果当前值 < k，则查找右子树
        if (!cur)                    // 空节点
        {
            val[++tot] = k;
            fa[tot] = f;
            ch[f][val[f] < k] = tot;
            push_up(tot);
            push_up(f);
            balance_ins(f);
            break;
        }
    }
}

int pre(int x)
{
    int cur = ch[x][0];
    if (!cur)
        return cur;
    while (ch[cur][1])
        cur = ch[cur][1];
    return cur;
}

void del(int k)
{
    int cur = root, f = 0;
    while (cur && val[cur] != k) // 查找目标节点
    {
        f = cur;
        cur = ch[cur][k > val[cur]];
    }
    if (!cur)
        return;                   // 未找到，直接返回
    if (ch[cur][0] && ch[cur][1]) // 如果有两个子节点
    {
        int pred = pre(cur);  // 找到前驱
        val[cur] = val[pred]; // 交换
        cur = pred;           // 转换为删除前驱
    }
    int child = ch[cur][0] ? ch[cur][0] : ch[cur][1]; // 至多只有一个子节点
    if (child)
        fa[child] = fa[cur];
    if (fa[cur])
        ch[fa[cur]][get_which(cur)] = child;
    else
        root = child; // 如果是根节点，直接更新
    balance_del(fa[cur]);
}

int query_maxle(int k) // 普通的二叉平衡树搜索
{
    int res = 0, cur = root;
    while (cur)
    {
        if (val[cur] == k)
            return val[cur];
        if (val[cur] < k)
        {
            res = cur;
            cur = ch[cur][1];
        }
        else
            cur = ch[cur][0];
    }
    if (res)
        return val[res];
    return -1;
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