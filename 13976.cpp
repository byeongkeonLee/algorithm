#include<stdio.h>
#include<stdlib.h>
#define MOD 1000000007


void dp(long N, long* pa, long *pb){
	long *a = (long*)malloc(sizeof(long)), *b = (long*) malloc(sizeof(long)); 
	if(N==1){
		*pa = 2;
		*pb = 1;
		return;
	}
	dp(N/2, a, b);

	*pa = ((*a * *a)%MOD + (3 * (*b * *b)%MOD)%MOD)%MOD;
	*pb = (2 * (*a * *b)%MOD)%MOD;
	if(N%2==1){
		long tmp = *pa;
		*pa = ((*pa * 2)%MOD + (*pb * 3)%MOD)%MOD;
		*pb = (tmp + (2 * *pb) %MOD)%MOD;
	}
	free(a);
	free(b);
}

int main(){
	long N, *a = (long*) malloc(sizeof(long)), *b = (long*) malloc(sizeof(long));
	scanf("%ld",&N);
	if(N%2)
		printf("0\n");
	else
		dp(N/2, a, b);
	printf("%ld %ld\n",*a,*b);
	printf("%ld",(*a+*b)%MOD);
}
