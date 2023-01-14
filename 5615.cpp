#include<stdio.h>

typedef unsigned long long int ULLI;

ULLI power(int a, ULLI p, ULLI MOD){
	if(p==1) return a % MOD;
	ULLI tmp = power(a, p/2, MOD);
	tmp = (tmp * tmp)%MOD;
	if(p%2) tmp = (tmp * a)%MOD;
	return tmp;
}

int isprime(ULLI n){
	int prime[3] = {2, 7, 61};
	for(int test_p = 0; test_p < 3; test_p++){
		int a = prime[test_p];
		if(a%n == 0) return 1;
		ULLI N = n-1;
		while(1){
			ULLI cur = power(a, N, n);
			if(cur == 1){
			   	if(N%2 == 0) N/=2;
				else break;
			}else if(cur == n-1) break;
			else{
				return 0;
			}
		}
	}
	return 1;
}

int main(){
	int N;
	scanf("%d",&N);
	int ans = 0;
	for(int i=0; i<N; i++){
		ULLI a;
		scanf("%lld",&a);
		ans += isprime(2*a+1) ? 1 : 0;
	}
	printf("%d\n",ans);
}
