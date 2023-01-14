#include<stdio.h>

int pow[226];
int dp[50001];
int last;

int main(){
	int n;
	scanf("%d",&n);

	for(int i=1; i*i<=n; i++){
		pow[i] = i*i;
		last = i;
	}
	if(pow[last] == n){
		printf("1");
		return 0;
	}
	int min = 4;
	for(int i=1; i<=last; i++){
		for(int j=1; j<=last && pow[i]+pow[j] <=n; j++){
			if(pow[i]+pow[j] == n){
				printf("2");
				return 0;
			}
			for(int k=1; k<=last && pow[i]+pow[j]+pow[k] <=n; k++){
				if(pow[i]+pow[j]+pow[k] == n){
					min = 3;
				}
			}
		}
	}
	printf("%d", min);
}
