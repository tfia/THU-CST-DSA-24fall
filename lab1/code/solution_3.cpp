#include <iostream>

using namespace std;

const int N = 2e3 + 5;

typedef long long ll;

int n, m, q;
ll matrix[N][N], sum[N][N];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			cin >> matrix[i][j];
			sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + matrix[i][j];
		}
	cin >> q;
	int x, y, a, b;
	for (int i = 1; i <= q; i++)
	{
		ll ans = 0;
		cin >> x >> y >> a >> b;
		ans = sum[x + a - 1][y + b - 1] - sum[x - 1][y + b - 1] - sum[x + a - 1][y - 1] + sum[x - 1][y - 1];
		cout << ans << "\n";
	}
	return 0;
}