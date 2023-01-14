#include<stdio.h>
#include<vector>
#include<string.h>
using namespace std;

int N, K;
vector<int> graph[501];
int back[501];
char visited[501];
int dfs(int node){
	if(visited[node]) return 0;
	visited[node] = 1;

	int s = graph[node].size();
	for(int i=0; i<s; i++){
		int next = graph[node][i];
		if(!back[next] || dfs(back[next])){
			back[next] = node;
			return 1;
		}
	}
	return 0;
}
int main(){
	scanf("%d %d",&N, &K);

	for(int i=0; i<K; i++){
		int a,b;
		scanf("%d %d",&a,&b);
		graph[a].push_back(b);
	}

	int Ans = 0;
	for(int i=1; i<=N; i++){
		memset(visited,0, N+1);
		Ans += dfs(i)? 1: 0;
	}

	printf("%d\n",Ans);
}
