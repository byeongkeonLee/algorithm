#include<stdio.h>
#include<vector>

using namespace std;

vector<int> graph[100000];
vector<int> stack;
int dfsn[100000];
char visited[100000];
char finished[100000];

int mapping[100000];
int ingress[100000];
int id, map_id;

int min(int a, int b){
	return a > b? b : a;
}
int dfs(int cur){
	dfsn[cur] = ++id;
	int ret = dfsn[cur];
	for(auto itr = graph[cur].begin(); itr != graph[cur].end(); ++itr){
		if(visited[*itr] ==0){
			visited[*itr] = 1;
			stack.push_back(*itr);
			ret = min(ret, dfs(*itr));
		}else if(!finished[*itr]){
			ret = min(ret, dfsn[*itr]);
		}
	}
	if(ret == dfsn[cur]){
		int back;
		do{
			back = stack.back();
			stack.pop_back();
			finished[back] = 1;
			mapping[back] = map_id;
		}while(back != cur);
		map_id ++;
	}
	return ret;
}
int main(){
	int testcase;
	scanf("%d",&testcase);

	while(testcase--){
		int N, M;
		int ANS = 0;
		scanf("%d %d",&N, &M);

		id = 0;
		for(int i=0;i<N;i++){
			graph[i].clear();
			mapping[i] = 0;
			ingress[i] = 0;
			stack.clear();
			finished[i] = 0;
			visited[i] = 0;
			map_id = 0;
		}

		int a,b;
		for(int i=0; i<M;i++){
			scanf("%d %d",&a,&b);
			a--;b--;
			graph[a].push_back(b);
		}

		for(int i=0; i<N; i++){
			if(!finished[i]){
				visited[i] = 1;
				stack.push_back(i);
				dfs(i);
			}
		}

		for(int i=0; i<N; i++){
			for(auto itr = graph[i].begin(); itr != graph[i].end(); ++itr){
				if(mapping[i] != mapping[*itr])
					ingress[mapping[*itr]] ++;
			}
		}
		for(int i=0; i<map_id; i++){
			if(ingress[i]==0) ANS++;
		}
		printf("%d\n",ANS);
	}
}
