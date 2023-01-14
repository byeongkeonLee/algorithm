#include<stdio.h>
#include<queue>
int dr[4] = {1,0,-1,0};
int dc[4] = {0,1,0,-1};
using namespace std;

char map[1000][1001];
char visited[2][1000][1000];
int N,M;

class Point{
	public:
	int r, c, item, cost;
	Point(int r, int c, int item, int cost): r(r), c(c), item(item), cost(cost){};
};
int bfs(int r, int c, int dest_r, int dest_c){
	queue<Point> q;
	q.push(Point(r,c,0,1));
	visited[0][r][c] = 1;
	if(r == dest_r && c == dest_c) return 1;
	
	while(!q.empty()){
		Point cur = q.front();
		q.pop();

		for(int i=0; i<4 ;i++){
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if(nr == dest_r && nc == dest_c) return cur.cost+1;
			if(nr < 0 || nc < 0 || nr >= N || nc >= M) continue;

			if(!visited[1][nr][nc] && map[nr][nc] == '1' && cur.item == 0){
				q.push(Point(nr, nc, 1, cur.cost+1));
				visited[1][nr][nc] = 1;
			}
			if(!visited[cur.item][nr][nc] && map[nr][nc] == '0'){
				q.push(Point(nr, nc, cur.item, cur.cost+1));
				visited[cur.item][nr][nc] = 1;
			}
		}
	}
	return -1;
}
int main(){
	scanf("%d %d\n",&N, &M);

	for(int i=0; i<N; i++){
		scanf("%s\n",map[i]);
	}
	printf("%d\n",bfs(0,0, N-1, M-1));
}
