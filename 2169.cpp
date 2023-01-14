#include<stdio.h>

int arr[1001][1001];
int dp[1001];
int N,M;

int max(int a, int b){
	return a > b? a : b;
}
int main(){
	scanf("%d %d",&N, &M);
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			scanf("%d", &arr[i][j]);
			if(i==0){
				if(j==0) dp[j] = arr[i][j];
				else dp[j] = dp[j-1]+arr[i][j];
			}
		}
	}
	int l2r[1001];
	int r2l[1001];
	for(int i=1; i<N; i++){
		l2r[0] = dp[0]+arr[i][0];
		for(int j=1; j<M; j++){
			l2r[j] = max(dp[j]+arr[i][j], l2r[j-1]+arr[i][j]);
		}
		r2l[M-1] = dp[M-1]+arr[i][M-1];
		for(int j=M-2; j>=0; j--){
			r2l[j] = max(dp[j]+arr[i][j], r2l[j+1]+arr[i][j]);
		}
		for(int j=0; j<M; j++){
			dp[j] = max(l2r[j], r2l[j]);
		}
	}
	printf("%d\n",dp[M-1]);
}
