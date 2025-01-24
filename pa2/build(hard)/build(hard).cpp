#include <iostream>
#include <cstdio>

using namespace std;

const int N = 1e6 + 5;

struct Node
{
	int fa, nxt, pre, siz, cnt, dep, fstc, lstc;
	int sufmx;
} a[N]; // 用于保存树上的节点
// 成员分别为：父节点、下一个兄弟节点、上一个兄弟节点、子树大小、子树节点数、高度、第一个孩子节点、最后一个孩子节点、后缀最大高度

int n, m, root;

int init_siz(int x)
{
	if (a[x].cnt == 0)
		return a[x].siz;
	for (int i = a[x].fstc; i != -1; i = a[i].nxt)
		a[x].siz += init_siz(i);
	return a[x].siz;
} // 初始化子树大小

int init_dep(int x)
{
	if (a[x].cnt == 0)
		return a[x].dep;
	for (int i = a[x].fstc; i != -1; i = a[i].nxt)
		a[x].dep = max(a[x].dep, init_dep(i) + 1);
	return a[x].dep;
} // 初始化高度

void init_sufmx(int x)
{
	if (a[x].cnt == 0)
		return;
	int mx = -1e9;
	for (int i = a[x].lstc; i != -1; i = a[i].pre)
	{
		a[i].sufmx = max(mx, a[i].dep);
		mx = a[i].sufmx;
		init_sufmx(i);
	}
	return;
} // 初始化后缀最大高度

int get_dep(int x)
{
	if (a[x].cnt == 0)
		return 0;
	else
		return a[a[x].fstc].sufmx + 1;
} // 获取深度

void update_sufmx(int x)
{
	int cur = x;
	while (cur)
	{
		while (1)
		{
			int t1 = get_dep(cur);
			int t2 = a[cur].nxt != -1 ? a[a[cur].nxt].sufmx : 0;
			a[cur].sufmx = max(t1, t2);
			if (a[cur].pre == -1)
				break;
			cur = a[cur].pre;
		}
		cur = a[cur].fa;
	}
} // 更新后缀最大高度

void secede(int x)
{
	if (x == root)
		return;
	int father = a[x].fa;
	for (int i = father; i != 0; i = a[i].fa)
		a[i].siz -= a[x].siz;
	if (a[father].cnt == 1) // only child
	{
		a[father].fstc = a[father].lstc = -1;
		a[father].cnt--;
		update_sufmx(father);
	}
	else if (a[father].fstc == x) // first child
	{
		a[a[x].nxt].pre = -1;
		a[father].fstc = a[x].nxt;
		a[father].cnt--;
		update_sufmx(father);
	}
	else if (a[father].lstc == x) // last child
	{
		a[a[x].pre].nxt = -1;
		a[father].lstc = a[x].pre;
		a[father].cnt--;
		update_sufmx(a[x].pre);
	}
	else // middle
	{
		a[a[x].pre].nxt = a[x].nxt;
		a[a[x].nxt].pre = a[x].pre;
		a[father].cnt--;
		update_sufmx(a[x].pre);
	}
}

void attach(int s, int d, int k)
{
	a[s].fa = d;
	for (int i = d; i != 0; i = a[i].fa)
		a[i].siz += a[s].siz;
	if (a[d].cnt == 0) // only child
	{
		a[d].fstc = a[d].lstc = s;
		a[s].pre = a[s].nxt = -1;
		a[d].cnt++;
		update_sufmx(s);
	}
	else if (k == 0) // insert to head
	{
		a[a[d].fstc].pre = s;
		a[s].nxt = a[d].fstc;
		a[s].pre = -1;
		a[d].fstc = s;
		a[d].cnt++;
		update_sufmx(s);
	}
	else if (k == a[d].cnt) // insert to tail
	{
		a[s].pre = a[d].lstc;
		a[s].nxt = -1;
		a[a[d].lstc].nxt = s;
		a[d].lstc = s;
		a[d].cnt++;
		update_sufmx(s);
	}
	else // insert to middle
	{
		int cur = a[d].fstc;
		while (k--)
			cur = a[cur].nxt;
		a[a[cur].pre].nxt = s;
		a[s].pre = a[cur].pre;
		a[s].nxt = cur;
		a[cur].pre = s;
		a[d].cnt++;
		update_sufmx(s);
	}
}

int get_root()
{
	int q;
	scanf("%d", &q);
	int cur = root;
	bool flag = 0;
	for (int i = 1; i <= q; i++)
	{
		int t;
		scanf("%d", &t);
		if (flag)
			continue;
		if (a[cur].cnt == 0)
		{
			flag = 1;
			continue;
		}
		if (a[cur].cnt < t + 1)
		{
			flag = 1;
			continue;
		}
		cur = a[cur].fstc;
		while (t--)
			cur = a[cur].nxt;
	}
	return cur;
} // 读入路径表示法，返回对应节点

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		a[i].siz = 1;
		int cnt;
		scanf("%d", &cnt);
		a[i].cnt = cnt;
		if (cnt == 0) // leaf
		{
			a[i].fstc = a[i].lstc = -1;
			continue;
		}
		if (cnt == 1) // only 1 child
		{
			int t;
			scanf("%d", &t);
			a[t].fa = i;
			a[t].pre = -1;
			a[t].nxt = -1;
			a[i].fstc = a[i].lstc = t;
			continue;
		}
		int t, last;
		scanf("%d", &t);
		a[t].pre = -1;
		a[t].fa = i;
		a[i].fstc = t;
		last = t;
		for (int j = 2; j <= cnt - 1; j++)
		{
			scanf("%d", &t);
			a[last].nxt = t;
			a[t].pre = last;
			a[t].fa = i;
			last = t;
		}
		scanf("%d", &t);
		a[last].nxt = t;
		a[t].pre = last;
		a[t].nxt = -1;
		a[t].fa = i;
		a[i].lstc = t;
	}
	for (int i = 1; i <= n; i++)
		if (a[i].fa == 0)
		{
			root = i;
			break;
		}
	// 获取根节点
	a[root].pre = a[root].nxt = -1;
	init_siz(root);
	init_dep(root);
	a[root].sufmx = a[root].dep;
	init_sufmx(root);
	// 初始化
	for (int i = 1; i <= m; i++)
	{
		int op;
		scanf("%d", &op);
		if (op == 0)
		{
			int s = get_root();
			secede(s);
			int d = get_root();
			int k;
			scanf("%d", &k);
			attach(s, d, k);
		}
		else if (op == 1)
		{
			int t = get_root();
			printf("%d\n", get_dep(t));
		}
		else if (op == 2)
		{
			int t = get_root();
			printf("%d\n", a[t].siz);
		}
	}
	return 0;
}