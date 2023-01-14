#include<stdio.h>
#include<vector>
using namespace std;

int dp[10][10002][2];

int min(int a, int b){
	if(a==-1)
		return 1;
	else
		return a<b? 0: 1;
}
int moveL(int s, int d){
	return (20+s-d)%10;
}
int moveR(int s, int d){
	return (20+d-s)%10;
}

int main(){
	int N;
	scanf("%d",&N);
	char src[10001], dst[10001];
	scanf("%s\n%s",src,dst);

	int s,d;
	s = src[0]-'0';
	d = dst[0]-'0';
	for(int i=0; i<10; i++){
		dp[i][0][0] = i+moveL(s+i,d);
		dp[i][0][1] = 0;
	}

	for(int j=1; j<N; j++){
		s = src[j] - '0';
		d = dst[j] - '0';
		for(int i=0; i<10; i++){
			dp[i][j][0] = -1;
			dp[i][j][1] = 0;
		}
		for(int i=0; i<10; i++){
			int Lval = dp[i][j-1][0] + moveL(s+i, d);
			if(min(dp[i][j][0], Lval)){
				dp[i][j][0] = Lval;
				dp[i][j][1] = i;
			}

			int R = moveR(s+i, d);
			int Rval = dp[i][j-1][0] + R;
			
			if(min(dp[(i+R)%10][j][0], Rval)){
				dp[(i+R)%10][j][0] = Rval;
				dp[(i+R)%10][j][1] = i;
			}
		}
	}
/*	for(int i=0; i<10; i++){
		for(int j=0; j<N; j++){
			printf("%d(%2d) ",dp[i][j][1], dp[i][j][0]);
		}
		printf("\n");
	}*/
	int ANS = -1, idx = -1;
	int stack[10001];
	for(int i=0; i<10; i++){
		if(min(ANS, dp[i][N-1][0])){
			idx = i;
			ANS = dp[i][N-1][0];
		}
	}
	for(int i = N-1; i>=0; i--){
		int next = dp[idx][i][1];
//		printf("(%d %d)\n",dp[idx][i][0], dp[next][i-1][0]);
		if(idx == next){
			stack[i] = dp[next][i-1][0] - dp[idx][i][0];
		}else{
			stack[i] = dp[idx][i][0] - dp[next][i-1][0];
		}
		idx = next;
	}
	printf("%d\n",ANS);

	int i=1;
	while(i<=N){
		printf("%d %d\n",i,stack[i-1]);
		i++;
	}
}
