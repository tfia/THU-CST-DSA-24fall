#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

typedef long long ll;

const int N = 1e6 + 5;

ll Q[N], a[N], m[N], mx[N], cnt, head, tail = -1, n, T;

void qsort(ll *a, ll l, ll r)
{
	ll i = l, j = r;
	ll x = a[(rand() % (r - l + 1)) + l]; // 随机选择一个数作为基准
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

ll find(ll x)
{
	ll l = 1, r = n;
	while (l < r)
	{
		ll mid = (l + r) >> 1;
		if (mx[mid] >= x)
			r = mid;
		else
			l = mid + 1;
	}
	if (mx[l] >= x)
		return l - 1;
	return l;
} // 二分查找，找到第一个大于等于x的数之前的位置

int main()
{
	srand(time(NULL));
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &m[i]);
	scanf("%lld", &T);
	ll tmpmx = -1e9;
	for (int i = 1; i <= n; i++)
	{
		if (m[i] + 1 < i)
			break;
		tmpmx = max(tmpmx, a[i - 1]);
		mx[++cnt] = tmpmx;
	}
	for (int i = cnt + 1 - m[cnt + 1]; i < cnt + 1; i++)
	{
		while (head <= tail && a[Q[tail]] <= a[i])
			tail--;
		Q[++tail] = i;
	} // 对于 m_i > i - 1 的特判
	for (int i = cnt; i < n; i++)
	{
		while (head <= tail && a[Q[tail]] <= a[i])
			tail--;
		Q[++tail] = i;
		while (Q[head] <= i - m[i + 1])
			head++;
		mx[++cnt] = a[Q[head]];
	} // 维护单调队列
	qsort(mx, 1, n); // 排序找到的所有最大值
	for (int i = 1; i <= T; i++)
	{
		ll p, q, ans1, ans2;
		scanf("%lld %lld", &p, &q);
		ans1 = find(p);
		ans2 = find(q) - ans1;
		printf("%lld %lld\n", ans1, ans2);
	} // 每次查询时，二分查找答案
	return 0;
}