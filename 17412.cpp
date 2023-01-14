#include<stdio.h>
#include<vector>
#include<queue>
#include<string.h>
using namespace std;
int N, P;

vector<int> graph[401];
int flow[401][401];
int capacity[401][401];

int bfs(int start, int end){
	queue<int> q;
	int parent[401];
	memset(parent, 0, 401);
	q.push(start);

	while(!q.empty()){
		int cur = q.front();
		q.pop();

		for(auto next: graph[cur]){
//			printf("[%d] (%d %d)\n",next, parent[next], flow[cur][next]);
			if(parent[next] == 0 && capacity[cur][next] - flow[cur][next] > 0){
				q.push(next);
	//			printf("[cur: %d, %d push]\n",cur, next);
				parent[next] = cur;
				if(next == end) break;
			}
		}
	}
	if(parent[end] == 0) return 0;

	int f = 2147483647;
	for(int cur = end; cur != start; cur = parent[cur]){
		int space = capacity[parent[cur]][cur] - flow[parent[cur]][cur];
		f = f < space ? f : space;
	}
	for(int cur = end; cur != start; cur = parent[cur]){
		flow[parent[cur]][cur] += f;
		flow[cur][parent[cur]] -= f;
	}	
	return f;
}
int main(){
	scanf("%d %d",&N, &P);

	int a,b;
	for(int i=0; i<P; i++){
		scanf("%d %d",&a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
		capacity[a][b] = 1;
	}
	int Ans = 0;
	while(int ret = bfs(1,2)){
		Ans+=ret;
	}
	printf("%d\n",Ans);
}
