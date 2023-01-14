#include<stdio.h>

char arr[14][15];

int N, M;
int dp[14*14][1<<14];
bool flag[14*14][1<<14];

int topu_arr[5][5] = {{10, 8, 7, 5, 1}, {8,  6, 4, 3, 1}, {7, 4, 3, 2, 1}, {5, 3, 2, 2, 1}, {1, 1, 1, 1, 0}};
int topu(int a, int b){
	char r = arr[a/M][a%M];
	char c = arr[b/M][b%M];
	r -= r == 'F' ? 1 : 0;
	c -= c == 'F' ? 1 : 0;
	return topu_arr[r-'A'][c-'A'];
}

int recursive(int cur, int status){
	if(cur >= N*M){
		if(status) return -1;
		else{
			return 0;
		}
	}
	if(flag[cur][status]) return dp[cur][status];
//	printf("[%d %d %d]\n",	cur, status, val);

	int ret = 0;
	int r = 0;

	r = recursive(cur+1, status >> 1); //skip me
	if(r>ret) ret = r;

	if((cur+1)%M && !(status&2) && !(status&1)){
		r = recursive(cur+2, status >> 2) + topu(cur, cur+1);
		if(r>ret) ret = r;
	}

	if(!(status&1) && cur < (N-1)*M){
		r = recursive(cur+1, status >> 1 | (1<< (M-1))) + topu(cur, cur+M);
		if(r>ret) ret = r;
	}

	flag[cur][status] = 1;
	dp[cur][status] = ret;
//	printf("[%d %d %d]\n",cur, status, ret);
	return ret;
}
int main(){
	scanf("%d %d\n",&N, &M);
	for(int i=0; i<N; i++){
		scanf("%s\n", arr[i]);
	}
	printf("%d\n", recursive(0, 0));
}
