#include<stdio.h>

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

int N,M, R;
int arr[2][64][64];
char flag;
int tmp[32][32];
int max_sum, max_cur;

//scale : 4
int rotate(int r, int c, int scale){

	for(int i=0;i<scale;i++){
		for(int j=0;j<scale;j++){
			arr[flag^1][r+j][c+scale-i-1] = arr[flag][r+i][c+j];
		}
	}
}

int tonardo(int lv){
	for(int i=0; i< (R>>lv) ; i++){
		for(int j=0; j< (R>>lv); j++){
			rotate(i * (1<<lv), j* (1<<lv), 1<<lv);
		}
	}
	flag = flag^1;
}

int melt(){
	int cnt=0, nr, nc;
	for(int i=0;i<R;i++){
		for(int j=0;j<R;j++){
			cnt=0;
			for(int k=0;k<4;k++){
				nr = i+dr[k];
				nc = j+dc[k];
				if(nr>=0 && nr<R && nc>=0 && nc<R && arr[flag][nr][nc]>0){
					cnt++;
				}
			}
			arr[flag^1][i][j] = arr[flag][i][j] + ((arr[flag][i][j]>0 && cnt<3)? -1: 0);
		}
	}
	flag = flag^1;
}
int visited[64][64];
int dfs(int r, int c){
	int nr,nc, sum = 0;
	for(int i=0;i<4;i++){
		nr = r+dr[i];
		nc = c+dc[i];
		if(nr>=0 && nr<R && nc>=0 && nc<R && arr[flag][nr][nc]!=0 && !visited[nr][nc]){
			visited[nr][nc] = 1;
			sum+=dfs(nr,nc);
		}
	}
	return sum+1;
}
	                
int main(){
	scanf("%d %d",&N,&M);
	R = 1<<N;
	flag = 0;
	for(int i=0;i< R ;i++){
		for(int j = 0; j<R;j++){
			scanf("%d",&arr[flag][i][j]);
		}
	}

	int lv;
	for(int i=0;i<M;i++){
		scanf("%d", &lv);
		tonardo(lv);
		melt();
	}

	for(int i=0;i<R;i++){
		for(int j=0;j<R;j++){
			max_sum += arr[flag][i][j];
		}
	}
	for(int i=0;i<R;i++){
		for(int j=0;j<R;j++){
			if(visited[i][j]==0 && arr[flag][i][j]!=0){
				visited[i][j] = 1;
				int tmp = dfs(i,j);
				if(tmp > max_cur) max_cur = tmp;
			}
		}
	}	
	printf("%d\n%d\n",max_sum, max_cur);
}
