#include <iostream>
#include <cstdlib>

using namespace std;

typedef long long ll;

const int N = 2e5 + 5;

ll n, m, X[N], Y[N];

void qsort(ll *a, int l, int r)
{
	int i = l, j = r;
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
}

bool to_left(ll xi, ll yi, ll x, ll y)
{
	return ((x * (y - yi) + xi * (-y)) > 0);
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	srand(time(NULL));
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> X[i];
	for (int i = 1; i <= n; i++)
		cin >> Y[i];
	qsort(X, 1, n);
	qsort(Y, 1, n);
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		ll xi, yi;
		cin >> xi >> yi;
		int l = 1, r = n;
		while (l < r)
		{
			int mid = (l + r) >> 1;
			if (to_left(xi, yi, X[mid], Y[mid]))
			{
				r = mid;
			}
			else
			{
				l = mid + 1;
			}
		} // 二分查找
		if (to_left(xi, yi, X[l], Y[l]))
			cout << l - 1 << "\n";
		else
			cout << l << "\n";
	}
	return 0;
}