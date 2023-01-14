#include<stdio.h>
#define MOD 1000000007
int n;
int dp[1000001] = {0};
int main(){
	scanf("%d",&n);

	dp[0] = 1;
	dp[2] = 3;
	for(int i=4; i<=n; i+=2){
		dp[i] = ((long)4*dp[i-2]-dp[i-4])%MOD;
	}
	printf("%d\n",dp[n]);
}
