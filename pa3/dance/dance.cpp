#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long ll;

const int N = 5e5 + 5;

struct Node // FHQ Treap 上的节点
{
	// 分别代表：左孩子下标、右孩子下标、子树大小、舞者代号、随机的修正值
	int ls, rs, siz, val, rnd;
	// 是否翻转区间的标记
	bool tag;
};

struct fhq_treap
{
	Node tr[N];
	int cnt;		   // 节点总数
	int root, x, y, z; // 树根节点和三个可能有用的临时节点，用于保存分裂后的子树

	int add_node(int val)
	{
		tr[++cnt].val = val;
		tr[cnt].siz = 1;
		tr[cnt].rnd = rand();
		tr[cnt].tag = false;
		return cnt;
	} // 添加节点，不单独调用

	void insert(int val, int rank)
	{
		x = y = 0;
		split(root, rank, x, y);
		root = merge(merge(x, add_node(val)), y);
	} // 在指定的 rank 处插入一个新节点，保持插入后 Treap 性质不变

	void push_up(int cur)
	{
		tr[cur].siz = tr[tr[cur].ls].siz + tr[tr[cur].rs].siz + 1;
	} // 上传子树大小信息

	void push_down(int cur)
	{
		tr[cur].tag = false;
		swap(tr[cur].ls, tr[cur].rs);
		tr[tr[cur].ls].tag ^= 1;
		tr[tr[cur].rs].tag ^= 1;
	} // 下推 tag，翻转两次相当于没有翻转

	void split(int cur, int k, int &X, int &Y)
	{
		// 按子树大小分裂
		if (!cur)
		{
			X = Y = 0;
			return;
		}
		// 如果当前区间有翻转标记，先下推
		if (tr[cur].tag)
			push_down(cur);
		// 如果左子树大小小于 k，那么“分裂点”一定在左子树中
		if (tr[tr[cur].ls].siz < k)
		{
			X = cur;
			split(tr[cur].rs, k - tr[tr[cur].ls].siz - 1, tr[cur].rs, Y);
		}
		else // 否则在右子树中
		{
			Y = cur;
			split(tr[cur].ls, k, X, tr[cur].ls);
		}
		// 上传子树大小信息
		push_up(cur);
	}

	int merge(int u, int v)
	{
		// 合并 u v 两棵子树
		if (!u || !v)
			return u + v;
		if (tr[u].rnd < tr[v].rnd) // 考虑两棵子树的修正值，以保证 Treap 堆的性质
		{
			if (tr[u].tag)
				push_down(u);
			tr[u].rs = merge(tr[u].rs, v);
			push_up(u);
			return u;
		}
		else
		{
			if (tr[v].tag)
				push_down(v);
			tr[v].ls = merge(u, tr[v].ls);
			push_up(v);
			return v;
		}
	}

	void swap_two(int i, int j)
	{
		// 交换舞者的操作，实际上只需要交换它们的代号
		if (i == j)
			return;
		x = y = z = 0;
		// 以 i 和 j 为分裂点，分裂出三棵子树
		split(root, (i + 1) - 1, x, y);
		split(y, j - i + 1, y, z);
		// i 和 j 分别位于中间那棵子树的最左和最右
		int L = y, R = y;
		while (tr[L].ls)
			L = tr[L].ls;
		while (tr[R].rs)
			R = tr[R].rs;
		// 交换它们的代号
		swap(tr[L].val, tr[R].val);
		// 复原
		root = merge(x, merge(y, z));
	}

	void rotate(int r)
	{
		// 整体旋转，实际上就是把整个序列分成两段，然后交换两段的位置
		x = y = 0;
		if (r == 0)
			return;
		if (r < 0)
		{
			r = -r;
			r %= cnt;
			split(root, r, x, y);
			merge(y, x);
			return;
		}
		r %= cnt;
		split(root, cnt - r, x, y);
		merge(y, x);
	}

	void reverse(int l, int r)
	{
		// l < r 时的翻转操作，实际上就是把 [l, r] 区间的子树分裂出来，然后打上标记
		x = y = z = 0;
		split(root, l - 1, x, y);
		split(y, r - l + 1, y, z);
		tr[y].tag ^= 1;
		root = merge(x, merge(y, z));
	}

	void flip(int l, int r)
	{
		if (l == r)
			return;
		if (l < r)
			reverse(l + 1, r + 1);
		else
		{
			// 若 l > r，则需要分裂 l r 外侧的子树，拼接为一棵临时的子树并翻转
			x = y = z = 0;
			swap(l, r);
			split(root, l + 1, x, y);
			split(y, r - l - 1, y, z);
			int siz1 = tr[x].siz, siz2 = tr[z].siz;
			int t = merge(z, x);
			tr[t].tag ^= 1;
			// 翻转之后分裂临时子树，并重新插入回去
			split(t, siz2, x, z);
			root = merge(z, merge(y, x));
		}
	}

	void print(int cur)
	{
		if (!cur)
			return;
		if (tr[cur].tag)
			push_down(cur);
		print(tr[cur].ls);
		printf("%d ", tr[cur].val);
		print(tr[cur].rs);
	} // 按照中序遍历的顺序打印所有舞者代号
} treap;

int n, m;

int main()
{
	srand(time(NULL));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		char op;
		scanf("%s", &op);
		// 对应所有序列操作
		if (op == 'I')
		{
			int a, b;
			scanf("%d%d", &a, &b);
			treap.insert(a, b);
		}
		else if (op == 'S')
		{
			int a, b;
			scanf("%d%d", &a, &b);
			treap.swap_two(min(a, b), max(a, b));
		}
		else if (op == 'R')
		{
			int r;
			scanf("%d", &r);
			treap.rotate(r);
		}
		else if (op == 'F')
		{
			int a, b;
			scanf("%d%d", &a, &b);
			treap.flip(a, b);
		}
	}
	// 输出答案
	treap.print(treap.root);
	return 0;
}