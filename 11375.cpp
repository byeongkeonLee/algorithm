#include<stdio.h>
#include<vector>
#include<string.h>
using namespace std;

int N, M;

vector<int> graph[1001];
int checked[1001];
char visited[1001];
int dfs(int node){
	
	if(visited[node]) return 0;
	visited[node] = 1;

	for(int i=0; i<graph[node].size(); i++){
		int next = graph[node][i];
		if(!checked[next] || dfs(checked[next])){
			checked[next] = node;
			return 1;
		}
	}
	return 0;
}
int main(){
	scanf("%d %d",&N, &M);

	for(int i=1; i<=N; i++){
		int a;
		scanf("%d",&a);
		for(int j=0; j<a; j++){
			int t;
			scanf("%d", &t);
			graph[i].push_back(t);
		}
	}
	
	int Ans = 0;
	for(int i=1; i<=N; i++){
		memset(visited, 0, 1001);
		Ans += dfs(i);
	}
	printf("%d\n",Ans);
}
