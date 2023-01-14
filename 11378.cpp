#include<stdio.h>
#include<vector>
#include<queue>
#include<string.h>

#define BOUND 1000
#define S 2001
#define BRANCH 2002
#define E 2003
#define MAX 2004
using namespace std;


vector<int> graph[MAX];
int capacity[MAX][MAX];
int flow[MAX][MAX];

int N,M,K;

int bfs(int start, int end){
	queue<int> q;
	int parent[MAX];
	memset(parent, 0, MAX*sizeof(int));	
	parent[start] = -1;
	q.push(start);

	while(!q.empty()){
		int cur = q.front();
	//	printf("((%d))",cur);
		q.pop();

		for(auto next: graph[cur]){
	//		printf("<%d -> %d> %d/%d\n",cur,next,flow[cur][next], capacity[cur][next]);
			if(!parent[next] && capacity[cur][next] - flow[cur][next] >0){
				parent[next] = cur;
				q.push(next);
				if(next == end) break;
			}
		}
	}

	if(!parent[end]) return 0;
	int f = 2147483647;

	for(int cur = end; cur != start; cur = parent[cur]){
	//	printf("[%d <- %d]", cur, parent[cur]);
		int remaining = capacity[parent[cur]][cur] - flow[parent[cur]][cur];
		f = f < remaining? f : remaining;
	}

	for(int cur = end; cur != start; cur = parent[cur]){
		flow[parent[cur]][cur] += f;
		flow[cur][parent[cur]] -= f;
	}
	return f;
}
int main(){
	scanf("%d %d %d",&N, &M, &K);

	int a, b;
	graph[S].push_back(BRANCH);
	graph[BRANCH].push_back(S);
	capacity[S][BRANCH] = K;

	for(int i=1; i<=N; i++){
		scanf("%d",&a);
		graph[S].push_back(i);
		graph[i].push_back(S);
		capacity[S][i] = 1;

		graph[BRANCH].push_back(i);
		graph[i].push_back(BRANCH);
		capacity[BRANCH][i] = K;

		for(int j=0; j<a; j++){
			scanf("%d",&b);
			graph[i].push_back(BOUND + b);
			graph[BOUND + b].push_back(i);
			capacity[i][BOUND + b] = 1;
		}
	}
	for(int i=1; i<=M; i++){
		graph[BOUND + i].push_back(E);
		graph[E].push_back(BOUND + i);
		capacity[BOUND+i][E] = 1;
	}

	while(bfs(S, E)){
	}
	int ANS = 0;
	for(int i=1; i<=N; i++){
		ANS += flow[S][i];
	}	
	printf("%d\n",ANS + flow[S][BRANCH]);

}
