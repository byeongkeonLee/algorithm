#include<stdio.h>
#include<vector>

using namespace std;

vector<int> graph[500000];
vector<int> dest;
vector<int> stack;
char visited[500000];
char finished[500000];
int dfsn[500000], dfsid;

int atm[500000], mapping_atm[500000];

vector<int> mapping_graph[500000];
int mapping[500000], mapping_id;
char mapping_indegree[500000];
int mapping_visited[500000];
int dp[500000];

int min(int a, int b){
	return a > b ? b : a;
}

int dfs(int cur){
	dfsn[cur] = ++dfsid;
	int ret = dfsn[cur];
	for(auto itr = graph[cur].begin(); itr != graph[cur].end(); ++itr){
		if(!visited[*itr]){
			stack.push_back(*itr);
			visited[*itr] = 1;
			ret = min(ret, dfs(*itr));
		}else if(!finished[*itr]){
			ret = min(ret, dfsn[*itr]);
		}
	}
//	printf("--%d :%d %d--\n",cur, ret, dfsn[cur]);
	if(ret == dfsn[cur]){
		int back;
		do{
			back = stack.back();
			stack.pop_back();
			finished[back] = 1;
			mapping_atm[mapping_id] += atm[back];
			mapping[back] = mapping_id;
		}while(back!=cur);
//		printf("< mapping:%d [%d]>\n", mapping_id, mapping_atm[mapping_id]);
		mapping_id ++;
	}
	return ret;
}

void mapping_dfs(int cur, int sum){
	if(dp[cur] < sum+mapping_atm[cur])
		dp[cur] = sum+mapping_atm[cur];

	mapping_indegree[cur] --;
	if(mapping_indegree[cur] != 0){
		return;	
	}
	mapping_visited[cur] = 1;
	for(auto itr = mapping_graph[cur].begin(); itr != mapping_graph[cur].end(); ++itr){
		int next = *itr;
		if(cur == next) continue;

		if(!mapping_visited[next]){
			mapping_dfs(*itr, dp[cur]);				
		}
	}	
}

int main(){
	int N, M;
	scanf("%d %d",&N, &M);

	int a,b;
	for(int i=0; i<M; i++){
		scanf("%d %d",&a,&b);
		a--;b--;
		graph[a].push_back(b);
	}
	for(int i=0; i<N; i++){
		mapping[i] = -1;
		scanf("%d",&atm[i]);
	}


	int S, P;
	scanf("%d %d",&S, &P);
	S--;

	visited[S] = 1;
	stack.push_back(S);
	dfs(S);

	S = mapping[S];
	for(int i=0; i<P; i++){
		scanf("%d",&a);
		a--;
		dest.push_back(mapping[a]);
	}

	for(int i=0; i<N; i++){
		if(mapping[i] == -1) continue;
		for(auto itr = graph[i].begin(); itr != graph[i].end(); itr++){
			if(mapping[i] != mapping[*itr]){
				mapping_indegree[mapping[*itr]] ++;
				mapping_graph[mapping[i]].push_back(mapping[*itr]);
			}
		}
	}
	mapping_indegree[S] = 1;
	mapping_dfs(S, 0);

	int ANS = 0;
	for(auto itr = dest.begin(); itr != dest.end(); ++itr){
		if(ANS < dp[*itr])
			ANS = dp[*itr];
	}	
	printf("%d\n",ANS);

}
