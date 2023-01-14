#include<stdio.h>
#define MOD 10007

long fact[50];

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
	for(int i=1; i<50; i++){
		fact[i] = (fact[i-1] *i)%MOD; 
	}
	int k = N-4;
	if(k<0){
		printf("0\n");
		return 0;
	}
	long ANS = fact[48];

	long mod1 = (pow(fact[k], MOD-2))%MOD;
	long mod2 = (pow(fact[48-k], MOD-2))%MOD;

	printf("%ld\n",(13*(ANS * mod1)%MOD * mod2)%MOD);
}
