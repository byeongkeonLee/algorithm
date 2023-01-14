#include<stdio.h>
#include<vector>
#include<string.h>
using namespace std;

vector<int> graph[1001];
char visited[1001];
int back[1001];

int dfs(int node){
	if(visited[node]) return 0;
	visited[node] = 1;
	
	int size = graph[node].size();
	for(int i=0; i<	size; i++){
		int next = graph[node][i];
		if(!back[next] || dfs(back[next])){
			back[next] = node;
			return 1;
		}
	}
	return 0;
}

int main(){
	int testcase;
	scanf("%d",&testcase);

	while(testcase--){
		int n,m;
		scanf("%d %d",&n,&m);

		for(int i=1; i<=m; i++){
			graph[i].clear();
		}
		memset(back, 0, 1001);
		int a, b;
		for(int i=1; i<=m; i++){
			scanf("%d %d",&a, &b);
			for(int j=a; j<=b; j++){
				graph[i].push_back(j);
			}
		}

		int Ans = 0;
		for(int i=1; i<=m; i++){
			memset(visited, 0, m+1);
			Ans += dfs(i)? 1: 0;
		}
		printf("%d\n",Ans);
	}	
}
