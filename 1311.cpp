#include<stdio.h>
#include<vector>
#define INF 2147483647
using namespace std;
int arr[20][20];
int dp[1<<20];
int N;

int min(int a, int b){
	return a>b? b:a;
}
int dfs(int cur, int n){
	if(n==N)
		return 0;
	if(dp[cur] < INF) return dp[cur];
	

	for(int i=0; i<N; i++){
		if(! (cur & (1<<i))){
			dp[cur] = min(dfs(cur | (1<<i), n+1)+arr[n][i], dp[cur]);
		}
	}
	return dp[cur];
}

int main(){
	scanf("%d",&N);

	for(int i=0; i<N;i++){
		for(int j=0; j<N; j++){
			scanf("%d",&arr[i][j]);
		}
	}
	for(int i=0; i< (1<<N); i++)
		dp[i] = INF;
	
	printf("%d\n",dfs(0, 0));
}
