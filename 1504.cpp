#include<stdio.h>
#include<queue>
#include<algorithm>
#include<vector>
#include<string.h>
using namespace std;

vector<pair<int, int>> graph[801];

struct cmp{
	bool operator()(pair<int, int> a, pair<int, int> b){
		return a.second > b.second;
	}
};

void dijkstra(int s, int* ret){
	char visited[801]={0};
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
	memset(visited, 0, 801);
	visited[s] = 1;
	ret[s] = 0;
	int cur = s;
	int cost = 0;
	for(auto itr = graph[cur].begin(); itr != graph[cur].end(); itr++){
		pq.push(make_pair(itr->first, itr->second));
	}

	while(!pq.empty()){
		cur = pq.top().first;
		cost = pq.top().second;
		pq.pop();

		if(visited[cur]) continue;
		visited[cur] = 1;
		ret[cur] = cost;

		for(auto itr = graph[cur].begin(); itr != graph[cur].end(); itr++){
			pq.push(make_pair(itr->first, cost + itr->second));
		}
	}
}
int main(){
	int N, E;
	scanf("%d %d",&N, &E);

	int a,b,c;
	int cost_1[801]={-1}, cost_a[801]={-1}, cost_b[801]={-1};
	for(int i=0; i<E; i++){
		scanf("%d %d %d",&a, &b, &c);
		graph[a].push_back(make_pair(b, c));
		graph[b].push_back(make_pair(a, c));
	}
	scanf("%d %d",&a, &b);
	memset(cost_1, -1, 801);
	memset(cost_a, -1, 801);
	memset(cost_b, -1, 801);
	dijkstra(1, cost_1);
	dijkstra(a, cost_a);
	dijkstra(b, cost_b);

	int ab = 2147483647;
	if(cost_1[a] >= 0 && cost_a[b] >= 0 && cost_b[N] >= 0)
		ab = (a != 1? cost_1[a] : 0) + cost_a[b] + (b != N? cost_b[N] : 0);
	int ba = 2147483647;
    if(cost_1[b] >= 0 && cost_b[a] >= 0 && cost_a[N] >= 0)
		ba = cost_1[b] + cost_b[a] + cost_a[N];

	int ans = ab > ba ? ba : ab;
	printf("%d\n", ans == 2147483647? -1 : ans);
}
