#include<stdio.h>

int dp[10][10002];

int min(int a, int b){
	if(a==-1)
		return b;
	else
		return a<b? a: b;
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
		dp[i][0] = i+moveL(s+i,d);
	}

	for(int j=1; j<N; j++){
		s = src[j] - '0';
		d = dst[j] - '0';
		for(int i=0; i<10; i++){
			dp[i][j] = -1;
		}
		for(int i=0; i<10; i++){
			dp[i][j] = min(dp[i][j], dp[i][j-1] + moveL(s+i, d));

			int R = moveR(s+i, d);
			dp[(i+R)%10][j] = min(dp[(i+R)%10][j], dp[i][j-1] + R);
			printf("<(%d, %d) %d %d %d %d>\n",i,j, dp[i][j], dp[i][j-1], moveL(s+i,d), moveR(s+i,d));
		}
	}
	for(int i=0; i<10; i++){
		for(int j=0; j<N; j++){
			printf("%2d ",dp[i][j]);
		}
		printf("\n");
	}
	int ANS = -1;
	for(int i=0; i<10; i++){
		ANS = min(ANS, dp[i][N-1]);
	}
	printf("%d\n",ANS);
}
