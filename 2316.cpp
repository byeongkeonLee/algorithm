#include<stdio.h>
#include<vector>
#include<queue>
#include<string.h>
#define NMAX 400
#define ARRAY 801
using namespace std;
vector<int> graph[ARRAY];

int flow[ARRAY][ARRAY];
int capacity[ARRAY][ARRAY];
int N, M;

int bfs(int start, int end){
	queue<int> q;
	q.push(start);
	int parent[ARRAY];

	memset(parent, 0, (ARRAY)*sizeof(int));

	while(!q.empty()){
		int cur = q.front();
		q.pop();
		
		if(cur == end) break;	
		for(auto next: graph[cur]){
//			printf("[%d %d]",cur,next);
			if(!parent[next] && capacity[cur][next] - flow[cur][next] > 0){
//				printf(" push");
				q.push(next);
				parent[next] = cur;
			}
//			printf("\n");
		}
	}
	if(!parent[end]) return 0;
	int f_min = 2147483647;
	for(int cur = end; cur != start; cur = parent[cur]){
		int prev = parent[cur];
		if(f_min > capacity[prev][cur] - flow[prev][cur])
			f_min = capacity[prev][cur] - flow[prev][cur];
	}

	for(int cur = end; cur != start; cur = parent[cur]){
		int prev = parent[cur];
		flow[prev][cur] += f_min;
		flow[cur][prev] -= f_min;
	}
	return 1;
}
int main(){
	scanf("%d %d",&N, &M);

	int a,b;
	for(int i=0; i<M; i++){
		scanf("%d %d", &a, &b);
		graph[a+NMAX].push_back(b);
		graph[b+NMAX].push_back(a);
		graph[a].push_back(b+NMAX);
		graph[b].push_back(a+NMAX);
		capacity[a+NMAX][b] = 1;
		capacity[b+NMAX][a] = 1;
	}
	for(int i=2; i<=N; i++){
		graph[i].push_back(i+NMAX);
		graph[i+NMAX].push_back(i);
		capacity[i][i+NMAX] = 1;
	}
	int Ans = 0;
	while(bfs(1+NMAX,2)){
		Ans++;
	}
	printf("%d\n",Ans);
}
