#include<stdio.h>
#define MOD 1000000007

long fact[4000001];

long pow(long a, long b){
	if(b==1){
		return a;
	}
	long ret = pow(a, b/2);
	return ((ret*ret)%MOD * (b%2==1? a:1))%MOD;
}
int main(){
	int N;
	scanf("%d",&N);

	fact[0] = 1;
	for(int i=1; i<4000001; i++){
		fact[i] = (fact[i-1] *i)%MOD; 
	}

	for(int i=0; i<N; i++){
		int n, k;
		scanf("%d %d",&n,&k);

		long ANS = fact[n];

		long mod1 = (pow(fact[k], MOD-2))%MOD;
		long mod2 = (pow(fact[n-k], MOD-2))%MOD;

//		printf("<%ld %ld %ld>\n",ANS, mod1, mod2);
		printf("%ld\n",((ANS * mod1)%MOD * mod2)%MOD);
	}
}
