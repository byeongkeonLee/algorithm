#include<stdio.h>
#include<string.h>

using namespace std;

long dp[100][1<<15];
char visited[100][1<<15];

int arr[15];
int len[15];

char input[15][51];
int N,K;

int power10[51];

long fact(int a){
	long ret = 1;
	while(a--){
		ret *= a+1;
	}
	return ret;
}
long dfs(int bit, int n, int r){
//	printf("%d %d %d\n",bit, n, r);	
	if(N==n){
	   	return r == 0 ? 1 : 0;
	}
	if(visited[r][bit]) return dp[r][bit];

	for(int i=0; i<N; i++){
		if(!(bit & (1<<i))){
			dp[r][bit] += dfs(bit | (1<<i), n+1,(r*power10[len[i]] + arr[i])%K );
			visited[r][bit] = 1;
		}
	}
	return dp[r][bit];
}
long GCD(long a, long b){
	long tmp = a%b;
	while(b){
		tmp = a%b;
		a = b;
		b = tmp;
	}
	return a;
}
int main(){
	scanf("%d",&N);
	for(int i=0; i<N; i++){
		scanf("%s\n",input[i]);
	}
	scanf("%d",&K);

	power10[0] = 1;
	for(int i=1; i<51; i++){
		power10[i] = (power10[i-1] * 10)%K;
	}

	for(int i=0; i<N; i++){
		len[i] = strlen(input[i]);
		for(int j=0; j<len[i]; j++){
			arr[i] = (arr[i]*10 + input[i][j]-'0')%K;
		}
	}


	long ans = dfs(0,0,0);
	long denominator = fact(N);
	if(!ans){
		printf("0/1\n");
	}else{
		long gcd = GCD(ans, denominator);
		printf("%ld/%ld\n",ans/gcd,denominator/gcd);
	}
}
