#include<stdio.h>
#include<string.h>

using namespace std;

long dp[1<<15][100];

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
long func(){
	dp[0][0] = 1;
	int prev;

	for(int i=0; i< (1<<N); i++){
		for(int j=0; j<K; j++){
			if(dp[i][j]>0){
				for(int l=0; l<N; l++){
					if(!(i & (1<<l))){
						dp[i|(1<<l)][(j*power10[len[l]] + arr[l])%K] += dp[i][j];
					}
				}
			}
		}
	}
/*
	for(int j=0; j<K; j++){
		for(int i=0; i< (1<<N); i++){
			printf("[%d]",dp[i][j]);
		}
		printf("\n");
	}*/
	return dp[(1<<N)-1][0];
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


	long ans = func();
	long denominator = fact(N);
	if(!ans){
		printf("0/1\n");
	}else{
		long gcd = GCD(ans, denominator);
		printf("%ld/%ld\n",ans/gcd,denominator/gcd);
	}
}
