#include<stdio.h>

int dp[14*14][1<<14];
char flag[14*14][1<<14];
int N, M;
int recursive(int cur, int status){
	if(cur >= N*M){
		if(status)	return 0;
		else return 1;
	}	
	if(flag[cur][status]) return dp[cur][status];
	int sum = 0;

	if(status & 1){
		sum += recursive(cur+1, status>>1);
	}else{
		if((cur+1)%M && !(status & 2)){
			sum += recursive(cur+2, status>>2);
		}
		sum += recursive(cur+1, (status>>1) | (1<<(M-1)));
	}

	flag[cur][status] = 1;
	return dp[cur][status] = (sum % 9901);

}
int main(){
	scanf("%d %d",&N, &M);
	printf("%d\n", recursive(0, 0));
}
