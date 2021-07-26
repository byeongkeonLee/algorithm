#include<stdio.h>


int N,M,H;
char arr[30][9];
int ANS=4;
void dfs(int cur, int a, int b){
	if(cur>3) return;
	int i=0;
	for(i=0;i<N;i++){
		int pos = i;
		for(int h=0; h<H; h++){
			if(pos<N-1 && arr[h][pos] == 1) pos++;
			else if(pos>0 && arr[h][pos-1] == 1) pos--;
		}
		if(pos != i)break;
	}
	if(i== N){
		if(ANS > cur){
			ANS = cur;
		}
	}
		
	for(int i=a;i<H;i++){
		int j=0;
		if(i==a) j=b+1;
		for(;j<N-1;j++){
			if(j>0 && arr[i][j-1]==1) continue;
			if(j<N-1 && arr[i][j+1]==1) continue;
			if(arr[i][j]==1) continue;
			arr[i][j] = 1;
			dfs(cur+1, i, j); 
			arr[i][j] = 0;
		}
	}
}
int main(){
	scanf("%d %d %d",&N,&M,&H);

	int a,b;
	for(int i=0;i<M;i++){
		scanf("%d %d",&a,&b);
		a--;b--;
		arr[a][b] = 1;
	}
	dfs(0, 0, -1);
	printf("%d\n",ANS == 4? -1:ANS);
}
