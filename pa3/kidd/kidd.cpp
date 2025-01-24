#include <cstdio>

using namespace std;

typedef long long ll;
typedef unsigned int ui;

const int N = 13180000;

ui lc[N], rc[N]; // 左右孩子编号
ui tag[N];
ll d[N]; // lazy tag 和节点值

ll n, m, cnt;

ll get_d(ui p, ui l, ui r)
{
	return d[p] + (ll)tag[p] * ((ll)r - (ll)l + 1);
} // 根据 tag 计算出节点管辖区间的真实和

void push_down(ui p, ui l, ui r)
{
	if (tag[p] == 0)
		return;
	d[p] = get_d(p, l, r);
	if (l != r)
	{
		if (!lc[p])
			lc[p] = ++cnt;
		if (!rc[p])
			rc[p] = ++cnt;
		tag[lc[p]] += tag[p];
		tag[rc[p]] += tag[p];
	}
	tag[p] = 0;
} // 下推 tag

void modify(ui p, ui l, ui r, ui ql, ui qr) // 区间修改。l r 为当前节点管辖区间，ql qr 为待修改区间
{
	if (ql > r || qr < l)
		return;				// 无交集
	if (ql <= l && qr >= r) // 完全覆盖，只需修改 tag
	{
		tag[p] += 1;
		return;
	}
	push_down(p, l, r); // 下推 tag
	// 递归修改左右孩子
	ll mid = (l + r) >> 1;
	if (ql <= mid)
	{
		if (!lc[p])
			lc[p] = ++cnt;			   // 假设没有左孩子，则新建一个左孩子
		modify(lc[p], l, mid, ql, qr); // 递归修改左孩子
	}
	if (qr > mid)
	{
		if (!rc[p])
			rc[p] = ++cnt; // 右孩子同理
		modify(rc[p], mid + 1, r, ql, qr);
	}
	// 在更新节点值时，也须考虑左右孩子是否存在
	d[p] = (lc[p] ? get_d(lc[p], l, mid) : 0) + (rc[p] ? get_d(rc[p], mid + 1, r) : 0);
}

ll query(ui p, ui l, ui r, ui ql, ui qr) // 区间查询。l r 为当前节点管辖区间，ql qr 为待查询区间
{
	if (!p)
		return 0; // 无节点
	if (ql > r || qr < l)
		return 0; // 无交集
	if (ql <= l && qr >= r)
		return get_d(p, l, r); // 完全覆盖
	push_down(p, l, r);		   // 下推 tag
	// 递归查询左右孩子
	ll mid = (l + r) >> 1;
	ll res = 0;
	if (ql <= mid)
		res += query(lc[p], l, mid, ql, qr);
	if (qr > mid)
		res += query(rc[p], mid + 1, r, ql, qr);
	return res;
}

int main()
{
	scanf("%lld%lld", &n, &m);
	ui root = 1;
	cnt = 1;
	for (int i = 1; i <= m; i++)
	{
		// 对应题目中操作
		char op;
		scanf("%s", &op);
		if (op == 'H')
		{
			ll s, t;
			scanf("%lld%lld", &s, &t);
			modify(root, 1, n, s, t);
		}
		else
		{
			ll s, t;
			scanf("%lld%lld", &s, &t);
			printf("%lld\n", query(root, 1, n, s, t));
		}
	}
	return 0;
}