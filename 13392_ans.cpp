#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

int main() {
	int dp[10005][10];
	memset(dp, 0x3f, sizeof(dp));
	int a[10005], b[10005], n;
	scanf("%d", &n);
	FOR(i, 1, n) scanf("%1d", &a[i]);
	FOR(i, 1, n) scanf("%1d", &b[i]);
	FOR(i, 0, 9) dp[0][i] = i;
	FOR(i, 1, n) FOR(j, 0, 9){
		int lcnt = (b[i] - j - a[i] + 20) % 10;
		int rcnt = 10 - lcnt;
		dp[i][j] = min(dp[i][j], dp[i - 1][j] + rcnt);
		dp[i][(j + lcnt) % 10] = min(dp[i][(j + lcnt) % 10], dp[i - 1][j] + lcnt);
	}
	int ans = 1e9;
	FOR(i, 0, 9) ans = min(ans, dp[n][i]);
	printf("%d\n", ans);
	return 0;
}
