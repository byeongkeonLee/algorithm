#include<stdio.h>
#include<vector>
using namespace std;
int dr[4] = {0,1,0,-1};
int dc[4] = {1,0,-1,0};
int R, C;
int cctv[8][2], cctv_cnt;
int map[8][8];
int counter[8][8];
int ANS;

void mask(int dir, int r, int c, int val){
	r = r+dr[dir];
	c = c+dc[dir];
	while(r>=0 && r<R && c>=0 && c<C && map[r][c] != 6){
		counter[r][c] += val;
		r = r+dr[dir];
		c = c+dc[dir];
	}
}

void dfs(int cur){
	if(cur == cctv_cnt){
		int invisible = 0;
		for(int i=0;i<R;i++){
			for(int j=0;j<C;j++){
				if(counter[i][j] == 0 && map[i][j] == 0){
					invisible ++;
				}
			}
		}
		if(ANS > invisible) ANS = invisible;
		return;
	}
	int r = cctv[cur][0], c = cctv[cur][1];
	int type = map[r][c];
	switch(type){
		case 1:
			for(int k=0;k<4;k++){
				mask(k, r, c, 1);	
				dfs(cur+1);
				mask(k, r, c, -1);	
			}
			break;
		case 2:
			for(int k=0;k<2;k++){
				mask(k, r, c, 1);
				mask(k+2, r, c, 1);
				dfs(cur+1);
				mask(k, r, c, -1);
				mask(k+2, r, c, -1);
			}
			break;
		case 3:
			for(int k=0;k<4;k++){
				mask(k, r, c, 1);
				mask((k+1)%4, r, c, 1);
				dfs(cur+1);
				mask(k, r, c, -1);
				mask((k+1)%4, r, c, -1);
			}
			break;
		case 4:
			for(int k=0;k<4;k++){
				mask(k, r, c, 1);
				mask((k+1)%4, r, c, 1);
				mask((k+2)%4, r, c, 1);
				dfs(cur+1);
				mask(k, r, c, -1);
				mask((k+1)%4, r, c, -1);
				mask((k+2)%4, r, c, -1);
			}
			break;
		case 5:
			for(int k=0;k<4;k++)
				mask(k, r, c, 1);
			dfs(cur+1);
			for(int k=0;k<4;k++)
				mask(k, r, c, -1);
			break;
	}

}
int main(){
	scanf("%d %d",&R,&C);
	for(int i=0;i<R;i++){
		for(int j=0;j<C;j++){
			scanf("%d",&map[i][j]);
			if(map[i][j] != 0 && map[i][j] != 6){
				cctv[cctv_cnt][0] = i;
				cctv[cctv_cnt][1] = j;
				cctv_cnt++;
			}
		}
	}
	ANS = 100;
	dfs(0);
	printf("%d\n",ANS);
}
