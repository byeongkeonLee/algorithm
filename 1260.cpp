#include<stdio.h>
#include<vector>
using namespace std;

int N,M;

char graph[1001][1001];

char visited[1001];
char visited2[1001];

int dfs_ans[1000], dfs_cnt;
int dfs(int cur){
	visited[cur] = 1;
	dfs_ans[dfs_cnt++] = cur;
	for(int i=1; i<=N;i++){
		if(graph[cur][i] && !visited[i]){
			dfs(i);
		}
	}
}

int bfs_ans[1000], bfs_cnt;

int bfs(int cur){
	vector<int> queue;

	queue.push_back(cur);
	bfs_ans[bfs_cnt++] = cur;
	visited2[cur] = 1;

	while(!queue.empty()){
		cur = queue.front();
		queue.erase(queue.begin());
		for(int i=1; i<=N; i++){
			if(graph[cur][i] && !visited2[i]){
				queue.push_back(i);
				bfs_ans[bfs_cnt++] = i;
				visited2[i] = 1;	
			}
		}
	}
}

int main(){
	int S;
	scanf("%d %d %d",&N,&M,&S);

	int a,b;
	for(int i=0; i<M; i++){
		scanf("%d %d",&a,&b);
		graph[a][b] = 1;
		graph[b][a] = 1;
	}

	dfs(S);
	for(int i=0; i<dfs_cnt; i++){
		printf("%d",dfs_ans[i]);
		if(i<dfs_cnt-1) printf(" ");
	}

	printf("\n");
	bfs(S);
	for(int i=0; i<bfs_cnt; i++){
		printf("%d",bfs_ans[i]);
		if(i<bfs_cnt-1) printf(" ");
	}
}
