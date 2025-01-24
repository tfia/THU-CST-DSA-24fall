#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

const int N = 501000 + 5;

string a, b;
ll dp[2][N], lena, lenb, k; // 分别对应 动态规划数组 文件名A长度 文件名B长度 阈值k
// dp数组第一维使用滚动数组的技巧来节省空间

int main()
{
	ios::sync_with_stdio(0), cin.tie(0); // 关闭同步以加速 cin cout
	cin >> lena >> lenb >> k;
	cin >> a >> b;
	int cur = 0; // 表示滚动数组当前转移的层
	for (int i = 1; i <= lena; i++, cur ^= 1)
	{
		for (int j = max(1ll, i - k); j <= min(i + k, lenb); j++) // 只考虑k步内能到的情形
		{
			if (a[i - 1] == b[j - 1])
				dp[cur][j] = dp[cur ^ 1][j - 1] + 1;
			else
				dp[cur][j] = max(dp[cur ^ 1][j], dp[cur][j - 1]);
		}
	} // 动态规划求A和B的LCS
	// dp[j]表示文件名A的前i个字符和文件名B的前j个字符的最长公共子序列长度
	ll ans = lena + lenb - (dp[cur ^ 1][lenb] << 1); // 计算答案
	if (ans > k)
		cout << -1;
	else
		cout << ans;
	return 0;
}